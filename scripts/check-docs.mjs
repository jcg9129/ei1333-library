import { existsSync, readdirSync, readFileSync, statSync } from "node:fs";
import { dirname, relative, resolve, sep } from "node:path";
import { fileURLToPath } from "node:url";

const repositoryRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..");
const docsDirectory = resolve(repositoryRoot, "docs");
const documentPaths = readdirSync(docsDirectory)
  .filter((name) => name.endsWith(".md"))
  .sort()
  .map((name) => resolve(docsDirectory, name));

const errors = [];

function report(path, line, message) {
  const location =
    line === undefined
      ? relative(repositoryRoot, path)
      : `${relative(repositoryRoot, path)}:${line}`;
  errors.push(`${location}: ${message}`);
}

function readFrontMatter(path, lines) {
  if (lines[0] !== "---") {
    report(path, 1, "front matter must start on the first line");
    return undefined;
  }

  const end = lines.indexOf("---", 1);
  if (end === -1) {
    report(path, 1, "front matter is not closed");
    return undefined;
  }

  const values = new Map();
  for (let index = 1; index < end; index += 1) {
    const match = lines[index].match(/^([A-Za-z0-9_-]+):\s*(.*?)\s*$/);
    if (!match) continue;

    const [, key, value] = match;
    if (values.has(key)) {
      report(path, index + 1, `front matter key '${key}' is duplicated`);
    } else {
      values.set(key, value);
    }
  }

  return values;
}

function checkDocumentationReference(path, value) {
  if (!value.startsWith("//") || value.length === 2) {
    report(
      path,
      undefined,
      "documentation_of must be a repository-relative path beginning with //",
    );
    return;
  }

  const target = resolve(repositoryRoot, value.slice(2));
  if (!target.startsWith(`${repositoryRoot}${sep}`)) {
    report(
      path,
      undefined,
      "documentation_of must remain inside the repository",
    );
  } else if (!existsSync(target) || !statSync(target).isFile()) {
    report(path, undefined, `documentation_of target does not exist: ${value}`);
  }
}

function checkFences(path, lines) {
  let openFence;

  for (let index = 0; index < lines.length; index += 1) {
    const match = lines[index].match(/^\s*(`{3,}|~{3,})(.*)$/);
    if (!match) continue;

    const marker = match[1];
    const suffix = match[2];
    if (!openFence) {
      openFence = {
        character: marker[0],
        length: marker.length,
        line: index + 1,
      };
    } else if (
      marker[0] === openFence.character &&
      marker.length >= openFence.length &&
      suffix.trim() === ""
    ) {
      openFence = undefined;
    }
  }

  if (openFence) {
    report(path, openFence.line, "code fence is not closed");
  }
}

for (const path of documentPaths) {
  const lines = readFileSync(path, "utf8").split(/\r?\n/);
  const frontMatter = readFrontMatter(path, lines);

  if (frontMatter) {
    for (const key of ["title", "documentation_of"]) {
      if (!frontMatter.has(key) || frontMatter.get(key) === "") {
        report(path, undefined, `front matter requires a non-empty '${key}'`);
      }
    }

    const documentationOf = frontMatter.get("documentation_of");
    if (documentationOf) checkDocumentationReference(path, documentationOf);
  }

  checkFences(path, lines);
}

if (errors.length > 0) {
  console.error(errors.join("\n"));
  process.exitCode = 1;
} else {
  console.log(`Checked ${documentPaths.length} documentation files.`);
}

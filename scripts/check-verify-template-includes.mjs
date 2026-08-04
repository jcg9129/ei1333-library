import { existsSync, readFileSync, readdirSync } from "node:fs";
import { dirname, relative, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const repositoryRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..");
const verifyDirectory = resolve(repositoryRoot, "test/verify");
const allowlistPath = resolve(
  repositoryRoot,
  "scripts/verify-template-include-allowlist.txt",
);
const templateInclude =
  /^\s*#\s*include\s*["<][^">]*template\/template\.hpp[">]/m;

function repositoryPath(path) {
  return relative(repositoryRoot, path).replaceAll("\\", "/");
}

function readAllowlist() {
  const entries = readFileSync(allowlistPath, "utf8")
    .split(/\r?\n/)
    .filter((line) => line !== "" && !line.startsWith("#"));
  const sortedEntries = [...new Set(entries)].sort();

  if (
    entries.length !== sortedEntries.length ||
    entries.some((entry, index) => entry !== sortedEntries[index])
  ) {
    throw new Error(
      `${repositoryPath(allowlistPath)} must be sorted and contain no duplicates`,
    );
  }
  return new Set(entries);
}

function findTemplateIncludes() {
  return new Set(
    readdirSync(verifyDirectory)
      .filter((name) => name.endsWith(".test.cpp"))
      .map((name) => resolve(verifyDirectory, name))
      .filter((path) => templateInclude.test(readFileSync(path, "utf8")))
      .map(repositoryPath),
  );
}

function optionValues(option) {
  const values = [];
  for (let index = 2; index < process.argv.length; index += 1) {
    if (process.argv[index] !== option) continue;
    if (index + 1 === process.argv.length) {
      throw new Error(`${option} requires a value`);
    }
    values.push(process.argv[index + 1]);
    index += 1;
  }
  return values;
}

const changedVerifyFiles = new Set(
  optionValues("--changed-file").filter((path) =>
    path.match(/^test\/verify\/.*\.test\.cpp$/),
  ),
);
const baseAllowlistPaths = optionValues("--base-allowlist");
if (baseAllowlistPaths.length > 1) {
  throw new Error("--base-allowlist may be specified at most once");
}

const allowlist = readAllowlist();
const templateIncludes = findTemplateIncludes();
const errors = [];

for (const path of templateIncludes) {
  if (!allowlist.has(path)) {
    errors.push(`${path}: template/template.hpp is not allowed`);
  }
}
for (const path of allowlist) {
  if (!existsSync(resolve(repositoryRoot, path))) {
    errors.push(`${repositoryPath(allowlistPath)}: missing file: ${path}`);
  } else if (!templateIncludes.has(path)) {
    errors.push(
      `${repositoryPath(allowlistPath)}: remove migrated entry: ${path}`,
    );
  }
}

for (const path of changedVerifyFiles) {
  if (templateIncludes.has(path)) {
    errors.push(
      `${path}: a new or modified verification test must not include template/template.hpp`,
    );
  }
}
if (baseAllowlistPaths.length === 1) {
  const baseAllowlist = new Set(
    readFileSync(baseAllowlistPaths[0], "utf8")
      .split(/\r?\n/)
      .filter((line) => line !== "" && !line.startsWith("#")),
  );
  for (const path of allowlist) {
    if (!baseAllowlist.has(path)) {
      errors.push(
        `${repositoryPath(allowlistPath)}: adding an exemption is not allowed: ${path}`,
      );
    }
  }
}

if (errors.length > 0) {
  console.error(errors.join("\n"));
  process.exitCode = 1;
} else {
  console.log(
    `Checked verification template includes (${allowlist.size} exemptions remain).`,
  );
}

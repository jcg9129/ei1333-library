import { readFileSync, readdirSync } from "node:fs";
import { dirname, relative, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const repositoryRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..");
const verifyDirectory = resolve(repositoryRoot, "test/verify");
const templateInclude =
  /^\s*#\s*include\s*["<][^">]*template\/template\.hpp[">]/m;

function repositoryPath(path) {
  return relative(repositoryRoot, path).replaceAll("\\", "/");
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

if (process.argv.length !== 2) {
  throw new Error("this check does not accept command-line options");
}

const templateIncludes = findTemplateIncludes();
const errors = [...templateIncludes].map(
  (path) => `${path}: template/template.hpp is not allowed`,
);

if (errors.length > 0) {
  console.error(errors.join("\n"));
  process.exitCode = 1;
} else {
  console.log("Checked verification template includes (no exemptions allowed).");
}

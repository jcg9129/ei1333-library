# Luzhiled's Library

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/ei1333/library/verify.yml?branch=master&style=flat-square) [![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://ei1333.github.io/library/)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/ei1333/library?style=flat-square)

## Table of Contents

- [About](#-about)
- [Contributions](#-contributions)
- [License](#-license)

## 🚀 About

Luzhiled's Library is a library implemented in C++17 for competitive programming.

## 🤝 Contributions

I welcome you to open issues or PRs if you find any typos or bugs.

You should apply `clang-format` to all files with the `.hpp` extension. Please use the predefined `google` style.

### Documentation

Create a new document from [`templates/documentation.md`](templates/documentation.md). Keep `title` and `documentation_of` in the front matter, and use H1 headings for APIs and H2 headings for their constraints and complexity.

Install and run the Markdown tools with:

```console
npm install
npm run docs:check
```

To apply safe formatting changes, run `npm run docs:format`. The check also verifies required front matter, `documentation_of` targets, and code fence pairs.

## 📃 License

Luzhiled's Library is licensed under [the Unlicense](https://choosealicense.com/licenses/unlicense/).

[Back to top](#top)

# ICPC Templates
<p align="center">
  <a href="/docs/README.md">English</a> •
  <a href="/docs/README.zh-CN.md">简体中文 (Simplified Chinese)</a>
</p>
## Introduction

ICPC Templates of Leachim in LaTeX

With a collection of implementation of Algorithms and Data Structure for Competitive Programming.

It may contain several open source code from online resources, which will be strictly enclosed with namespace and labeled with origin as comment (if possible).

## Features

1. Enable Math Formula in LaTeX display in comments. 
2. Easy to use and modify, highly modular.
3. Enable a neat Syntax Highlight.
4. Highly printable.
5. Maintained by a ICPC retired competitor.

## Compilation Guide

### Dependancy

XeLaTeX(Packages are listed in tex file), Pygments(For minted package to syntax highlight in code)

XeLaTeX can be obtained by installing LaTeX distribution on your device, for which [Tex Live](https://www.tug.org/texlive/) are recommanded.

[Pygments](https://pygments.org/) can be install by `pip` or package manager of your choice.
#### Using pip
```bash
pip install Pygments
```
#### Using Homebrew
```bash
brew install pygments
```

### Compilation

In the directory `./LaTeX`, compile the `templates.tex` file using

```bash
make
```
If you encounter mistakes about pygmentize, it is posible that the flag "-shell-escape" is left or you didn't configure the path for pygments properly.

## Future Features

Divide the tex file for each section.

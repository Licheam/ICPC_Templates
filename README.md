# ICPC Templates 算法竞赛模板
## General Information 简介

ICPC Templates of Leachim in LaTeX
这是我用LaTeX整理的ICPC模板（会持续更新）

With a collection of implementation of Algorithms and Data Structure for Competitive Programming.
拥有一系列竞技编程的算法和数据结构的实现

I will keep this updated.

It may contain several open source code from online resources, which will be strictly enclosed with namespace and labeled with origin as comment(if possible).

## Features 特点

1. Easy to use and modify, highly modular. 容易使用和修改，高度模块化。
2. Enable a neat Syntax Highlight. 拥有非常优雅的代码语法高亮。
3. Highly printable. 可直接打印。
4. Maintaining by a ICPC active competitor. 由ICPC现役选手维护。

## Compilation Guide 编译指南

### Requirements 前置需求

XeLaTeX(Packages are listed in tex file), Pygments(For minted package to syntax highlight in code)

XeLaTeX can be obtained by installing LaTeX distribution on your device, for which Tex Live are recommanded.

Pygments can be install by pip, just simply run
```bash
pip install Pygments
```

### Compilation

In the directory LaTeX, compile the templates.tex file using

```bash
xelatex -shell-escape templates
```
If you encounter mistakes abount pygmentize, it is posible that the flag "-shell-escape" is left or you didn't config the path for pygments properly.
For the latter reason, you may want to install the pygments or make a soft link inside the tex folder.


## Future Features

Divide the tex file for each section. 将tex文件按章节分开。


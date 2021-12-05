# ICPC Templates 算法竞赛模板
## General Information 简介

ICPC Templates of Leachim in LaTeX
这是我用LaTeX整理的ICPC模板

With a collection of implementation of Algorithms and Data Structure for Competitive Programming.
拥有一系列竞技编程的算法和数据结构的实现

It may contain several open source code from online resources, which will be strictly enclosed with namespace and labeled with origin as comment(if possible).

## Features 特点

1. Enable Math Formula in LaTeX display in comments. 支持在注释内显示LaTeX数学公式
1. Easy to use and modify, highly modular. 容易使用和修改，高度模块化。
2. Enable a neat Syntax Highlight. 拥有非常优雅的代码语法高亮。
3. Highly printable. 可直接打印。
4. Maintained by a ICPC retired competitor. 被ICPC退役选手维护过。

## Compilation Guide 编译指南

### Dependancy 依赖项

XeLaTeX(Packages are listed in tex file), Pygments(For minted package to syntax highlight in code)

XeLaTeX can be obtained by installing LaTeX distribution on your device, for which [Tex Live](https://www.tug.org/texlive/) are recommanded.

[Pygments](https://pygments.org/) can be install by pip, just simply run
```bash
pip install Pygments
```

### Compilation 编译指南

In the directory LaTeX, compile the templates.tex file using

```bash
xelatex -shell-escape templates
```
If you encounter mistakes about pygmentize, it is posible that the flag "-shell-escape" is left or you didn't config the path for pygments properly.
For the latter reason, you may want to install the pygments or make a soft link inside the tex folder.


## Future Features 计划中的功能

Divide the tex file for each section. 将tex文件按章节分开。

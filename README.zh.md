# ICPC 模板

## 简介

Leachim 的 ICPC 模板（使用 LaTeX）

包含用于竞技编程的算法和数据结构实现集合。

它可能包含来自在线资源的开源代码，这些代码将严格用命名空间封装，并尽可能标注来源。

## 功能

1. 允许在注释中以 LaTeX 样式显示数学公式。
2. 易于使用和修改，高度模块化。
3. 支持简洁的语法高亮显示。
4. 可打印。
5. 由一位退役的 ICPC 选手维护。

## 编译指南

### 依赖项

XeLaTeX（程序包列在 tex 文件中）、Pygments（用于代码语法高亮的 minted 程序包）

XeLaTeX 可以通过在您的设备上安装 LaTeX发行版获得，推荐使用 [Tex Live](https://www.tug.org/texlive/)。

[Pygments](https://pygments.org/) 可以通过您选择的包管理器或 `pip` 安装。

#### 使用 pip

```bash
pip install Pygments
```

#### 使用 Homebrew

```bash
brew install pygments
```

### 编译

在 `./LaTeX` 目录中，使用以下命令编译 `templates.tex`：

```bash
make
```
如果您遇到有关 pygmentize 的错误，可能因为`Pygments`没有被正确的配置入环境变量。

## 未来功能

为每个部分划分 tex 文件。

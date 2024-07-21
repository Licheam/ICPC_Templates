// This function gets your whole document as its `body` and formats
// it as a simple fiction book.
#let book(
  // The book's title.
  title: [Book title],

  // The book's author.
  author: "Author",

  // The author's affiliation.
  affiliation: "Affiliation",

  // The paper size to use.
  paper-size: "a4",

  // A dedication to display on the third page.
  dedication: none,

  // Details about the book's publisher that are
  // display on the second page.
  publishing-info: none,

  // The book's content.
  body,
) = {
  // Set the document's metadata.
  set document(title: title, author: author)

  // Set the body font. TeX Gyre Pagella is a free alternative
  // to Palatino.
  set text(font: "TeX Gyre Pagella")

  // Configure the page properties.
  set page(
    paper: paper-size,
    margin: (left: 3.18cm, right: 3.18cm, bottom: 2.54cm, top: 2.54cm),
  )

  // The first page.
  page(align(center + horizon)[
    #text(2em)[*#title*]
    #v(2em, weak: true)
    #text(1.6em, author)
    #v(2em, weak: true)
    #text(1.6em, affiliation)
    #v(2em, weak: true)
    #image("../Figures/ICPC.png", width: 20em)
    #v(2em, weak: true)
    #text(1.6em, datetime.today().display())
  ])

  pagebreak()

  // Books like their empty pages.
  pagebreak(to: "odd")

  // Configure paragraph properties.
  set par(leading: 0.78em, first-line-indent: 12pt, justify: true)
  show par: set block(spacing: 0.78em)

  set heading(numbering: "1.")

  // Start with a chapter outline.
  outline(indent: auto)

  // Configure page properties.
  set page(
    numbering: "1",

    // The header always contains the book title on odd pages and
    // the chapter title on even pages, unless the page is one
    // that starts a chapter (the chapter title is obvious then).
    header: locate(loc => {
      // Are we on an odd page?
      let i = counter(page).at(loc).first()
      if calc.odd(i) {
        return text(0.95em, smallcaps(title))
      }

      // Are we on a page that starts a chapter? (We also check
      // the previous page because some headings contain pagebreaks.)
      let all = query(heading, loc)
      if all.any(it => it.location().page() in (i - 1, i)) {
        return
      }

      // Find the heading of the section we are currently in.
      let before = query(selector(heading).before(loc), loc)
      if before != () {
        align(right, text(0.95em, smallcaps(before.last().body)))
      }
    }),
  )

  // Configure chapter headings.
  show heading.where(level: 1): it => {
    // Always start on odd pages.
    pagebreak(to: "odd")

    // Create the heading numbering.
    let number = if it.numbering != none {
      counter(heading).display(it.numbering)
      h(7pt, weak: true)
    }

    v(5%)
    text(2em, weight: 700, block([#number #it.body]))
    v(1.25em)
  }
  show heading: set text(11pt, weight: 400)

  body
}

#show: book.with(
  title: [ICPC Templates],
  author: "Leachim",
  affiliation: "Xidian University",
)

= C++模板
== 图论
=== 树的重心Get_Centroid
#raw(read("../Cpp/图论/树的重心Get_Centroid.cpp"), lang: "cpp", tab-size: 4)

=== 最小生成树Kruskal
#raw(read("../Cpp/图论/最小生成树Kruskal.cpp"), lang: "cpp", tab-size: 4)

=== 最小生成树Prim
#raw(read("../Cpp/图论/最小生成树Prim.cpp"), lang: "cpp", tab-size: 4)

=== 最短路Djikstra
#raw(read("../Cpp/图论/最短路Djikstra.cpp"), lang: "cpp", tab-size: 4)

=== 最短路SPFA
#raw(read("../Cpp/图论/最短路SPFA.cpp"), lang: "cpp", tab-size: 4)

=== 最近公共祖先LCA_Doubling
#raw(read("../Cpp/图论/最近公共祖先LCA_Doubling.cpp"), lang: "cpp", tab-size: 4)

=== 最近公共祖先LCA_Tarjan
#raw(read("../Cpp/图论/最近公共祖先LCA_Tarjan.cpp"), lang: "cpp", tab-size: 4)

=== 最近公共祖先LCA_Heavy-Light_Decomposition
#raw(read("../Cpp/图论/最近公共祖先LCA_Heavy-Light_Decomposition.cpp"), lang: "cpp", tab-size: 4)

=== 判断负环SPFA_Negtive_Cycle
#raw(read("../Cpp/图论/判断负环SPFA_Negtive_Cycle.cpp"), lang: "cpp", tab-size: 4)

=== 拓扑排序Topological_Sort_Khan
#raw(read("../Cpp/图论/拓扑排序Topological_Sort_Khan.cpp"), lang: "cpp", tab-size: 4)

=== 树链剖分Heavy-Light_Decomposition
#raw(read("../Cpp/图论/树链剖分Heavy-Light_Decomposition.cpp"), lang: "cpp", tab-size: 4)

== 多项式
=== FFT字符串匹配String_Match_FFT
#raw(read("../Cpp/多项式/FFT字符串匹配String_Match_FFT.cpp"), lang: "cpp", tab-size: 4)

=== FFT递归Fast_Fourier_Transform_Cooley-Tukey_Recursion
#raw(read("../Cpp/多项式/FFT递归Fast_Fourier_Transform_Cooley-Tukey_Recursion.cpp"), lang: "cpp", tab-size: 4)

=== FFT递推Fast_Fourier_Transform_Cooley-Tukey_Iteration
#raw(read("../Cpp/多项式/FFT递推Fast_Fourier_Transform_Cooley-Tukey_Iteration.cpp"), lang: "cpp", tab-size: 4)

=== NTT递推Number_Theoretic_Transforms
#raw(read("../Cpp/多项式/NTT递推Number_Theoretic_Transforms.cpp"), lang: "cpp", tab-size: 4)

=== MTT任意模数Fast_Fourier_Transform_MOD
#raw(read("../Cpp/多项式/MTT任意模数Fast_Fourier_Transform_MOD.cpp"), lang: "cpp", tab-size: 4)

=== 多项式求逆Polynomial_Inverse
#raw(read("../Cpp/多项式/多项式求逆Polynomial_Inverse.cpp"), lang: "cpp", tab-size: 4)

== 字符串
=== 字符串哈希String_Hash
#raw(read("../Cpp/字符串/字符串哈希String_Hash.cpp"), lang: "cpp", tab-size: 4)

=== 最小表示法Lexicographically_Minimal_String_Rotation
#raw(read("../Cpp/字符串/最小表示法Lexicographically_Minimal_String_Rotation.cpp"), lang: "cpp", tab-size: 4)

=== 马拉车Manacher
#raw(read("../Cpp/字符串/马拉车Manacher.cpp"), lang: "cpp", tab-size: 4)

=== 字符串匹配KMP
#raw(read("../Cpp/字符串/字符串匹配KMP.cpp"), lang: "cpp", tab-size: 4)

=== AC自动机AC-Automaton
#raw(read("../Cpp/字符串/AC自动机AC-Automaton.cpp"), lang: "cpp", tab-size: 4)

=== 后缀数组Suffix_Array
#raw(read("../Cpp/字符串/后缀数组Suffix_Array.cpp"), lang: "cpp", tab-size: 4)

=== 后缀自动机Suffix-Automaton
#raw(read("../Cpp/字符串/后缀自动机Suffix-Automaton.cpp"), lang: "cpp", tab-size: 4)

=== 广义后缀自动机General_Suffix-Automaton
#raw(read("../Cpp/字符串/广义后缀自动机General_Suffix-Automaton.cpp"), lang: "cpp", tab-size: 4)

== 数据结构
=== 并查集Disjoin_Set_Union
#raw(read("../Cpp/数据结构/并查集Disjoin_Set_Union.cpp"), lang: "cpp", tab-size: 4)

=== 可撤销并查集Disjoin_Set_Union_Withdrawable
#raw(read("../Cpp/数据结构/可撤销并查集Disjoin_Set_Union_Withdrawable.cpp"), lang: "cpp", tab-size: 4)

=== 分块Block_1
#raw(read("../Cpp/数据结构/分块Block_1.cpp"), lang: "cpp", tab-size: 4)

=== 分块Block_2
#raw(read("../Cpp/数据结构/分块Block_2.cpp"), lang: "cpp", tab-size: 4)

=== 分块Block_4
#raw(read("../Cpp/数据结构/分块Block_4.cpp"), lang: "cpp", tab-size: 4)

=== 树状数组Binary_Indexed_Tree
#raw(read("../Cpp/数据结构/树状数组Binary_Indexed_Tree.cpp"), lang: "cpp", tab-size: 4)

=== 二维树状数组2D_Binary_Indexed_Tree
#raw(read("../Cpp/数据结构/二维树状数组2D_Binary_Indexed_Tree.cpp"), lang: "cpp", tab-size: 4)

=== 线段树Segment_Tree
#raw(read("../Cpp/数据结构/线段树Segment_Tree.cpp"), lang: "cpp", tab-size: 4)

=== 线段树Segment_Tree_Multiply
#raw(read("../Cpp/数据结构/线段树Segment_Tree_Multiply.cpp"), lang: "cpp", tab-size: 4)

=== 扫描线Scanline
#raw(read("../Cpp/数据结构/扫描线Scanline.cpp"), lang: "cpp", tab-size: 4)

=== zkw线段树ZKW_Segment_Tree
#raw(read("../Cpp/数据结构/zkw线段树ZKW_Segment_Tree.cpp"), lang: "cpp", tab-size: 4)

=== 吉司机线段树Segment_Tree_Beats
#raw(read("../Cpp/数据结构/吉司机线段树Segment_Tree_Beats.cpp"), lang: "cpp", tab-size: 4)

=== 李超线段树Li-Chao_Segment_Tree
#raw(read("../Cpp/数据结构/李超线段树Li-Chao_Segment_Tree.cpp"), lang: "cpp", tab-size: 4)

=== 可并堆左偏树Leftist_Tree
#raw(read("../Cpp/数据结构/可并堆左偏树Leftist_Tree.cpp"), lang: "cpp", tab-size: 4)

=== Splay树Splay_Tree
#raw(read("../Cpp/数据结构/Splay树Splay_Tree.cpp"), lang: "cpp", tab-size: 4)

=== Splay树Splay_Tree_Flip
#raw(read("../Cpp/数据结构/Splay树Splay_Tree_Flip.cpp"), lang: "cpp", tab-size: 4)

=== Splay树Splay_Tree_Dye&Flip
#raw(read("../Cpp/数据结构/Splay树Splay_Tree_Dye&Flip.cpp"), lang: "cpp", tab-size: 4)

=== 动态树Link-Cut_Tree
#raw(read("../Cpp/数据结构/动态树Link-Cut_Tree.cpp"), lang: "cpp", tab-size: 4)

=== 红黑树Red_Black_Tree
#raw(read("../Cpp/数据结构/红黑树Red_Black_Tree.cpp"), lang: "cpp", tab-size: 4)

== 数论

=== 线性求逆元 Modular Multiplicative Inverse
#raw(read("../Cpp/数论/线性求逆元Modular_Multiplicative_Inverse.cpp"), lang: "cpp", tab-size: 4)

=== 数论分块 Block Division
#raw(read("../Cpp/数论/数论分块Block_Division.cpp"), lang: "cpp", tab-size: 4)

=== 贝祖引理 Bezout Lemma
#raw(read("../Cpp/数论/贝祖引理Bezout_Lemma.cpp"), lang: "cpp", tab-size: 4)

=== 卢卡斯 Lucas
#raw(read("../Cpp/数论/卢卡斯Lucas.cpp"), lang: "cpp", tab-size: 4)

=== 拓展欧几里得 Exgcd
#raw(read("../Cpp/数论/拓展欧几里得Exgcd.cpp"), lang: "cpp", tab-size: 4)

=== 拓展欧拉定理 Ex Euler Theorem - Automaton
#raw(read("../Cpp/数论/拓展欧拉定理Ex_Euler_Theorem.cpp"), lang: "cpp", tab-size: 4)

=== 中国剩余定理 Chinese Remainder Theorem
#raw(read("../Cpp/数论/中国剩余定理Chinese_Remainder_Theorem.cpp"), lang: "cpp", tab-size: 4)

=== 拓展中国剩余定理 Ex Chinese Remainder Theorem
#raw(read("../Cpp/数论/拓展中国剩余定理Ex_Chinese_Remainder_Theorem.cpp"), lang: "cpp", tab-size: 4)

=== 欧拉筛 Eular Sieve
#raw(read("../Cpp/数论/欧拉筛Eular_Sieve.cpp"), lang: "cpp", tab-size: 4)

=== 杜教筛 Dujiao Sieve
#raw(read("../Cpp/数论/杜教筛Dujiao_Sieve.cpp"), lang: "cpp", tab-size: 4)

=== 求原根 Get Primitive Root
#raw(read("../Cpp/数论/求原根Get_Primitive_Root.cpp"), lang: "cpp", tab-size: 4)

=== 素数测试 Miller Rabin
#raw(read("../Cpp/数论/素数测试Miller_Rabin.cpp"), lang: "cpp", tab-size: 4)

=== 大数分解 Pollard Rho
#raw(read("../Cpp/数论/大数分解Pollard_Rho.cpp"), lang: "cpp", tab-size: 4)


== 组合数学
=== 康托展开Cantor
#raw(read("../Cpp/组合数学/康托展开Cantor.cpp"), lang: "cpp", tab-size: 4)
=== 波利亚Polya
#raw(read("../Cpp/组合数学/波利亚Polya.cpp"), lang: "cpp", tab-size: 4)
=== 卡特兰数Catalan
#include "../Cpp/组合数学/卡特兰数Catalan.typ"
=== 斯特林数Stirling
#include "../Cpp/组合数学/斯特林数Stirling.typ"
=== 范德蒙德卷积Vandermonde_Convolution
#include "../Cpp/组合数学/范德蒙德卷积Vandermonde_Convolution.typ"

== 网络流
=== 最大费用流 Minimum-Cost Flow Edmonds-Karp
#raw(read("../Cpp/网络流/最大费用流Minimum-Cost_Flow_Edmonds-Karp.cpp"), lang: "cpp", tab-size: 4)

=== 最大流 Maximum Flow Edmonds-Karp
#raw(read("../Cpp/网络流/最大流Maximum_Flow_Edmonds-Karp.cpp"), lang: "cpp", tab-size: 4)

=== 最大流 Maximum Flow Dinic
#raw(read("../Cpp/网络流/最大流Maximum_Flow_Dinic.cpp"), lang: "cpp", tab-size: 4)

=== 二分图最大匹配 Bipartite Graph Maximum Matching Dinic
#raw(read("../Cpp/网络流/二分图最大匹配Bipartite_Graph_Maximum_Matching_Dinic.cpp"), lang: "cpp", tab-size: 4)

=== 二分图最大匹配 Bipartite Graph Maximum Matching Hungarian
#raw(read("../Cpp/网络流/二分图最大匹配Bipartite_Graph_Maximum_Matching_Hungarian.cpp"), lang: "cpp", tab-size: 4)

=== 二分图最大匹配 Bipartite Graph Maximum Matching Hopcroft-Karp
#raw(read("../Cpp/网络流/二分图最大匹配Bipartite_Graph_Maximum_Matching_Hopcroft-Karp.cpp"), lang: "cpp", tab-size: 4)

== 计算几何
=== 计算几何Compuational_Geometry
#raw(read("../Cpp/计算几何/计算几何Compuational_Geometry.cpp"), lang: "cpp", tab-size: 4)

=== 圆的K次面积交K-Intersection_Area_of_Circles
#raw(read("../Cpp/计算几何/圆的K次面积交K-Intersection_Area_of_Circles.cpp"), lang: "cpp", tab-size: 4)

=== 构造凸包+旋转卡壳Graham_Scan+Rotating_Calipers
#raw(read("../Cpp/计算几何/构造凸包+旋转卡壳Graham_Scan+Rotating_Calipers.cpp"), lang: "cpp", tab-size: 4)

== 优化算法
=== wqs二分+决策单调性dp
#raw(read("../Cpp/优化算法/wqs二分+决策单调性dp.cpp"), lang: "cpp", tab-size: 4)

=== 斜率优化Slope_Optimization
#raw(read("../Cpp/优化算法/斜率优化Slope_Optimization.cpp"), lang: "cpp", tab-size: 4)

== 离线算法
=== 莫队算法Mo
#raw(read("../Cpp/离线算法/莫队算法Mo.cpp"), lang: "cpp", tab-size: 4)

=== 线段树分治Segment_Tree_Partition
#raw(read("../Cpp/离线算法/线段树分治Segment_Tree_Partition.cpp"), lang: "cpp", tab-size: 4)

== 杂项
=== 快读快写Fast_Read&Write
#raw(read("../Cpp/杂项/快读快写Fast_Read&Write.cpp"), lang: "cpp", tab-size: 4)

=== 快速幂Fast_Power
#raw(read("../Cpp/杂项/快速幂Fast_Power.cpp"), lang: "cpp", tab-size: 4)

=== 矩阵快速幂Matrix_Fast_Power
#raw(read("../Cpp/杂项/矩阵快速幂Matrix_Fast_Power.cpp"), lang: "cpp", tab-size: 4)

=== 矩阵加速Matrix_Acceleration
#raw(read("../Cpp/杂项/矩阵加速Matrix_Acceleration.cpp"), lang: "cpp", tab-size: 4)

=== 最长公共子序列Longest_Increasing_Subsequence
#raw(read("../Cpp/杂项/最长公共子序列Longest_Increasing_Subsequence.cpp"), lang: "cpp", tab-size: 4)

=== 模拟退火Simulated_Annealing
#raw(read("../Cpp/杂项/模拟退火Simulated_Annealing.cpp"), lang: "cpp", tab-size: 4)

=== 快速沃尔什变换Fast_Walsh_Transform
#raw(read("../Cpp/杂项/快速沃尔什变换Fast_Walsh_Transform.cpp"), lang: "cpp", tab-size: 4)

=== 快速莫比乌斯变换Fast_Mobius_Transform
#raw(read("../Cpp/杂项/快速莫比乌斯变换Fast_Mobius_Transform.cpp"), lang: "cpp", tab-size: 4)

=== 快速子集变换Fast_Subset_Transform
#raw(read("../Cpp/杂项/快速子集变换Fast_Subset_Transform.cpp"), lang: "cpp", tab-size: 4)

=== 24点24_Point
#raw(read("../Cpp/杂项/24点24_Point.cpp"), lang: "cpp", tab-size: 4)

= Rust模板
== 工具
=== 读入Read
#raw(read("../Rust/工具/读入Read.rs"), lang: "rust", tab-size: 4)
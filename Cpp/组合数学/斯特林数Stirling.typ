==== 第一类斯特林数
<第一类斯特林数>
（斯特林轮换数）

$mat(delim: "[", n; k)$ 表示将 $n$ 个两两不同的元素，划分为 $k$
个非空圆排列的方案数。

递推式

$ mat(delim: "[", n; k) = mat(delim: "[", n - 1; k - 1) + (n - 1) mat(delim: "[", n - 1; k) $

边界是 $mat(delim: "[", n; 0) = [n = 0]$ 。

==== 第二类斯特林数
<第二类斯特林数>
（斯特林子集数）

$mat(delim: "{", n; k)$ 表示将 $n$ 个两两不同的元素，划分为 $k$
个非空子集的方案数。

递推式

$ mat(delim: "{", n; k) = mat(delim: "{", n - 1; k - 1) + k mat(delim: "{", n - 1; k) $

边界是 $mat(delim: "{", n; 0) = [n = 0]$ 。

==== 上升幂与普通幂的相互转化
<上升幂与普通幂的相互转化>
我们记上升阶乘幂 $x^(overline(n)) = product_(k = 0)^(n - 1) (x + k)$ 。

则可以利用下面的恒等式将上升幂转化为普通幂：

$ x^(overline(n)) = sum_k mat(delim: "[", n; k) x^k $

如果将普通幂转化为上升幂，则有下面的恒等式：

$ x^n = sum_k mat(delim: "{", n; k) (- 1)^(n - k) x^(overline(k)) $

==== 下降幂与普通幂的相互转化
<下降幂与普通幂的相互转化>
我们记下降阶乘幂
$x^(underline(n)) = frac(x !, (x - n) !) = product_(k = 0)^(n - 1) (x - k)$
。

则可以利用下面的恒等式将普通幂转化为下降幂：

$ x^n = sum_k mat(delim: "{", n; k) x^(underline(k)) $

如果将下降幂转化为普通幂，则有下面的恒等式：

$ x^(underline(n)) = sum_k mat(delim: "[", n; k) (- 1)^(n - k) x^k $

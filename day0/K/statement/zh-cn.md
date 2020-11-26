{{ self.title() }}

{{ s('description') }}

给定一张 $n$ 个点 $m$ 条边的无向图。

对于 $\{1,2,\ldots,n\}$ 的某个子集 $A$，$A$ 的分数为：
1. 初始分数为 0；
2. 对于所有 $i\in A$， 分数加 $a_i$；
3. 对于所有边 $(u, v, k)$ 满足 $u\in A$ 并且 $v\in A$, 分数减 $k$；

现在请你计算出所有的 $A$ 中，分数最高是多少。 

{{ s('input format') }}

{{ self.input_file() }}

令 $q = 101, b = 137, p = 1000000007$。

第一行包含六个整数 $n, m, x_0, y_0, a_0, z_0$ $(1\le n\le 100000,0\le m\le \frac{n}{2}, 0 \le x_0, y_0, r_0, z_0 < P)$。

对于 $1 \le i \le n$, 有 $a_i = (q\times a_{i-1} + b)\mod p$。

对于 $1 \le i \le m$, 有 $x_i = (q\times x_{i-1} + b)\mod p,y_i = (q\times y_{i-1} + b)\mod p, z_i = (q\times z_{i-1} + b)\mod p$。对于每一组 $(x_i, y_i, z_i)$ 描述了一条连接 $(x_i\mod n)+1,(y_i\mod n)+1$ 的值为 $z_i$ 的边，如果 $x_i=y_i$ 或者之前出现过连接$x_i$和$y_i$的边，则忽视这条边（即这条边不存在）。

{{ s('output format') }}

{{ self.output_file() }}

输出一行一个整数表示最高分数。

{{ s('sample', 1) }}

{{ self.sample_text() }}

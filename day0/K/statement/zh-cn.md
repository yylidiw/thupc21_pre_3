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

第一行包含两个整数 $n, m$ $(1\le n\le 100000,1\le m\le \frac{n}{2})$。

接下来一行包含 $n$ 个整数 $a_1,a_2,\ldots,a_n$ $(1\le a_i\le 1000000000)$。

接下来 $m$ 行，每行三个整数 $ u,v,k~(1\leq u,v \leq n, u \neq v,1\le k\le 1000000000)$，描述了一条连接 $u,v$ 的值为 $k$ 的边。

数据保证所有的边都是随机生成的。

{{ s('output format') }}

{{ self.output_file() }}

输出一行一个整数表示最高分数。

{{ s('sample', 1) }}

{{ self.sample_text() }}

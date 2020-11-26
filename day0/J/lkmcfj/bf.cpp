#include <cstdio>

const int MAXN = 510, MAXK = 4, mod = 998244353;
int s[MAXN], n, k;
bool legal()
{
    for (int i = 0; i + k <= n; ++i)
    {
        int cur = 0;
        for (int j = i; j < i + k; ++j) cur = (cur << 1) | s[j];
        if (!s[cur]) return false;
    }
    return true;
}
int dfs(int cur)
{
    if (cur == n) return legal() ? 1 : 0;
    s[cur] = 0;
    int ret = dfs(cur + 1);
    s[cur] = 1;
    ret = (ret + dfs(cur + 1)) % mod;
    return ret;
}
int main()
{
    scanf("%d%d", &n, &k);
    int ans = dfs(0);
    printf("%d\n", ans);
}
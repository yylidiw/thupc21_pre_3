#include <cstdio>
#include <cstdlib>

const int MAXN = 500, MAXK = 4;
const int mod = 998244353;
int dp[MAXN][1 << (MAXK - 1)];
bool legal[1 << MAXK];
int inverse(int mask, int w)
{
    int ret = 0;
    while (w--)
    {
        ret = (ret << 1) | (mask & 1);
        mask >>= 1;
    }
    return ret;
}
int solve(int n, int k, int start_segment)
{
    for (int j = 0; j < (1 << (k - 1)); ++j) dp[(1 << k) - 1][j] = 0;
    dp[(1 << k) - 1][start_segment] = 1;
    for (int i = (1 << k); i < n; ++i)
    {
        for (int j = 0; j < (1 << (k - 1)); ++j)
        {
            dp[i][j] = 0;
            if (legal[j]) dp[i][j] = dp[i - 1][j >> 1];
            if (legal[j | (1 << (k - 1))]) dp[i][j] = (dp[i][j] + dp[i - 1][(j | (1 << (k - 1))) >> 1]) % mod;
        }
    }
    int ret = 0;
    for (int j = 0; j < (1 << (k - 1)); ++j)
        ret = (ret + dp[n - 1][j]) % mod;
    return ret;
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int bound_bits = 1 << k;
    int ans = 0;
    for (int mask = 0; mask < (1 << bound_bits); ++mask)
    {
        for (int i = 0; i < bound_bits; ++i)
            legal[i] = ((mask >> i) & 1);
        bool flag = true;
        for (int i = 0; i < bound_bits - k; ++i)
        {
            int cur_segment = ((mask >> i) & ((1 << k) - 1));
            cur_segment = inverse(cur_segment, k);
            if (!legal[cur_segment])
            {
                flag = false;
                break;
            }
        }
        if (flag)  ans = (ans + solve(n, k, inverse(mask >> (bound_bits - k + 1), k - 1))) % mod;
    }
    printf("%d\n", ans);
}
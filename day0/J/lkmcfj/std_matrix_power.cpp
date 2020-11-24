#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stdexcept>

using std::vector;
const int MAXK = 4;
const int mod = 998244353;
typedef long long ll;
struct Matrix
{
    int n;
    int data[1 << (MAXK - 1)][1 << (MAXK - 1)];
    static Matrix I(int n)
    {
        Matrix ret;
        ret.n = n;
        memset(ret.data, 0, sizeof(ret.data));
        for (int i = 0; i < n; ++i) ret.data[i][i] = 1;
        return ret;
    }
};
Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.n != rhs.n) throw std::runtime_error("lhs.n != rhs.n");
    Matrix ret;
    ret.n = lhs.n;
    memset(ret.data, 0, sizeof(ret.data));
    for (int i = 0; i < ret.n; ++i)
        for (int j = 0; j < ret.n; ++j)
            for (int k = 0; k < ret.n; ++k)
                ret.data[i][k] = (ret.data[i][k] + static_cast<ll>(lhs.data[i][j]) * rhs.data[j][k]) % mod;
    return ret;
}

int n, k;
bool valid(const vector<int> &start_bits)
{
    int cur_seg = 0;
    for (size_t i = 0; i < k - 1; ++i) cur_seg = (cur_seg << 1) | start_bits[i];
    for (size_t i = k - 1; i < start_bits.size(); ++i)
    {
        cur_seg = (cur_seg << 1) | start_bits[i];
        cur_seg &= ((1 << k) - 1);
        if (!start_bits[cur_seg]) return false;
    }
    return true;
}
Matrix transfer_matrix(const vector<int> &start_bits)
{
    Matrix ret;
    ret.n = 1 << (k - 1);
    memset(ret.data, 0, sizeof(ret.data));
    for (int j = 0; j < ret.n; ++j)
    {
        if (start_bits[j << 1])
            ret.data[(j << 1) & ((1 << (k - 1)) - 1)][j] += 1;
        if (start_bits[(j << 1) | 1])
            ret.data[((j << 1) | 1) & ((1 << (k - 1)) - 1)][j] += 1;
    }
    return ret;
}
Matrix qp(const Matrix &x, int y)
{
    if (y == 0) return Matrix::I(x.n);
    int w = 0;
    while ((y >> w) > 1) ++w;
    Matrix ret = x;
    while (w > 0)
    {
        --w;
        ret = ret * ret;
        if ((y >> w) & 1) ret = ret * x;
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &k);
    int ans = 0;
    for (int mask = 0; mask < (1 << (1 << k)); ++mask)
    {
        vector<int> start_bits;
        for (int i = 0; i < (1 << k); ++i) start_bits.push_back((mask >> i) & 1);
        if (valid(start_bits))
        {
            Matrix A = transfer_matrix(start_bits);
            Matrix res = qp(A, n - (1 << k));
            int start_state = 0;
            for (size_t i = start_bits.size() - (k - 1); i < start_bits.size(); ++i)
                start_state = (start_state << 1) | start_bits[i];
            for (int i = 0; i < (1 << (k - 1)); ++i)
                ans = (ans + res.data[i][start_state]) % mod;
        }
    }
    printf("%d\n", ans);
}
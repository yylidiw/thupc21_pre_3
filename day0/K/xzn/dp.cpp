#include<vector>
#include<set>
#include<map>
#include<queue>
#include<string>
#include<algorithm>
#include<iostream>
#include<bitset>
#include<functional>
#include<numeric>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<cmath>
#include<iomanip>
#include<random>
#include<ctime>
#include<complex>
using namespace std;
typedef long long LL;
typedef double D;
#define all(v) (v).begin(), (v).end()
mt19937 gene(233);
typedef complex<double> Complex;
#define fi first
#define se second
#define ins insert
#define pb push_back
inline char GET_CHAR(){
    const int maxn = 131072;
    static char buf[maxn],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,maxn,stdin),p1==p2)?EOF:*p1++;
}
inline int getInt() {
    int res(0);
    char c = getchar();
    while(c < '0') c = getchar();
    while(c >= '0') {
        res = res * 10 + (c - '0');
        c = getchar();
    }
    return res;
}

inline LL fastpo(LL x, LL n, LL mod) {
    LL res(1);
    while(n) {
        if(n & 1) {
            res = res * (LL)x % mod;
        }
        x = x * (LL) x % mod;
        n /= 2;
    }
    return res;
}
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

inline string itoa(int x, int width = 0) {
    string res;
    if(x == 0) res.push_back('0');
    while(x) {
        res.push_back('0' + x % 10);
        x /= 10;
    }
    while((int)res.size() < width) res.push_back('0');
    reverse(res.begin(), res.end());
    return res;
}
const int _B = 131072;
char buf[_B];
int _bl = 0;
inline void flush() {
    fwrite(buf, 1, _bl, stdout);
    _bl = 0;
}
__inline void _putchar(char c) {
    if(_bl == _B) flush();
    buf[_bl++] = c;
}
inline void print(LL x, char c) {
    static char tmp[20];
    int l = 0;
    if(!x) tmp[l++] = '0';
    else {
        while(x) {
            tmp[l++] = x % 10 + '0';
            x /= 10;
        }
    }
    for(int i = l - 1; i >= 0; i--) _putchar(tmp[i]);
    _putchar(c);
}
struct P {
    D x, y;
};
const int N = 100033;
const int LOG = 20;
const int mod = 1e9 + 7;
const int inf = 1e9 + 7;
int n, m;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
set<int> mp[N];
int x[N], y[N], a[N], vst[N], idmask[N], dep[N], z[N], fa[N], id[N], fap[N];
vector<pair<int, int> > e[N];
LL dp[N][128][2];
int main() {
    int q = 101, b = 137, p = 1000000007;
    int n, m;
    scanf("%d%d%d%d%d%d", &n, &m, &x[0], &y[0], &a[0], &z[0]);
    for(int i = 1; i <= n; i++) {
        a[i] = (a[i - 1] * (LL)q + b) % p;
        x[i] = (x[i - 1] * (LL)q + b) % p;
        y[i] = (y[i - 1] * (LL)q + b) % p;
        z[i] = (z[i - 1] * (LL)q + b) % p;
    }
    for(int i = 1; i <= m; i++) {
        int x = ::x[i];
        int y = ::y[i];
        int z = ::z[i];
        x = x % n + 1;
        y = y % n + 1;
        if(x != y && mp[x].count(y) == 0) {
            //printf("%d %d %d\n", x, y, z);
            e[x].pb({y, z});
            e[y].pb({x, z});
            mp[x].insert(y);
            mp[y].insert(x);
        }
    }
    int np = 0;
    LL ans = 0;
    memset(dp, 0x80, sizeof(dp));
    for(int i = 1; i <= n; i++) {
        if(vst[i]) continue;
        vector<pair<int, int> > st;
        vector<int> q;
        st.pb(make_pair(i, 0));
        q.pb(i);
        vst[i] = 1;
        while(!st.empty()) {
            int v = st.back().fi, p = st.back().se++;
            if(p < (int)e[v].size()) {
                auto tmp = e[v][p];
                int y = tmp.fi, z = tmp.se;
                if(!vst[y]) {
                    fa[y] = v;
                    dep[y] = dep[v] +1;
                    fap[y] = z;
                    st.pb(make_pair(y, 0));
                    q.pb(y);
                    vst[y] = 1;
                }else if(y != fa[v] && dep[y] < dep[v]) {
                    if(id[v] == 0) {
                        id[v] = ++np;
                        idmask[v] |= 1 << (id[v] - 1);
                    }
                }
            }else {
                st.pop_back();
            }
        }
        reverse(all(q));
        for(int v : q) {
            for(auto tmp : e[v]) {
                int y = tmp.fi;
                if(fa[y] == v) {
                    idmask[v] |= idmask[y];
                }
            }
            for(int msk = idmask[v]; msk >= 0; msk = (msk - 1) & idmask[v]) {

                dp[v][msk][0] = dp[v][msk][1] = 0;
                LL pd[2] = {0, a[v]};
                for(auto tmp : e[v]) {
                    int y = tmp.fi, z = tmp.se;
                    //cout << y << ' ' << v << ' ' << dep[y] << ' ' << dep[v] << ' '<< fa[y] << endl;
                    if(fa[y] == v) {
                        pd[0] += max(dp[y][msk & idmask[y]][0], dp[y][msk & idmask[y]][1]);
                        pd[1] += max(dp[y][msk & idmask[y]][0], dp[y][msk & idmask[y]][1] - z);
                    }else if(dep[y] > dep[v]) {
                        //cout << "??" << endl;
                        //cout << 1 << (-1) << endl;
                        if(id[y] > 0 && (msk & (1 << (id[y] - 1)))) {
                            dp[v][msk][1] -= z;
                        }
                    }
                }
                dp[v][msk][0] += pd[0];
                dp[v][msk][1] += pd[1];
                if(id[v] > 0) {
                    dp[v][msk][((msk >> (id[v] - 1)) & 1) ^ 1] = (LL)inf * -inf;
                }
                if(msk == 0) break;
            }
    
        }
        LL mx = 0;
        for(int msk = 0; msk < (1 << np); msk++) {
            mx = max(mx, max(dp[q.back()][msk][0], dp[q.back()][msk][1]));

        }
        //cout << "mx = " << mx << endl;
        ans += mx;
    }
    cout << ans << endl;
//    cout << np << endl;
    
    
}





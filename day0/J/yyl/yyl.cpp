#include<cstdio>
#include<iostream>
#include<cstring>
#define rep(i,j,k) for(int i = j; i <= k; i++)
#define ll long long
using namespace std;

inline int read() {
    int s = 0, t = 1; char c = getchar();
    while( !isdigit(c) ) { if( c == '-' ) t = -1; c = getchar(); }
    while( isdigit(c) ) s = s * 10 + c - 48, c = getchar();
    return s * t;
}

const int K = 4, N = 505;
const int K_mask = 1 << K;
const int Km_mask = 1 << (K-1);
const int mod = 998244353;

int n, k, k_mask, km_mask, ti = 0;
ll f[N][Km_mask], ans = 0;
int t[N][Km_mask];
bool val[K_mask];
bool flag[K_mask];

void _(ll &x) {
    while( x >= mod ) x -= mod;
    while( x < 0 ) x += mod;
}

void update(int n, int k, int v) {
    if( t[n][k] == ti ) {
        _(f[n][k] += v);
    } else {
        f[n][k] = v;
        t[n][k] = ti;
    }
}

void solve(int now) {
    if( now == k_mask + 1 ) {
        memset(flag,0,sizeof(flag));
        for(int i = 0; i <= k_mask; i++) {
            flag[i] = 1 ^ val[i];
        }
        
        int now = 0;
        for(int i = 0; i <= k - 2; i++) {
            now = now << 1 | val[i];
        }

        /*
        cout<<"In: ";
        for(int i = 0; i <= k_mask; i++) {
            cout<<val[i]<<" ";
        } cout<<endl;

        cout<<"Flag: ";
        for(int i = 0; i <= k_mask; i++)
            cout<<flag[i]<<" ";
        cout<<endl;
        */

        for(int i = k-1; i <= k_mask; i++) {
            now = now << 1 | val[i];
            if( flag[now] ) return;
            now = now & km_mask;
        }

        //cout<<"Pass "<<endl;

        ti++;
        update(k_mask, now, 1);
        for(int i = k_mask; i <= n - 2; i++) {
            for(int j = 0; j <= km_mask; j++) {
                if( !f[i][j] || t[i][j] != ti ) continue;
                int t0 = j << 1 | 0;
                if( !flag[t0] ) {
                    update(i+1, t0 & km_mask, f[i][j]);
                }
                int t1 = j << 1 | 1;
                if( !flag[t1] ) {
                    update(i+1, t1 & km_mask, f[i][j]);
                }
            }
        }

        for(int j = 0; j <= km_mask; j++)
            if( t[n-1][j] == ti ) _(ans += f[n-1][j]);
        //cout<<"E "<<ans<<endl;
        return;
    }
    for(int i = 0; i <= 1; i++) {
        val[now] = i;
        solve(now+1);
    }
}

int main() {
    n = read(), k = read(), k_mask = (1 << k) - 1;
    km_mask = (1 << (k-1)) - 1;
    solve(0);
    cout<<ans<<endl;
}
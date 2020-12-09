//#define Test
#include<bits/stdc++.h>
using namespace std;
const int Nmax=1e5+7;
typedef long long ll;
const ll INF=(ll)1e18+(ll)7;
typedef pair<ll,ll> pll;
map<pll,ll> mp;
ll a[Nmax],ans;
ll dp[Nmax][256][2];
int fa[Nmax], vis[Nmax], deep[Nmax], id[Nmax], mask[Nmax];
vector<pll> e[Nmax];
vector<pair<int, int> > st;
vector<int> q;
inline ll nxt(ll x)
{
    ll q=101,b=137,p=1000000007;
    return (q*x%p+b)%p;
}
inline void init()
{
    ans=0;
    st.clear();
    q.clear();
    memset(dp, 256, sizeof(dp));
}
int main()
{
    ll n,m,x0,y0,z0;
    cin>>n>>m>>x0>>y0>>a[0]>>z0;

    for(int i=1; i<=n; i++)
        a[i]=nxt(a[i-1]);

    //int ttt=0;
    for(int i=1; i<=m; i++)
    {
        x0=nxt(x0);
        y0=nxt(y0);
        z0=nxt(z0);
        ll x,y;
        x=x0%n+1;
        y=y0%n+1;

        if(x>y)
            swap(x,y);

        if(x==y || mp.count(pll(x, y)))
            continue;

        mp[pll(x, y)]=z0;
        e[x].push_back(pll(y,z0));
        e[y].push_back(pll(x,z0));
        //ttt++;
    }

    //cout<<ttt<<endl;
    init();
    int sz=0;

    for(int i = 1; i <= n; i++)
    {
        if(vis[i])
            continue;

        q.clear();
        st.clear();
        st.push_back(make_pair(i, 0));
        q.push_back(i);
        vis[i] = 1;

        while(!st.empty())
        {
            int v = st.back().first, p = st.back().second++;

            if(p < e[v].size())
            {
                int y = e[v][p].first;

                if(!vis[y])
                {
                    vis[y] = 1;
                    fa[y] = v;
                    deep[y] = deep[v] +1;
                    st.push_back(make_pair(y, 0));
                    q.push_back(y);
                }
                else if(y != fa[v] && deep[y] < deep[v] && !id[v])
                {
                    id[v] = ++sz;
                    mask[v] |= 1 << (id[v] - 1);
                }
            }
            else
                st.pop_back();
        }

        for(auto it=q.rbegin(); it!=q.rend(); it++)
        {
            int v=*it;
            for(auto tmp : e[v])
            {
                int y = tmp.first;

                if(v == fa[y])
                    mask[v] |= mask[y];
            }

            for(int msk = mask[v]; msk >= 0; msk = (msk - 1) & mask[v])
            {
                ll vx = 0, vy = a[v];
                dp[v][msk][0] = dp[v][msk][1] = 0;

                for(auto now : e[v])
                {
                    int y = now.first;
                    ll z = now.second;

                    if(v == fa[y])
                    {
                        vx += max(dp[y][msk & mask[y]][0], dp[y][msk & mask[y]][1]);
                        vy += max(dp[y][msk & mask[y]][0], dp[y][msk & mask[y]][1] - z);
                    }
                    else if(deep[y] > deep[v] && id[y]>0 && (msk & (1 << (id[y] - 1))))
                        dp[v][msk][1] -= z;
                }

                dp[v][msk][0] += vx;
                dp[v][msk][1] += vy;

                if(id[v] > 0)
                    dp[v][msk][((msk >> (id[v] - 1)) & 1) ^ 1] = (ll)-INF;

                if(!msk)
                    break;
            }

        }

        ll maxx = 0;
        int now=q.front();
        for(int msk = 0; msk < (1 << sz); msk++)
        {
            maxx = max(maxx, dp[now][msk][0]);
            maxx = max(maxx, dp[now][msk][1]);
        }

        ans += maxx;
    }

    cout << ans << endl;

    return 0;
}



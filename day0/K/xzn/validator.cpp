#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct node {
  node *next;
  int where, v;
} *first[100001], a[100001];

int n, m, l, v[100001], c[100001], dist[100001], w[100001], cnt, father[100001], idx[100001], sx[100001];
bool b[100001];
long long f[100001][2];
set < pair<int, int> > events;

inline void makelist(int x, int y, int z) {
  a[++l].where = y; a[l].v = z; a[l].next = first[x]; first[x] = &a[l];
}

int uu = 0;

long long calc(int init) {
  dist[init] = 1; c[1] = init; cnt = 0;
  int k = 1;
  for (int l = 1; l <= k; l++) {
    int m = c[l];
    for (node *x = first[m]; x; x = x->next)
      if (!dist[x->where])
        dist[x->where] = dist[m] + 1, c[++k] = x->where, father[x->where] = m, sx[x->where] = k;
      else
        if (father[m] != x->where && sx[x->where] >= sx[m])
          w[++cnt] = x->where;
  }
  sort(w + 1, w + cnt + 1);
  uu += cnt;
  int tot = 0;
  for (int i = 1; i <= cnt; i++)
    if (i == 1 || w[i] != w[tot])
      w[++tot] = w[i];
  for (int i = 1; i <= tot; i++)
    idx[w[i]] = i;
  long long res = 0;
  for (int i = 0; i < 1 << tot; i++) {
    for (int j = k; j; --j) {
      int m = c[j];
      f[m][0] = 0; f[m][1] = v[m];
      if (idx[m])
        if (i & (1 << (idx[m] - 1)))
          f[m][0] = -1LL << 60LL;
        else
          f[m][1] = -1LL << 60LL;
      for (node *x = first[m]; x; x = x->next)
        if (sx[x->where] >= sx[m]) {
          if (father[x->where] == m) {
            f[m][0] += max(f[x->where][0], f[x->where][1]);
            f[m][1] += max(f[x->where][0], f[x->where][1] - x->v);
          } else 
            if (idx[x->where] && (i & (1 << (idx[x->where] - 1))))
              f[m][1] -= x->v;
        }
      //printf("%d %lld %lld\n", m, f[m][0], f[m][1]);
    }
    res = max(res, max(f[init][0], f[init][1]));
  }
  return res;
}

long long calcs(long long x) {
  int P = 1000000007, xs = 101, ex = 137;
  return (xs * x + ex) % P;
}

int main() {
  int x, y, z, r;
  scanf("%d%d%d%d%d%d", &n, &m, &x, &y, &r, &z);
  assert(n>=1);
  assert(n<=100000);
  assert(m>=0);
  assert(m<=n/2);
  assert(x<1000000007);
  assert(y<1000000007);
  assert(r<1000000007);
  assert(z<1000000007);
  assert(x>=0);
  assert(y>=0);
  assert(r>=0);
  assert(z>=0);
  for (int i = 1; i <= n; i++) {
    r = calcs(r);
    v[i] = r;
  }
  for (int i = 1; i <= m; i++) {
    x = calcs(x);
    y = calcs(y);
    z = calcs(z);
    int cx = x % n + 1, cy = y % n + 1;
    if (cx != cy && events.find(make_pair(cx, cy)) == events.end())
        makelist(cx, cy, z), makelist(cy, cx, z), 
        events.insert(make_pair(cx, cy)),
        events.insert(make_pair(cy, cx));
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++)
    if (!dist[i])
      ans += calc(i);
  printf("%lld\n", ans);
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
 
using namespace std;
 
const int MAXC = 25;
const int MAXN = 20000 + 10;
 
int n, Q, a[MAXN], tot[MAXC][MAXC][MAXN], b[MAXN], qu[MAXN][3], pn, st[MAXC], en[MAXC], belong[MAXN], num[MAXC][MAXC], cnt[MAXN], sss;
char opr[5];
 
int Query(int l, int r)
{
    int cl = belong[l], cr = belong[r];
    int res = 0;
    if (cr - cl < 2)
    {
        for (int i = l; i <= r; ++i)
        {
            if (!cnt[a[i]]) ++res;
            cnt[a[i]]++;
        }
        for (int i = l; i <= r; ++i) cnt[a[i]] = 0;
        return res;
    }
    res = num[cl + 1][cr - 1];
    for (int i = l; i <= en[cl]; ++i)
    {
        if (!cnt[a[i]]) cnt[a[i]] += tot[cl + 1][cr - 1][a[i]];
        if (!cnt[a[i]]) ++res;
        cnt[a[i]]++;
    }
    for (int i = st[cr]; i <= r; ++i)
    {
        if (!cnt[a[i]]) cnt[a[i]] += tot[cl + 1][cr - 1][a[i]];
        if (!cnt[a[i]]) ++res;
        cnt[a[i]]++;
    }
    for (int i = l; i <= en[cl]; ++i) cnt[a[i]] = 0;
    for (int i = st[cr]; i <= r; ++i) cnt[a[i]] = 0;
    return res;
}
 
void Update(int p, int d)
{
    int x = belong[p];
    for (int i = 1; i <= x; ++i)
        for (int j = x; j <= pn; ++j)
        {
            --tot[i][j][a[p]];
            if (!tot[i][j][a[p]]) --num[i][j];
        }
    a[p] = d;
    for (int i = 1; i <= x; ++i)
        for (int j = x; j <= pn; ++j)
        {
            if (!tot[i][j][a[p]]) ++num[i][j];
            ++tot[i][j][a[p]];
        }
}
 
int main()
{
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), b[++sss] = a[i];
    for (int i = 1; i <= Q; ++i)
    {
        scanf("%s", opr);
        scanf("%d%d", &qu[i][1], &qu[i][2]);
        if (opr[0] == 'R') qu[i][0] = 1; else qu[i][0] = 0;
        if (qu[i][0]) b[++sss] = qu[i][2];
    }
    sort(b + 1, b + 1 + sss);
    sss = unique(b + 1, b + 1 + sss) - b - 1;
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + sss, a[i]) - b - 1;
    for (int i = 1; i <= Q; ++i) if (qu[i][0]) qu[i][2] = lower_bound(b + 1, b + 1 + sss, qu[i][2]) - b - 1;
    while (pn * pn * pn <= n) ++pn;
    int sz = n / pn;
    for (int i = 1; i <= pn; ++i)
    {
        st[i] = (i - 1) * sz + 1;
        en[i] = i * sz;
    }
    en[pn] = n;
    for (int i = 1; i <= pn; ++i)
        for (int j = st[i]; j <= en[i]; ++j) belong[j] = i;
    for (int i = 1; i <= pn; ++i)
        for (int j = i; j <= pn; ++j)
            for (int k = st[i]; k <= en[j]; ++k)
            {
                if (tot[i][j][a[k]] == 0) ++num[i][j];
                ++tot[i][j][a[k]];
            }
    for (int i = 1; i <= Q; ++i)
    {
        if (qu[i][0]) Update(qu[i][1], qu[i][2]);
        else printf("%d\n", Query(qu[i][1], qu[i][2]));
    }
     
    return 0;
}

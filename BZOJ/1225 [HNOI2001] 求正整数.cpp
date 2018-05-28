#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 100000 + 10;
const int BASE = 100000;
const int MAXM = 50;
 
struct BigNum
{
    int a[MAXN], len;
    BigNum() {memset(a, 0, sizeof(a)); len = 1;}
    void Mul(int b)
    {
        for (int i = 1; i <= len; ++i) a[i] *= b;
        for (int i = 1; i <= len; ++i)
        {
            a[i + 1] += a[i] / BASE;
            a[i] %= BASE;
            if (a[len + 1]) ++len;
        }
    }
    void Print()
    {
        printf("%d", a[len]);
        for (int i = len - 1; i; --i) printf("%05d", a[i]);
        putchar('\n');
    }
} ans;
 
int times[MAXM], anst[MAXM], prm[MAXM], Top, n;
double d[MAXM], best = 1e100;
bool vis[MAXM];
 
void dfs(int dep, int now, double T)
{
    if (T > best) return;
    if (now == 1)
    {
        best = T;
        for (int i = 1; i <= Top; ++i) anst[i] = times[i];
        return;
    }
    for (int i = 1; i < now; ++i) if (now % (i + 1) == 0)
    {
        int tmp = times[dep];
        times[dep] = i;
        dfs(dep + 1, now / (i + 1), T + d[dep] * i);
        times[dep] = tmp;
    }
}
 
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= 47; ++i)
    {
        if (!vis[i]) prm[++Top] = i;
        for (int j = 1; j <= Top && i * prm[j] <= 47; ++j)
        {
            vis[i * prm[j]] = 1;
            if (i % prm[j] == 0) break;
        }
    }
    for (int i = 1; i <= Top; ++i) d[i] = log(prm[i]);
    dfs(1, n, 0);
    ans.a[1] = 1;
    for (int i = 1; i <= Top; ++i)
        for (int j = 1; j <= anst[i]; ++j) ans.Mul(prm[i]);
    ans.Print();
     
    return 0;
}

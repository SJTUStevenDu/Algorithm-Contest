#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 300 + 10;
 
int T, n, m;
bool a[MAXN][MAXN];
 
bool check()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            bool f1, f2;
            f1 = f2 = false;
            for (int k = 1; k <= n; ++k)
            {
                if (a[i][k] && a[j][k]) f1 = true;
                if ((a[i][k] ^ a[j][k])) f2 = true;
                if (f1 && f2) return false;
            }
        }
    return true;
}
 
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        for (int x, y, i = 1; i <= m; ++i)
        {
            scanf("%d%d", &x, &y);
            ++x; ++y;
            a[x][y] = 1;
        }
        if (check()) puts("Yes");
        else puts("No");
    }
     
    return 0;
}

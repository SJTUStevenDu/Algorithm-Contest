#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <bitset>
 
using namespace std;
 
const int MAXN = 1000 + 10;
 
bitset <100> a[MAXN][MAXN], b[MAXN];
int n, m, Q, r, c, p[MAXN];
 
int main()
{
    scanf("%d%d%d%d", &n, &m, &r, &c);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            scanf(" ");
            if (i >= r)
            {
                a[i][j] = a[i - 1][j] >> 1;
                a[i][j][r - 1] = (getchar() == '1');
            }
            else a[r - 1][j][i] = (getchar() == '1');
        }
    scanf("%d", &Q);
    if (r > n || c > m)
    {
        while (Q--) puts("0");
        return 0;
    }
    while (Q--)
    {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
            {
                scanf(" ");
                b[j][i] = (getchar() == '1');
            }
        p[1] = 0;
        for (int i = 2, j = 0; i <= c; ++i)
        {
            for (; j && b[i - 1] != b[j]; j = p[j]);
            p[i] = j += (b[j] == b[i - 1]);
        }
        bool ans = false;
        for (int i = r - 1; !ans && i < n; ++i)
            for (int j = 1, k = 0; j <= m && !ans; ++j)
            {
                for (; k && a[i][j - 1] != b[k]; k = p[k]);
                k += (a[i][j - 1] == b[k]);
                if (k == c) ans = true;
            }
        if (ans) puts("1"); else puts("0");
    }
     
    return 0;
}

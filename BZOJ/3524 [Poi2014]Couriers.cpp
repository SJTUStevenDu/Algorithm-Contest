#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
 
using namespace std;
 
const int MAXN = 500000 + 10;
 
int a[MAXN], n, Q, l, r;
vector <int> pos[MAXN];
 
inline int Find(int x, int p)
{
    int l = 0, r = pos[x].size() - 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (pos[x][mid] > p) r = mid - 1;
        else l = mid + 1;
    }
    return r + 1;
}
 
int main()
{
    scanf("%d", &n); scanf("%d", &Q);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) pos[i].push_back(0);
    for (int i = 1; i <= n; ++i) pos[a[i]].push_back(i);
    for (int i = 1; i <= n; ++i) pos[i].push_back(n + 1);
    for (int i = 1; i <= Q; ++i)
    {
        scanf("%d%d", &l, &r);
        int p = l, d = max((r - l + 1) / 19, 1), ans = 0;
        for (int t = 1; p <= r; ++t, p += d)
        {
            int x = a[p];
//          cerr<<Find(x, r)<<" "<<Find(x, l - 1)<<endl;
            if (Find(x, r) - Find(x, l - 1) > (r - l + 1) / 2)
            {
                ans = x;
                break;
            }
            if (t & 1) ++p;
        }
        printf("%d\n", ans);
    }
     
    return 0;
}

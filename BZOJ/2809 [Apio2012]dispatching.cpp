#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int MAXN = 100000 + 10;
 
struct Leftist_Tree
{
    int dist, cnt, left, right;
    long long sum;
} tree[MAXN];
 
struct Edge
{
    int next, to;
} g[MAXN];
int start[MAXN], gn;
 
inline void AddEdge(int a, int b)
{
    gn++; g[gn].next = start[a]; start[a] = gn; g[gn].to = b;
}
 
int n;
long long Lim, lead[MAXN], sal[MAXN], ans;
 
int Merge(int A, int B)
{
    if (!A || !B) return A + B;
    if (sal[A] < sal[B]) swap(A, B);
    tree[A].right = Merge(tree[A].right, B);
    if (tree[tree[A].right].dist > tree[tree[A].left].dist) swap(tree[A].left, tree[A].right);
    tree[A].dist = tree[tree[A].right].dist + 1;
    tree[A].sum = tree[tree[A].left].sum + tree[tree[A].right].sum + sal[A];
    tree[A].cnt = tree[tree[A].left].cnt + tree[tree[A].right].cnt + 1;
    return A;
}
 
int dfs(int p)
{
    int x = p;
    tree[p].cnt = 1; tree[p].sum = sal[p];
    for (int i = start[p]; i; i = g[i].next) x = Merge(x, dfs(g[i].to));
    for (; tree[x].sum > Lim; x = Merge(tree[x].left, tree[x].right));
    ans = max(ans, (long long)tree[x].cnt * lead[p]);
    return x;
}
 
int main()
{
    scanf("%d%lld", &n, &Lim);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d%lld%lld", &x, &sal[i], &lead[i]);
        if (x) AddEdge(x, i);
    }
    tree[0].dist = -1;
    dfs(1);
    printf("%lld\n", ans);
     
    return 0;
}

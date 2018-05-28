#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 5000 + 10;

int n, A, B, C, Minh, Minw, Maxw, Maxk;
int ans, cnt, l, r, cw, ch;

struct Node
{
	int h, w, k;
} s[MAXN], sort_h[MAXN], sort_k[MAXN];

inline bool cmp1(Node A, Node B)
{
	return A.h > B.h;
}

inline bool cmp2(Node A, Node B)
{
	return A.k > B.k;
}

inline void update(int x)
{
	Minh = sort_h[x].h;
	Maxk = A * Minh + B * Minw + C;
	for (; r <= n && sort_h[r].h >= Minh; ++r)
		if (sort_h[r].w >= Minw && sort_h[r].w <= Maxw) ++cnt;
	for (; l <= n && sort_k[l].k > Maxk; ++l)
		if (sort_k[l].w >= Minw && sort_k[l].w <= Maxw) --cnt;
	ans=max(ans,cnt);
}

inline void Calc(int x)
{
	Minw = sort_h[x].w;
	Maxw = Minw + cw;
	l = 1; r = 1; cnt = 0;
	int i = 1;
	for(; i <= n && sort_h[i].h > sort_h[x].h + ch; ++i);
	for(; i <= n && sort_h[i].h >= sort_h[x].h - ch; ++i)
		if (sort_h[i].w >= Minw && sort_h[i].w <= Maxw) update(i); 
}

int main()
{
	scanf("%d%d%d%d", &n, &A, &B, &C);
	ch = C / A; cw = C / B;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d%d", &s[i].h, &s[i].w);
		s[i].k = A * s[i].h + B * s[i].w;
		sort_k[i] = s[i];
		sort_h[i] = s[i];
	}
	sort(sort_k + 1, sort_k + 1 + n, cmp2);
	sort(sort_h + 1, sort_h + 1 + n, cmp1);
	for (int i = 1; i <= n; ++i) Calc(i);
	printf("%d\n", ans);
	
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 170000 + 10;
const long long INF = (1LL << 60);

struct Node
{
	int left, right, idx;
	long long data;
}a[MAXN];
int num, tot;

int n, k, v[MAXN];
long long b[MAXN], ans;

inline void Update(int x) {v[a[x].idx] = x;}

void Up(int x)
{
	while (x > 1 && a[x].data < a[x / 2].data) 
	{
		swap(a[x], a[x / 2]);
		Update(x); Update(x / 2);
		x = x / 2;
	}
}

void Down(int x)
{
	while (x * 2 <= num)
	{
		int tmp = x * 2;
		if (tmp + 1 <= num && a[tmp].data > a[tmp + 1].data) tmp = tmp + 1;
		if (a[tmp].data < a[x].data) 
		{
			swap(a[tmp], a[x]);
			Update(tmp); Update(x);
			x = tmp;
		}
		else break;
	}
}

void Delete(int x)
{
	swap(a[x], a[num]); Update(x); Update(num); --num;
	Up(x); Down(x);
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]);
	for (int i = 1; i <= n + 1; ++i)
	{
		a[i].data = b[i] - b[i - 1];
		if (i != 1) a[i].left = i - 1; if (i != n + 1) a[i].right = i + 1; a[i].idx = i; v[i] = i;
	}
	a[1].data = a[n + 1].data = INF; num = tot = n + 1;
	for (int i = num / 2; i; --i) Down(i);
	while (k--)
	{
		ans += a[1].data;
		int l = a[1].left, r = a[1].right;
		long long tmpdata = a[v[l]].data + a[v[r]].data - a[1].data;
		++num; ++tot; 
		a[num].data = tmpdata; a[num].left = a[v[l]].left; a[num].right = a[v[r]].right;
		a[v[a[v[l]].left]].right = tot; a[v[a[v[r]].right]].left = tot; 
		v[tot] = num; a[num].idx = tot;
		Up(num);
		Delete(1);
		Delete(v[l]);
		Delete(v[r]);
	}
	printf("%lld\n", ans);
	
	return 0;
}

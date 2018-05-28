#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 20000 + 10;
const int INF = 1000000001;

int x[MAXN], y[MAXN], n, stk1[MAXN], Top1, stk2[MAXN], Top2;
bool vis[MAXN];

bool InRectangle(int x1, int y1, int x2, int y2, int sx, int sy)
{
	return sx >= x1 && sx <= x2 && sy >= y1 && sy <= y2;
}

inline void checkmin(int &x, int y) {if (x > y) x = y;}
inline void checkmax(int &x, int y) {if (x < y) x = y;}

bool check3(int L)
{
	int x1 = INF, x2 = -INF, y1 = INF, y2 = -INF;
	for (int i = 1; i <= n; ++i) if (!vis[i]) 
	{
		checkmin(x1, x[i]);
		checkmax(x2, x[i]);
		checkmin(y1, y[i]);
		checkmax(y2, y[i]);
	}
	if (x2 - x1 + 1 <= L && y2 - y1 + 1 <= L) return true;
	return false;
}

bool check2(int L)
{
	Top2 = 0;
	int x1 = INF, x2 = -INF, y1 = INF, y2 = -INF;
	for (int i = 1; i <= n; ++i) if (!vis[i]) 
	{
		checkmin(x1, x[i]);
		checkmax(x2, x[i]);
		checkmin(y1, y[i]);
		checkmax(y2, y[i]);
	}
	int x3, y3;
	x3 = x1 + L - 1; y3 = y1 + L - 1;
	for (int i = 1; i <= n; ++i) if (!vis[i] && InRectangle(x1, y1, x3, y3, x[i], y[i])) vis[i] = 1, stk2[++Top2] = i;
	if (check3(L)) return true; 
	while (Top2) {vis[stk2[Top2]] = 0; --Top2;}
	x3 = x1 + L - 1, y3 = y2 - L + 1;
	for (int i = 1; i <= n; ++i) if (!vis[i] && InRectangle(x1, y3, x3, y2, x[i], y[i])) vis[i] = 1, stk2[++Top2] = i;
	if (check3(L)) return true; 
	while (Top2) {vis[stk2[Top2]] = 0; --Top2;}
	x3 = x2 - L + 1, y3 = y1 + L - 1;
	for (int i = 1; i <= n; ++i) if (!vis[i] && InRectangle(x3, y1, x2, y3, x[i], y[i])) vis[i] = 1, stk2[++Top2] = i;
	if (check3(L)) return true; 
	while (Top2) {vis[stk2[Top2]] = 0; --Top2;}
	x3 = x2 - L + 1, y3 = y2 - L + 1;
	for (int i = 1; i <= n; ++i) if (!vis[i] && InRectangle(x3, y3, x2, y2, x[i], y[i])) vis[i] = 1, stk2[++Top2] = i;
	if (check3(L)) return true; 
	while (Top2) {vis[stk2[Top2]] = 0; --Top2;}
	return false;
}

bool check1(int L)
{
	Top1 = 0;
	int x1 = INF, x2 = -INF, y1 = INF, y2 = -INF;
	for (int i = 1; i <= n; ++i)
	{
		checkmin(x1, x[i]);
		checkmax(x2, x[i]);
		checkmin(y1, y[i]);
		checkmax(y2, y[i]);
	}
	int x3, y3;
	x3 = x1 + L - 1; y3 = y1 + L - 1;
	for (int i = 1; i <= n; ++i) if (InRectangle(x1, y1, x3, y3, x[i], y[i])) vis[i] = 1, stk1[++Top1] = i;
	if (check2(L)) return true; 
	while (Top1) {vis[stk1[Top1]] = 0; --Top1;}
	x3 = x1 + L - 1; y3 = y2 - L + 1;
	for (int i = 1; i <= n; ++i) if (InRectangle(x1, y3, x3, y2, x[i], y[i])) vis[i] = 1, stk1[++Top1] = i;
	if (check2(L)) return true; 
	while (Top1) {vis[stk1[Top1]] = 0; --Top1;}
	x3 = x2 - L + 1; y3 = y1 + L - 1;
	for (int i = 1; i <= n; ++i) if (InRectangle(x3, y1, x2, y3, x[i], y[i])) vis[i] = 1, stk1[++Top1] = i;
	if (check2(L)) return true; 
	while (Top1) {vis[stk1[Top1]] = 0; --Top1;}
	x3 = x2 - L + 1; y3 = y2 - L + 1;
	for (int i = 1; i <= n; ++i) if (InRectangle(x3, y3, x2, y2, x[i], y[i])) vis[i] = 1, stk1[++Top1] = i;
	if (check2(L)) return true; 
	while (Top1) {vis[stk1[Top1]] = 0; --Top1;}
	return false;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d%d", &x[i], &y[i]);
	int l = 1, r = INF;
	while (l <= r)
	{
		memset(vis, 0, sizeof(vis));
		int mid = (l + r) / 2;
		if (check1(mid)) r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", r);
	
	return 0;
}

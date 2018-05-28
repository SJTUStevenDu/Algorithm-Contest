#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 50;
const int dx[8] = {-2, -1, -2, -1, 1, 2, 1, 2};
const int dy[8] = {-1, -2, 1, 2, -2, -1, 2, 1};

int dist[MAXN][MAXN], q[MAXN * MAXN][2], head, tail;
int sx, sy, tx, ty, ans;
bool vis[MAXN][MAXN];

inline void check(int &x) {if (x < 0) x = -x;}

int main()
{
	scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
	tx -= sx; ty -= sy;
	check(tx); check(ty);
	while (tx > 20 || ty > 20)
	{
		if (tx >= 2 * ty) tx -= 2, --ty;
		else --tx, ty -= 2;
		check(tx); check(ty);
		++ans;
	}
	tx += 20; ty += 20;
	vis[20][20] = 1; q[head][0] = 20; q[head][1] = 20; tail = 1;
	while (head != tail)
	{
		int px = q[head][0], py = q[head][1];
		++head;
		for (int k = 0; k < 8; ++k)
		{
			int vx = px + dx[k], vy = py + dy[k];
			if (vx > 0 && vy > 0 && vx <= 40 && vy <= 40 && !vis[vx][vy]) 
			{
				dist[vx][vy] = dist[px][py] + 1;
				vis[vx][vy] = 1;
				q[tail][0] = vx;
				q[tail][1] = vy;
				++tail;
			}
		}
	}
	ans += dist[tx][ty];
	printf("%d\n", ans);
	
	return 0;
}

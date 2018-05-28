#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

bool vis[21][16][16][16][16][16];
int n;

int main()
{
	scanf("%d", &n);
	for (int a = 0; a < 16; ++a)
		for (int b = 0; b < 16; ++b) 
			for (int c = 0; c < 16; ++c) 
				for (int d = 0; d < 16; ++d)
					for (int e = 0; e < 16; ++e)
						for (int f = 0; f < 16; ++f)
							for (int g = 0; g < 16; ++g)
							{
								if (vis[0][a][b][c][d][e] || vis[1][a][b][c][d][f] || vis[2][a][b][c][d][g] || vis[3][a][b][c][e][f] || vis[4][a][b][c][e][g]
								 || vis[5][a][b][c][f][g] || vis[6][a][b][d][e][f] || vis[7][a][b][d][e][g] || vis[8][a][b][d][f][g] || vis[9][a][b][e][f][g]
								|| vis[10][a][c][d][e][f] || vis[11][a][c][d][e][g] || vis[12][a][c][d][f][g] || vis[13][a][c][e][f][g] || vis[14][a][d][e][f][g]
								|| vis[15][b][c][d][e][f] || vis[16][b][c][d][e][g] || vis[17][b][c][d][f][g] || vis[18][b][c][e][f][g] || vis[19][b][d][e][f][g]
								|| vis[20][c][d][e][f][g]) continue;
								--n;
								if (n == 0)
								{
									if (a < 10) printf("%d", a);
									else putchar(a - 10 + 'a');
									if (b < 10) printf("%d", b);
									else putchar(b - 10 + 'a');
									if (c < 10) printf("%d", c);
									else putchar(c - 10 + 'a');
									if (d < 10) printf("%d", d);
									else putchar(d - 10 + 'a');
									if (e < 10) printf("%d", e);
									else putchar(e - 10 + 'a');
									if (f < 10) printf("%d", f);
									else putchar(f - 10 + 'a');
									if (g < 10) printf("%d", g);
									else putchar(g - 10 + 'a');
									printf("\n");
									return 0;
								}
								vis[0][a][b][c][d][e] = vis[1][a][b][c][d][f] = vis[2][a][b][c][d][g] = vis[3][a][b][c][e][f] = vis[4][a][b][c][e][g]
								 = vis[5][a][b][c][f][g] = vis[6][a][b][d][e][f] = vis[7][a][b][d][e][g] = vis[8][a][b][d][f][g] = vis[9][a][b][e][f][g]
								= vis[10][a][c][d][e][f] = vis[11][a][c][d][e][g] = vis[12][a][c][d][f][g] = vis[13][a][c][e][f][g] = vis[14][a][d][e][f][g]
								= vis[15][b][c][d][e][f] = vis[16][b][c][d][e][g] = vis[17][b][c][d][f][g] = vis[18][b][c][e][f][g] = vis[19][b][d][e][f][g]
								= vis[20][c][d][e][f][g] = 1;
							}
	return 0;
}

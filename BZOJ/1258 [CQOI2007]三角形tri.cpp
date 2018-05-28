#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100 + 10;

char S[MAXN], tmp[MAXN];
int n, tot;
char ans[10][MAXN];
bool vis[4];

bool cmp(char A[], char B[])
{
	int len = max(A[0], B[0]);
	for (int i = 1; i <= len; ++i) if (A[i] != B[i]) return A[i] < B[i];
	return 1;
}

int main()
{
	scanf("%s", S + 1);
	n = strlen(S + 1);
	if (S[n] == '4') 
	{
		for (int i = 1; i <= 3; ++i) 
		{
			for (int j = 1; j < n; ++j) printf("%c", S[j]);
			printf("%c", i + '0');
			putchar('\n');
		}
		return 0;
	}
	for (int i = n; i > 1; --i) if (!vis[S[i] - '0'])
	{
		vis[S[i] - '0'] = 1;
		++tot;
		int len = 0;
		for (int j = 1; j < i; ++j) ans[tot][++ans[tot][0]] = S[j];
		ans[tot][++ans[tot][0]] = '4';
	}
	for (int i = 1; i <= tot; ++i)
		for (int j = 1; j < i; ++j) if (cmp(ans[i], ans[j]))
		{
			memcpy(tmp, ans[i], sizeof(ans[i]));
			memcpy(ans[i], ans[j], sizeof(ans[i]));
			memcpy(ans[j], tmp, sizeof(ans[j]));
		}
	for (int i = 1; i <= tot; ++i)
	{
		for (int j = 1; j <= ans[i][0]; ++j) printf("%c", ans[i][j]);
		putchar('\n');
	}
	
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node
{
	int son[26];
	bool f;
} trie[12005];

int n, m, pn, ro, ans;
int f[1200021];
char S[1500000];

inline void NewNode(int &x) {x = ++pn;}

inline void Insert()
{
	int len = strlen(S), now = ro;
	for (int i = len - 1; i >= 0; --i)
	{
		if (!trie[now].son[S[i] - 'a']) NewNode(trie[now].son[S[i] - 'a']);
		now = trie[now].son[S[i] - 'a'];
	}
	trie[now].f = 1;
}

void Solve()
{
	f[0] = m; ans = 0;
	int now = ro, len = strlen(S + 1);
	for (int i = 1; i <= len; ++i)
	{
		now = ro;
		for (int j = i; j; --j)
		{
			if (!trie[now].son[S[j] - 'a']) break;
			now = trie[now].son[S[j] - 'a'];
			if (f[j - 1] == m && trie[now].f) 
			{
				f[i] = m;
				ans = i;
			}
		}
	}
	printf("%d\n", ans);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%s", S);
		Insert();
	}
	memset(f, -1, sizeof(f));
	while (m--)
	{
		scanf("%s", S + 1);
		Solve();
	}
	
	return 0;
}

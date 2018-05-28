#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 10000 + 10;
const int MAXC = 20 + 10;

struct Trie_Node
{
	int son[26];
	bool end;
	Trie_Node() {memset(son, 0, sizeof(son)); end = false;} 
} trie[MAXN * MAXC];

int n, m, pn, ro, ans, cnt, len;
char S[MAXC], T[MAXC];

inline void NewNode(int &p) {p = ++pn;}

inline void Insert(char S[])
{
	int x = ro, len = strlen(S);
	for (int i = 0; i < len; ++i)
	{
		if (!trie[x].son[S[i] - 'a']) NewNode(trie[x].son[S[i] - 'a']);
		x = trie[x].son[S[i] - 'a'];
	}
	trie[x].end = true;
}

inline bool Find(char S[])
{
	int x = ro, len = strlen(S);
	for (int i = 0; i < len; ++i)
	{
		if (!trie[x].son[S[i] - 'a']) return false;
		x = trie[x].son[S[i] - 'a'];
	}
	return trie[x].end;
}

int main()
{
	scanf("%d%d", &n, &m);
	NewNode(ro);
	for (int i = 1; i <= n; ++i) 
	{
		scanf("%s", S);
		Insert(S);
	}
	while (m--)
	{
		scanf("%s", S);
		if (Find(S)) puts("-1");
		else 
		{
			len = strlen(S);
			ans = 0;
			memset(T, 0, sizeof(T));
			for (int i = 0; i < len; ++i) 
			{
				if (S[i] == S[i + 1]) continue;
				cnt = 0;
				for (int j = 0; j <= len; ++j) if (i != j) T[cnt++] = S[j];
				if (Find(T)) ++ans;
			}
			memset(T, 0, sizeof(T));
			for (int k = 'a'; k <= 'z'; ++k)
				for (int i = 0; i <= len; ++i)
				{
					if (S[i] == k) continue;
					cnt = 0;
					for (int j = 0; j <= len; ++j)
					{
						if (i == j) T[cnt++] = k;
						T[cnt++] = S[j];
					}
					if (Find(T)) ++ans;
				}
			memset(T, 0, sizeof(T));
			for (int k = 'a'; k <= 'z'; ++k)
				for (int i = 0; i < len; ++i)
				{
					if (S[i] == k) continue;
					cnt = 0;
					for (int j = 0; j <= len; ++j)
					{
						if (i == j) T[cnt++] = k;
						else T[cnt++] = S[j];
					}
					if (Find(T)) ++ans;
				}
			printf("%d\n", ans);
		}
	}
	
	return 0;
}

/*
DATE : 2013-3-3 
RATING : 2
TAG : Tarjan
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 200000 + 5;

int n,next[MAXN];
int dfn[MAXN],low[MAXN],cnt[MAXN];
int stk[MAXN],Top,ans[MAXN];
int Belong[MAXN],Bcnt,Index;
bool vis[MAXN];

void Tarjan(int p)
{
	dfn[p]=low[p]=++Index;
	vis[p]=1;
	stk[++Top]=p;
	int v=next[p];
	if(!dfn[v])
	{
		Tarjan(v);
		low[p]=min(low[p],low[v]);
	}
	else if(vis[v]) low[p]=min(low[p],dfn[v]);
	if(low[p]==dfn[p])
	{
		int i=-1;
		Bcnt++;
		while(i!=p)
		{
			i=stk[Top--];
			vis[i]=0;
			Belong[i]=Bcnt;
		}
	}
}

int Solve(int p)
{
	if(ans[p]) return ans[p];
	else if(cnt[Belong[p]]>1) return ans[p]=cnt[Belong[p]];
	else if(next[p]==p) return ans[p]=1;
	else return ans[p]=Solve(next[p])+1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&next[i]);
	for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++) cnt[Belong[i]]++;
	for(int i=1;i<=n;i++) printf("%d\n",Solve(i));
	
	return 0;
}

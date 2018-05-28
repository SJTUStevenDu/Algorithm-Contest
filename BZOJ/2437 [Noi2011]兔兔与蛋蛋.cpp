#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXC = 50;
const int MAXN = MAXC * MAXC;
const int MAXM = MAXN * 4 + 100;

struct Edge
{
	int next,to;
} g[MAXM];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

int n,m,k,x,y;
int ans[MAXN];
char map[MAXC][MAXC];
int Link[MAXN],idx[MAXC][MAXC],tot;
bool vis[MAXN],flag;

bool Find(int p)
{
	if(vis[p]) return 0;
	vis[p]=1;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(!Link[v] || Find(Link[v]))
		{
			Link[v]=p;
			Link[p]=v;
			return 1;
		}
	}
	return 0;
}

void del(int s,int x)
{
	if(g[start[s]].to==x) start[s]=g[start[s]].next;
	else for(int i=start[s];i;i=g[i].next) if(g[g[i].next].to==x) {g[i].next=g[g[i].next].next;return;}
}

bool check(int x)
{
	int v=Link[x];
	if(!v) return 0;
	memset(vis,0,sizeof(vis));
	if(Find(v)) return 0;
	Link[v]=0;
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",map[i]+1);
	for(int i=1;i<=n;i++) 
	{
		if(x) break;
		for(int j=1;j<=m;j++) if(map[i][j]=='.')
		{
			map[x=i][y=j]='X';
			break;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(((i+j)%2!=(x+y)%2) ^ (map[i][j]=='X')) idx[i][j]=++tot;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(idx[i][j])
		{
			if(idx[i+1][j]) AddEdge(idx[i][j],idx[i+1][j]),AddEdge(idx[i+1][j],idx[i][j]);
			if(idx[i][j+1]) AddEdge(idx[i][j],idx[i][j+1]),AddEdge(idx[i][j+1],idx[i][j]);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(idx[i][j] && map[i][j]=='X') 
			{
				memset(vis,0,sizeof(vis));
				Find(idx[i][j]);
			}
	scanf("%d",&k);
	for(int i=1;i<=2*k;i++)
	{
		int now=idx[x][y];
		scanf("%d%d",&x,&y);
		if(i&1) flag=check(now);
		else if(check(now) && flag) ans[++ans[0]]=i/2;
		for(int j=start[now];j;j=g[j].next) del(g[j].to,now);
	}
	printf("%d\n",ans[0]);
	for(int i=1;i<=ans[0];i++) printf("%d\n",ans[i]);
	
	return 0;
}

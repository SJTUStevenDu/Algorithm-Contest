#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100000 + 10;
const int MAXM = 2000000 + 10;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int next,to,w;
	bool nuked;
} g[MAXM];
int gn=1,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;g[gn].nuked=false;
}

int n,m,cnt,ans1,ans2;
int lab[MAXN],num[MAXN];
bool vis[MAXN];

inline int gcd(int n,int m)
{
	int tmp=0;
	while(m)
	{
		tmp=n%m;
		n=m;
		m=tmp;
	}
	return n;
}

void init()
{
	scanf("%d%d",&n,&m);
	for(int a,b,i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b,1);
		AddEdge(b,a,-1);
	}
}

void dfs1(int p,int it)
{
	vis[p]=1;
	lab[p]=it;
	for(int i=start[p];i;i=g[i].next) if(!g[i].nuked)
	{
		int v=g[i].to;
		g[i].nuked=g[i^1].nuked=true;
		if(vis[v])
		{
			if(lab[v]!=lab[p]+g[i].w) num[++cnt]=abs(lab[v]-(lab[p]+g[i].w));
		}
		else dfs1(v,lab[p]+g[i].w);
	}
}

int Belong[MAXN],D,Bmax[MAXN],Bmin[MAXN];

void dfs2(int p)
{
	Belong[p]=D;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(Belong[v]) continue;
		dfs2(v);
	}
}

void dfs3(int p,int it)
{
	lab[p]=it;
	vis[p]=1;
	for(int i=start[p];i;i=g[i].next) if(!g[i].nuked)
	{
		g[i].nuked=g[i^1].nuked=true;
		int v=g[i].to;
		dfs3(v,it+g[i].w);
	}
}

void Work()
{
	for(int i=1;i<=n;i++) if(!Belong[i])
	{
		++D;
		Bmax[D]=-INF;
		Bmin[D]=INF;
		dfs2(i);
	}
	memset(vis,0,sizeof(vis));
	for(int p=1;p<=n;p++) 
		for(int i=start[p];i;i=g[i].next) g[i].nuked=false;
	for(int i=1;i<=n;i++) 
	{
		if(!vis[i]) dfs3(i,1);
		Bmax[Belong[i]]=max(Bmax[Belong[i]],lab[i]);
		Bmin[Belong[i]]=min(Bmin[Belong[i]],lab[i]);
	}
	ans1=0;
	for(int i=1;i<=D;i++) ans1+=Bmax[i]-Bmin[i]+1;
	if(ans1<3) ans1=ans2=-1;
	else ans2=3;
}

void Solve()
{
	for(int i=1;i<=n;i++) if(!vis[i]) dfs1(i,1);
	int MIN,GCD,LCD;
	MIN=GCD=num[1];
	for(int i=2;i<=cnt;i++) GCD=gcd(GCD,num[i]),MIN=min(MIN,num[i]);
	for(LCD=3;LCD<=MIN;LCD++)
	{
		bool flag=true;
		for(int i=1;i<=n;i++) if(num[i]%LCD!=0) {flag=false;break;}
		if(flag) break;
	}
	if(cnt==0) Work();
	else if(GCD>=3) ans1=GCD,ans2=LCD;
	else ans1=ans2=-1;
}

int main()
{
	init();
	Solve();
	printf("%d %d\n",ans1,ans2);
	
	return 0;
}

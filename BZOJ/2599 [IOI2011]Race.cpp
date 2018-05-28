#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 200000 + 10;
const int MAXC = 1000000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXN*2];
int gn,start[MAXN];

inline void checkmax(int &x,int y) {if(x<y) x=y;}
inline void checkmin(int &x,int y) {if(x>y) x=y;}

int n,m,cur,size,now,ans;
int e[MAXN],d[MAXN],vv[MAXC],f[MAXN],c[MAXC],s[MAXN];
bool vis[MAXN*2];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;vis[gn]=true;
}

void FindRoot(int x,int pre)
{
	s[x]=1;f[x]=0;
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		if(v==pre) continue;
		FindRoot(v,x);
		s[x]+=s[v];
		checkmax(f[x],s[v]);
	}
	checkmax(f[x],size-s[x]);
	if(f[x]<f[cur]) cur=x;
}

void dfs1(int x,int pre)
{
	if(d[x]>m) return;
	if(vv[m-d[x]]==now) checkmin(ans,e[x]+c[m-d[x]]);
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		if(v==pre) continue;
		d[v]=d[x]+g[i].w;
		e[v]=e[x]+1;
		dfs1(v,x);
	}
}

void dfs2(int x,int pre)
{
	if(d[x]>m) return;
	if(vv[d[x]]!=now)
	{
		c[d[x]]=e[x];
		vv[d[x]]=now;
	}
	else checkmin(c[d[x]],e[x]);
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		if(v==pre) continue;
		dfs2(v,x);
	}
}

void Work(int x)
{
	vv[0]=now=x;
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		d[v]=g[i].w;
		e[v]=1;
		dfs1(v,x);
		dfs2(v,x);
	}
	FindRoot(x,0);
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		vis[i^1]=false;
		f[0]=size=s[v];
		FindRoot(v,cur=0);
		Work(cur);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	gn=1;
	for(int x,y,z,i=1;i<n;i++) 
	{
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x+1,y+1,z);
		AddEdge(y+1,x+1,z);
	}
	ans=f[0]=size=n;
	FindRoot(1,cur=0);
	Work(cur);
	printf("%d\n",ans<n ? ans : -1);
	
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10000 + 10;

struct Edge
{
	int next,to,w;
} g[MAXN*2];
int gn,start[MAXN];

int n,k,cur,ans;
int s[MAXN],sz,d[MAXN],f[MAXN],a[MAXN];
bool vis[MAXN*2];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;vis[gn]=true;
}

inline void checkmax(int &x,int y) {if(x<y) x=y;}

void FindRoot(int x,int pre)
{
	f[x]=0;s[x]=1;
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		if(v==pre) continue;
		FindRoot(v,x);
		s[x]+=s[v];
		checkmax(f[x],s[v]);
	}
	checkmax(f[x],sz-s[x]);
	if(f[x]<f[cur]) cur=x;
}

void dfs(int x,int pre)
{
	a[++a[0]]=d[x];s[x]=1;
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		if(v==pre) continue;
		d[v]=d[x]+g[i].w;
		dfs(v,x);
		s[x]+=s[v];
	}
}

inline int calc(int x,int init)
{
	int res=a[0]=0;
	d[x]=init;
	dfs(x,0);
	sort(a+1,a+1+a[0]);
	for(int l=1,r=a[0];l<r;)
		if(a[l]+a[r]<=k) {res+=r-l;l++;}
		else r--;
	return res;
}

void Work(int x)
{
	ans+=calc(x,0);
	for(int i=start[x];i;i=g[i].next) if(vis[i])
	{
		int v=g[i].to;
		vis[i^1]=false;
		ans-=calc(v,g[i].w);
		f[0]=sz=s[v];
		FindRoot(v,cur=0);
		Work(cur);
	}
}

int main()
{
	while(scanf("%d%d",&n,&k) && n)
	{
		gn=1;ans=0;
		memset(start,0,sizeof(start));
		for(int x,y,z,i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			AddEdge(x,y,z);
			AddEdge(y,x,z);
		}
		f[0]=sz=n;
		FindRoot(1,cur=0);
		Work(cur);
		printf("%d\n",ans);
	}
	
	return 0;
}

/*
DATE : 2013-4-2 
RATING : 3
TAG : Mininum Spanning Tree
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100 + 10;
const int MAXM = 1000 + 10;
const int MOD = 31011;

struct Edge
{
	int from,to,w;
} e[MAXM];

bool cmp(Edge A,Edge B)
{
	return A.w<B.w;
}

int n,m,num[MAXN],cnt,po;
int father[MAXN],st[MAXN],father2[MAXN];
long long ans=1;
bool vis[MAXN];

int getfather(int x)
{
	if(father[x]==x) return x;
	else return father[x]=getfather(father[x]);
}

int getfather2(int x)
{
	if(father2[x]==x) return x;
	else return getfather2(father2[x]);
}

long long tmp;

void dfs(int st,int en,int sum)
{
	if(sum==0)
	{
		++tmp;
		return;
	}
	if(st>en) return;
	int fa=getfather2(e[st].from),fb=getfather2(e[st].to);
	if(vis[e[st].from] && vis[e[st].to] && fa!=fb)
	{
		father2[fa]=fb;
		dfs(st+1,en,sum-1);
		father2[fa]=fa;
	}
	dfs(st+1,en,sum);
}

void work(int x)
{
	tmp=0;
	dfs(st[x],st[x+1]-1,num[x]);
	ans=(ans*tmp)%MOD;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&e[i].from,&e[i].to,&e[i].w);
	for(int i=1;i<=n;i++) father[i]=father2[i]=i;
	sort(e+1,e+1+m,cmp);
	int i;
	for(i=1;i<=m;i++) 
	{
		if(i==1 || e[i-1].w!=e[i].w)
		{
			st[++cnt]=i;
			num[cnt]=0;
			if(i!=1) work(cnt-1);
			for(int j=1;j<=n;j++) father2[j]=father[j];
		}
		if(getfather(e[i].from)!=getfather(e[i].to))
		{
			++po;
			father[getfather(e[i].from)]=getfather(e[i].to);
			++num[cnt];
			vis[e[i].from]=vis[e[i].to]=1;
		}
		if(po==n-1) break;
	}
	for(int j=i+1;j<=m+1;j++)
		if(e[j].w!=e[j-1].w) {st[cnt+1]=j;break;}
	work(cnt);
	if(po==n-1) printf("%lld\n",ans);
	else printf("0\n");
	
	return 0;
}

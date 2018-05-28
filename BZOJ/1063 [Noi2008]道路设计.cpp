#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 100000 + 10;

struct Edge
{
	int next,to;
} g[MAXN*2];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int n,m,MOD;
long long f[3][MAXN][15];
int q[MAXN],head,tail,father[MAXN];
bool vis[MAXN],ind[MAXN];

int main()
{
	scanf("%d%d%d",&n,&m,&MOD);
	if(m!=n-1)
	{
		printf("-1\n-1\n");
		return 0;
	}
	for(int a,b,i=1;i<=m;i++) 
	{
		scanf("%d%d",&a,&b);
		AddEdge(a,b);
		AddEdge(b,a);
	}
	q[tail++]=1;vis[1]=1;
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=start[p];i;i=g[i].next)
		{
			int v=g[i].to;
			if(vis[v]) continue;
			father[v]=p;
			q[tail++]=v;
			vis[v]=1;
			ind[p]=1;
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=tail-1;i;i--)
	{
		int p=q[i];
		if(!ind[p]) for(int k=1;k<=11;k++) f[0][p][k]=1;
		int v=father[p];
		if(!vis[v])
		{
			vis[v]=1;
			for(int k=1;k<=11;k++)
			{
				f[0][v][k]=(f[0][p][k-1]+f[1][p][k-1]+f[2][p][k-1])%MOD;
				f[1][v][k]=(f[0][p][k]+f[1][p][k])%MOD;
			}
		}
		else for(int k=1;k<=11;k++)
		{
			f[2][v][k]=(f[1][v][k]*(f[0][p][k]+f[1][p][k])%MOD+f[2][v][k]*(f[0][p][k-1]+f[1][p][k-1]+f[2][p][k-1])%MOD)%MOD;
			f[1][v][k]=(f[0][v][k]*(f[0][p][k]+f[1][p][k])%MOD+f[1][v][k]*(f[0][p][k-1]+f[1][p][k-1]+f[2][p][k-1])%MOD)%MOD;
			f[0][v][k]=f[0][v][k]*(f[0][p][k-1]+f[1][p][k-1]+f[2][p][k-1])%MOD;
		}
	}
	for(int i=1;i<=11;i++)
	{
		if(f[0][1][i]+f[1][1][i]+f[2][1][i]>0)
		{
			printf("%d\n",i-1);
			printf("%d\n",(f[0][1][i]+f[1][1][i]+f[2][1][i])%MOD);
			return 0;
		}
	}
	printf("2\n0\n");
	
	return 0;
}

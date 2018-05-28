/*
DATE : 2013-3-11 
RATING : 2
TAG : MaxFlow
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <queue>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 2500;
const int MAXE = 200005;
const int INF = 0x7FFFFFFF>>2;

struct Edge
{
	int to,next,w,rev;
} g[MAXE*2];
int gn,start[MAXN];

void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];g[gn].to=b;g[gn].w=c;g[gn].rev=gn+1;start[a]=gn;
	gn++;g[gn].next=start[b];g[gn].to=a;g[gn].w=0;g[gn].rev=gn-1;start[b]=gn;
}

int n,m,d,S,T,cnt;
int Map[25][25];
int vh[MAXN],h[MAXN],MaxFlow,flow;
bool flag;

inline int f(int i,int j,int Type)
{
	return ((i-1)*m+j)*2+Type;
}

inline int dist(int i,int j,int ii,int jj)
{
	return abs(i-ii)+abs(j-jj);
}

void Aug(int p)
{
	if(p==T)
	{
		flag=1;
		MaxFlow+=flow;
		return;
	}
	int i,minnode=n-1,tmp=flow;
	for(i=start[p];i;i=g[i].next) if(g[i].w>0)
	{
		int v=g[i].to;
		if(h[p]==h[v]+1)
		{
			flow=min(flow,g[i].w);
			Aug(v);
			if(h[S]>=n) return;
			if(flag) break;
			flow=tmp;
		}
		minnode=min(minnode,h[v]);
	}
	if(flag)
	{
		g[i].w-=flow;
		g[g[i].rev].w+=flow;
	}
	else 
	{
		vh[h[p]]--;
		if(vh[h[p]]==0) h[S]=n;
		h[p]=minnode+1;
		vh[h[p]]++;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&d);
	S=n*m*2+2;T=S+1;
	char ch=getchar();
	for(int i=1;i<=n;i++) 
	{
		while(ch!='0' && ch!='1' && ch!='2' && ch!='3') ch=getchar();
		for(int j=1;j<=m;j++) Map[i][j]=ch-'0',ch=getchar();
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
		{
			if(Map[i][j]==0) continue;
			AddEdge(f(i,j,0),f(i,j,1),Map[i][j]);
			for(int ii=max(1,i-d);ii<=min(n,i+d);ii++)
				for(int jj=max(1,j-d);jj<=min(m,j+d);jj++)
				{
					if(i==ii && j==jj) continue;
					if(!Map[ii][jj]) continue;
					if(dist(i,j,ii,jj)<=d) AddEdge(f(i,j,1),f(ii,jj,0),INF);
				}
			if(i<=d || i>=n-d+1 || j<=d || j>=m-d+1) AddEdge(f(i,j,1),T,INF);
		}
	for(int i=1;i<=n;i++) 
	{
		while(ch!='.' && ch!='L') ch=getchar();
		for(int j=1;j<=m;j++) 
		{
			if(ch=='L') AddEdge(S,f(i,j,0),1),cnt++;
			ch=getchar();
		}
	}
	n=T;
	vh[0]=n;
	while(h[S]<n)
	{
		flow=INF;
		flag=false;
		Aug(S);
	}
	printf("%d\n",cnt-MaxFlow);
	
	return 0;
}

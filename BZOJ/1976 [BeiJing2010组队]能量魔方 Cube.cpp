#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXC = 50;
const int MAXN = MAXC * MAXC * MAXC + 10;
const int MAXE = 600000 + 10;
const int INF = 0x7FFFFFFF>>2;
const int gx[3]={0,0,1};
const int gy[3]={1,0,0};
const int gz[3]={0,1,0};

struct Edge
{
	int next,to,w;
} g[MAXE];
int gn,start[MAXN];

inline void AddEdge(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;g[gn].w=c;
}

int n,idx[MAXC][MAXC][MAXC],ans,S,T,N,vh[MAXN],h[MAXN];
char str[MAXC];

int Aug(int p,int flow)
{
	if(p==T) return flow;
	int l=flow,minnode=N-1;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(g[i].w>0 && h[p]==h[v]+1)
		{
			int f=Aug(v,min(l,g[i].w));
			l-=f;
			g[i].w-=f;
			g[i^1].w+=f;
			if(!l || h[S]>=N) return flow-l;
		}
		if(g[i].w>0) minnode=min(minnode,h[v]);
	}
	if(l==flow)
	{
		if(--vh[h[p]]==0) h[S]=N;
		vh[h[p]=minnode+1]++;
	}
	return flow-l;
}

int main()
{
	scanf("%d",&n);
	gn=1;
	S=1;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			for(int k=1;k<=n;k++) idx[i][j][k]=S++;
	T=S+1;N=T;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
		{
			scanf("%s",str+1);
			for(int k=1;k<=n;k++) 
			{
				for(int l=0;l<3;l++)
				{
					int px=gx[l]+i,py=gy[l]+j,pz=gz[l]+k;
					if(px<=n && py<=n && pz<=n && px && py && pz)
					{
						++ans;
						AddEdge(idx[i][j][k],idx[px][py][pz],1);
						AddEdge(idx[px][py][pz],idx[i][j][k],1);
					}
				}
				if(str[k]=='?') continue;
				if((str[k]=='P') ^ ((i+j+k)&1))
				{
					AddEdge(S,idx[i][j][k],INF);
					AddEdge(idx[i][j][k],S,0);
				}
				else 
				{
					AddEdge(idx[i][j][k],T,INF);
					AddEdge(T,idx[i][j][k],0);
				}
			}
		}
	vh[0]=N;
	while(h[S]<N) ans-=Aug(S,INF);
	printf("%d\n",ans);
	
	return 0;
}

/*
DATE : 2012-11-27
RATING : 1
TAG : shortest path
*/ 

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN=1000+10;
int map[MAXN][MAXN],ans,dist[MAXN],dist1[MAXN],a,b,t,n,m,x;
bool vis[MAXN];
int queue[MAXN],head,tail;

void spfa()
{
	memset(dist,21,sizeof(dist));
	memset(queue,0,sizeof(queue));
	memset(vis,0,sizeof(vis));
	head=0;
	tail=1;
	queue[tail]=x;
	dist[x]=0;
	vis[x]=1;
	while(head!=tail)
	{
		head=(head+1)%MAXN;
		int p=queue[head];
		vis[p]=0;
		for(int i=1;i<=n;i++) 
		{
			if(map[p][i] && dist[i]>dist[p]+map[p][i])
			{
				dist[i]=map[p][i]+dist[p];
				if(!vis[i]) tail=(tail+1)%MAXN,queue[tail]=i,vis[i]=1;
			}
		}
	}
	return;
}

int main()
{
	scanf("%d%d%d",&n,&m,&x);
	while(m--)
	{
		cin>>a>>b>>t;
		map[a][b]=t;
	}
	spfa();
	memcpy(dist1,dist,sizeof(dist));
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++) swap(map[i][j],map[j][i]);
	spfa();
	for(int i=1;i<=n;i++) ans=max(ans,dist[i]+dist1[i]);
	cout<<ans<<endl;
	
	return 0;
}

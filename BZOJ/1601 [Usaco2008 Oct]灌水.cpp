/*
DATE : 2012-11-23 
RATING : 1
TAG : minimal spanning tree_prim
*/

#include <iostream>
#include <cstdio>
#include <cstring>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN=305;
const int INF=0x7FFFFFFF;
int n,map[MAXN][MAXN],dist[MAXN],w[MAXN],ans=INF;

int prim(int v0)
{
	int mind=0;dist[v0]=INF;
	for(int i=1;i<=n;i++) dist[i]=map[v0][i];
	for(int z=1;z<=n;z++)
	{
		int mindist=INF,minnode=-1;
		for(int i=1;i<=n;i++) if(mindist>dist[i]) mindist=dist[i],minnode=i;
		mind+=mindist;
		dist[minnode]=INF;
		for(int i=1;i<=n;i++) if(dist[i]!=INF && dist[i]>map[minnode][i]) dist[i]=map[minnode][i];
	}
	return mind;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>map[i][0];
		map[0][i]=map[i][0];
	}
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
		{
			cin>>map[i][j];
			if(!map[i][j]) map[i][j]=INF;
		}
	cout<<prim(0)<<endl;
	
	return 0;
}

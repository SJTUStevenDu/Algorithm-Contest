/*
DATE : 2012-12-22
RATING : 1
TAG : DFS
*/ 

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1000 + 10 ;

int n,s[MAXN],a[MAXN],k,m,ans;
bool map[MAXN][MAXN];
bool vis[MAXN];

void dfs(int p)
{
	for(int i=1;i<=n;i++) if(!vis[i] && map[p][i])
	{
		vis[i]=1;
		dfs(i);
	}
}

int main()
{
	cin>>k>>n>>m;
	for(int i=1;i<=k;i++) cin>>a[i];
	for(int i=1;i<=m;i++) 
	{
		int pa,pb;
		cin>>pa>>pb;
		map[pa][pb]=1;
	}
	for(int i=1;i<=k;i++) 
	{
		memset(vis,0,sizeof(vis));
		vis[a[i]]=1;
		dfs(a[i]);
		for(int i=1;i<=n;i++) if(vis[i]) s[i]++;
	}
	for(int i=1;i<=n;i++) if(s[i]==k) ans++;
	cout<<ans<<endl;
	return 0;
}

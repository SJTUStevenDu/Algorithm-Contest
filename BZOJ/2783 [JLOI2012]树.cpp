#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;
int n,s;
int v[MAXN],fa[MAXN];
int ans;

void dfs(int p,int c)
{
	if (c==s) ans++;
	if (c>s) return;
	if (fa[p]) dfs(fa[p],c+v[fa[p]]);
}

int main()
{
	cin>>n>>s;
	for (int i=1;i<=n;i++)
		cin>>v[i];
	for (int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		fa[y]=x;
	}
	for (int i=1;i<=n;i++)
		dfs(i,v[i]);
	cout<<ans<<endl;
	return 0;
} 

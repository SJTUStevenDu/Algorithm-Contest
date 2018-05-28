#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

const int MAXN = 100000 + 10;

typedef map<int,int> MII;
typedef MII::iterator MIIT;

MII nxt[MAXN];
int n,m,pn,Fail[MAXN],q[MAXN],head,tail,a[MAXN<<1],cnt[MAXN],vis[MAXN],pos[MAXN],num[MAXN];
int ans1[MAXN],ans2[MAXN];

inline int GetInt()
{
	char ch=0;
	for(;ch<'0' || ch>'9';ch=getchar());
	int res=0;
	for(;ch>='0' && ch<='9';ch=getchar()) res=res*10+ch-'0';
	return res;
}

int main()
{
	n=GetInt();m=GetInt();
	for(int j=0,i=1;i<=n;i++)
	{
		a[++j]=GetInt();
		for(int k=a[j];k;k--) a[++j]=GetInt();
		a[++j]=GetInt();
		for(int k=a[j];k;k--) a[++j]=GetInt();
	}
	for(int i=1;i<=m;i++)
	{
		int len=GetInt();
		int k=0;
		for(int j=1;j<=len;j++) 
		{
			int x=GetInt();
			if(!nxt[k][x]) nxt[k][x]=++pn;
			k=nxt[k][x];
		}
		++cnt[k];
		pos[i]=k;
	}
	tail=0;
	for(MIIT it=nxt[0].begin();it!=nxt[0].end();it++) q[tail++]=it->second;
	while(head!=tail)
	{
		int p=q[head++];
		for(MIIT it=nxt[p].begin();it!=nxt[p].end();it++) 
		{
			q[tail++]=it->second;
			int x=Fail[p];
			for(;x && !nxt[x][it->first];x=Fail[x]);
			Fail[it->second]=nxt[x][it->first];
		}
	}
	for(int j=1,i=1;i<=n;i++)
	{
		int len=a[j++];
		for(int k=1,x=0;k<=len;k++,j++)
		{
			for(;x && !nxt[x][a[j]];x=Fail[x]);
			x=nxt[x][a[j]];
			int t=x;
			for(;t && vis[t]!=i;t=Fail[t])
			{
				ans1[i]+=cnt[t];
				ans2[t]++;
				vis[t]=i;
			}
		}
		len=a[j++];
		for(int k=1,x=0;k<=len;k++,j++)
		{
			for(;x && !nxt[x][a[j]];x=Fail[x]);
			x=nxt[x][a[j]];
			int t=x;
			for(;t && vis[t]!=i;t=Fail[t])
			{
				ans1[i]+=cnt[t];
				ans2[t]++;
				vis[t]=i;
			}
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans2[pos[i]]);
	for(int i=1;i<n;i++) printf("%d ",ans1[i]);
	printf("%d\n",ans1[n]);

	return 0;
}

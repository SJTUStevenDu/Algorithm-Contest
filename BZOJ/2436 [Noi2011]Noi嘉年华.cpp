#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 400 + 10;
const int INF = 0x7FFFFFFF>>2;

int n,fir[MAXN],sec[MAXN],tot,Ans;
int a[MAXN],b[MAXN];

int Find(int x)
{
	int l=1,r=tot;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(b[mid]<x) l=mid+1;
		else r=mid-1;
	}
	return l;
}

void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&fir[i],&sec[i]),sec[i]+=fir[i];
	for(int i=1;i<=n;i++) a[++tot]=fir[i],a[++tot]=sec[i];
	sort(a+1,a+1+n*2);
	tot=1;b[tot]=a[1];
	for(int i=2;i<=n*2;i++) if(a[i]!=a[i-1]) b[++tot]=a[i];
	for(int i=1;i<=n;i++) fir[i]=Find(fir[i]),sec[i]=Find(sec[i]);
}

int pre[MAXN][MAXN],suc[MAXN][MAXN],ans[MAXN][MAXN],num[MAXN][MAXN];

void solve()
{
	for(int i=1;i<=tot;i++)
		for(int j=i;j<=tot;j++)
			for(int k=1;k<=n;k++) 
				if(fir[k]>=i && sec[k]<=j) num[i][j]++;
	for(int i=0;i<=tot+1;i++) for(int j=0;j<=tot+1;j++) pre[i][j]=-INF;
	pre[0][0]=0;
	for(int i=1;i<=tot;i++)
		for(int j=i;j>=0;j--)
		{
			pre[i][j]=pre[i][j+1];
			for(int k=0;k<i;k++) 
				pre[i][j]=max(pre[i][j],max(pre[k][j]+num[k][i],pre[k][j-num[k][i]]));
		}
	for(int i=0;i<=tot+1;i++) for(int j=0;j<=tot+1;j++) suc[i][j]=-INF;
	suc[tot+1][0]=0;
	for(int i=tot;i;i--)
		for(int j=tot-i+1;j>=0;j--)
		{
			suc[i][j]=suc[i][j+1];
			for(int k=i+1;k<=tot+1;k++)
				suc[i][j]=max(suc[i][j],max(suc[k][j]+num[i][k],suc[k][j-num[i][k]]));
		}
	int old=0;
	for(int i=1;i<=tot;i++)
		for(int j=i;j<=tot;j++) 
		{
			int k=tot-j+1;
			int kk;
			for(int x=0;x<=i;x++)
			{
				for(int y=0;y<=k;y++) if(x+y<=n)
				{
					old=min(x+y+num[i][j],pre[i][x]+suc[j][y]);
					if(old<0) break;
					if(ans[i][j]<old)
					{
						ans[i][j]=old;
						kk=y;
					}
					else break;
				}
				else break;
				k=kk;
			}
		}
}

int main()
{
	init();
	solve();
	Ans=0;
	for(int i=1;i<=n;i++) Ans=max(Ans,min(i,pre[tot][i]));
	printf("%d\n",Ans);
	for(int k=1;k<=n;k++) 
	{
		Ans=0;
		for(int i=1;i<=tot;i++) 
			for(int j=i;j<=tot;j++) 
				if(fir[k]>=i && sec[k]<=j) Ans=max(Ans,ans[i][j]);
		printf("%d\n",Ans);
	}
	
	return 0;
}

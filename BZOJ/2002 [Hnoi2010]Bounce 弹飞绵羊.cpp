#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 200000 + 10;

int n,m,ans,tot,Belong[MAXN],f[MAXN],To[MAXN],k[MAXN],First[MAXN];

int main()
{
	scanf("%d",&n);
	m=(int)sqrt(n);
	for(int j=m,i=0;i<n;i++)
	{
		if(j==m)
		{
			j=1;
			++tot;
			First[tot]=i;
		}
		else j++;
		scanf("%d",&k[i]);
		Belong[i]=tot;
	}
	First[++tot]=n;
	for(int i=n-1;i>=0;i--)
	{
		if(i+k[i]>=First[Belong[i]+1]) f[i]=1,To[i]=i+k[i];
		else f[i]=f[i+k[i]]+1,To[i]=To[i+k[i]];
	}
	scanf("%d",&m);
	while(m--)
	{
		int opr,x,y;
		scanf("%d",&opr);
		if(opr==1)
		{
			scanf("%d",&x);
			ans=0;
			while(x<n) ans+=f[x],x=To[x];
			printf("%d\n",ans);
		}
		else 
		{
			scanf("%d%d",&x,&y);
			k[x]=y;
			for(int i=x;i>=First[Belong[x]];i--)
				if(i+k[i]>=First[Belong[i]+1]) f[i]=1,To[i]=i+k[i];
				else f[i]=f[i+k[i]]+1,To[i]=To[i+k[i]];
		}
	}
	
	return 0;
}

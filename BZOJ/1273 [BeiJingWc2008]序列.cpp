#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = (1<<16) + 50;

int s[20][MAXN];
int n,m,delay,x;
char opr[20];
long long ans;

int main()
{
	scanf("%d%d",&n,&m);
	for(int xx,i=1;i<=n;i++)
	{
		scanf("%d",&xx);
		for(int j=0;j<16;j++)
			s[j][(xx&(1<<(j+1))-1)+1]++;
	}
	for(int i=0;i<16;i++)
		for(int j=1;j<=(1<<16);j++) s[i][j]+=s[i][j-1];
	while(m--)
	{
		scanf("%s",opr);
		scanf("%d",&x);
		if(opr[0]=='A')
		{
			delay+=x;
			delay=delay&((1<<16)-1);
		}
		else if(x<16)
		{
			int l=(1<<x),r=(1<<(x+1))-1;
			ans+=s[x][min(max(0,r-(delay&((1<<(x+1))-1))+1),1<<16)];
			ans-=s[x][min(max(0,l-(delay&((1<<(x+1))-1))),1<<16)];
			l+=1<<(x+1),r+=1<<(x+1);
			ans+=s[x][min(max(0,r-(delay&((1<<(x+1))-1))+1),1<<16)];
			ans-=s[x][min(max(0,l-(delay&((1<<(x+1))-1))),1<<16)];
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}

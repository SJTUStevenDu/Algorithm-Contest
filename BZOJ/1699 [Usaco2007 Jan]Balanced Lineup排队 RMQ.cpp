/*
DATE : 2013-2-21 
RATING : 1
TAG : RMQ
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50000 + 5;

int a[MAXN],Log[MAXN],n,l,r,Q;
int rmqmin[20][MAXN],rmqmax[20][MAXN];

void Build()
{
	Log[0]=-1;
	for(int i=1;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++) rmqmax[0][i]=rmqmin[0][i]=a[i];
	for(int i=1;i<=Log[n];i++)
		for(int j=1;j<=n-(1<<i)+1;j++) 
			rmqmin[i][j]=min(rmqmin[i-1][j],rmqmin[i-1][j+(1<<(i-1))]),rmqmax[i][j]=max(rmqmax[i-1][j],rmqmax[i-1][j+(1<<(i-1))]);
}

int Query(int l,int r)
{
	int x=Log[r-l+1];
//	cout<<max(rmqmax[x][l],rmqmax[x][r-(1<<x)+1])<<' '<<min(rmqmin[x][l],rmqmin[x][r-(1<<x)+1])<<endl;
	return max(rmqmax[x][l],rmqmax[x][r-(1<<x)+1])-min(rmqmin[x][l],rmqmin[x][r-(1<<x)+1]);
}

int main()
{
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	Build();
	while(Q--)
	{
		scanf("%d%d",&l,&r);
		printf("%d\n",Query(l,r));
	}
	
	return 0;
}

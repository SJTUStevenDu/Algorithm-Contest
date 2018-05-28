/*
DATE : 2012-12-12 
RATING : 3
TAG : Euler Road
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 10000 + 5;

struct E
{
	int v,d;
} Edge1[MAXN],Edge2[MAXN];

int n,m,x[MAXN],cnt1,cnt2;
int indegree[MAXN],ans;

bool cmp(E a,E b)
{
	return a.v<b.v;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		indegree[x]--;indegree[y]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(indegree[i]>0) Edge1[++cnt1].v=x[i],Edge1[cnt1].d=indegree[i];
		else if(indegree[i]<0) Edge2[++cnt2].v=x[i],Edge2[cnt2].d=-indegree[i];
	}
	sort(Edge1+1,Edge1+1+cnt1,cmp);
	sort(Edge2+1,Edge2+1+cnt2,cmp);
	while(cnt2)
	{
		int tmp=min(Edge1[cnt1].d,Edge2[cnt2].d);
		ans+=tmp*abs(Edge1[cnt1].v-Edge2[cnt2].v);
		Edge1[cnt1].d-=tmp;Edge2[cnt2].d-=tmp;
		if(Edge1[cnt1].d==0) cnt1--;
		if(Edge2[cnt2].d==0) cnt2--;
	}
	printf("%d\n",ans);
	
	return 0;
}

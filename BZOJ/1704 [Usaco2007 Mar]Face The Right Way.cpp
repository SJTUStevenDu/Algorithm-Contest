/*
DATE : 2013-2-8 
RATING : 2
TAG : ???
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

const int MAXN = 5000 + 5;

int n;
bool a[MAXN],r[MAXN];
int ansk,ansm;

int GetM(int k)
{
	int pos=1,m=0;
	bool state=false;
	memset(r,0,sizeof(r));
	while(pos<=n)
	{
		while(a[pos]^state) state^=r[pos],pos++;
		if(pos>n) break;
		if(pos>n-k+1) return -1;
		r[pos+k-1]=1;
		state^=1;
		m++;
	}
	return m;
}

int main()
{
	scanf("%d",&n);
	char ch=0;
	for(int i=1;i<=n;i++)
	{
		ch=getchar();
		while(ch!='F' && ch!='B') ch=getchar();
		if(ch=='F') a[i]=1;else a[i]=0;
	}
	ansm=GetM(1);ansk=1;
	for(int i=2;i<=n;i++) 
	{
		int mm=GetM(i);
		if(mm<ansm && mm!=-1) ansm=mm,ansk=i;
	}
	printf("%d %d\n",ansk,ansm);
	
	return 0;
}

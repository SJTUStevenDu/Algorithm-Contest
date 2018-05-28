/*
DATE : 2013-4-3 
RATING : 2
TAG : Greedy
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50000 + 10;
 
struct Line
{
	int k,b,idx;
} a[MAXN];

bool cmp(Line A,Line B)
{
	return A.k<B.k || (A.k==B.k && A.b>B.b);
}

int n;
int ans[MAXN];
Line stk[MAXN];
int top;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d%d",&a[i].k,&a[i].b);
		a[i].idx=i;
	}
	sort(a+1,a+1+n,cmp);
	stk[++top]=a[1];
	for(int i=2;i<=n;i++)
	{
		if(a[i].k!=a[i-1].k) 
		{
			while(top>1 && (a[i].b-stk[top].b)*1.0/(stk[top].k-a[i].k)<=(stk[top-1].b-stk[top].b)*1.0/(stk[top].k-stk[top-1].k)) --top;
			stk[++top]=a[i];
		}
	}
	for(int i=1;i<=top;i++) ans[stk[i].idx]=1;
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
	printf("\n");
	
	return 0;
}

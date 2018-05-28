/*
DATE : 2012-12-6 
RATING : 1
TAG : BFS 
*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN=300005;
int n,k,step[MAXN];
int q[MAXN],head,tail;

int main()
{
	cin>>n>>k;
	head=0;tail=1;q[tail]=n;step[n]=1;
	while(head!=tail)
	{
		head=(head+1)%MAXN;
		int x=q[head];
		if(x==k) break;
		if(2*x<MAXN && !step[x*2]) step[x*2]=step[x]+1,tail=(tail+1)%MAXN,q[tail]=x*2;
		if(x>=1 && !step[x-1]) step[x-1]=step[x]+1,tail=(tail+1)%MAXN,q[tail]=x-1;
		if(x<MAXN-1 && !step[x+1]) step[x+1]=step[x]+1,tail=(tail+1)%MAXN,q[tail]=x+1;
	}
	cout<<step[k]-1<<endl;
	
	return 0;
}

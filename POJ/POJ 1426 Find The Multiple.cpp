/*
DESCRITION : POJ 1426
TIME : 2012-11-18 
STATUS : ACCPETED
TAG : BFS
*/

#include <iostream>
#include <cstdio>

using namespace std;

long long n;
long long q[1000000],head,tail,now;

long long bfs()
{
	head=0;tail=1;q[tail]=1;
	while(head<tail)
	{
		head++;
		now=q[head]*10;
		if(now%n==0) return now;
		q[++tail]=now;
		now+=1;
		q[++tail]=now;
	}
}

int main()
{
	for(;;)
	{
		cin>>n;
		if(n==0) break;
		cout<<bfs()<<endl;
	}
	
	return 0;
}

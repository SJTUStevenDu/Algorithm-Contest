/*
DATE : 2013-5-21 
RATING : 2
TAG : DFSID
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN=50+5;
const int MAXM=1023+5;

int n,m,pack[MAXN],board[MAXN],rail[MAXM],total,waste,sum_rail[MAXM],l,r,mid;

bool dfsid(int deep,int pos)
{
	if(deep<=0) return true;
	if(waste>total-sum_rail[mid]) return false;
	for(int i=pos;i<=n;i++)
	{
		if(pack[i]>=rail[deep])
		{
			pack[i]-=rail[deep];
			if(pack[i]<rail[1]) waste+=pack[i];
			if(rail[deep]==rail[deep-1])
			{
				if(dfsid(deep-1,i)) return true;
			}
			else if(dfsid(deep-1,1)) return true;
			if(pack[i]<rail[1]) waste-=pack[i];
			pack[i]+=rail[deep];
		}
	}
	return false;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>board[i];
	cin>>m;
	for(int i=1;i<=m;i++) cin>>rail[i];
	sort(board+1,board+1+n);
	sort(rail+1,rail+m+1);
	for(int i=1;i<=m;i++) sum_rail[i]=sum_rail[i-1]+rail[i];
	for(int i=1;i<=n;i++) total+=board[i];
	r=m;
	while(sum_rail[r]>total) r--;
	while(l<=r)
	{
		for(int i=1;i<=n;i++) pack[i]=board[i];
		mid=(l+r)/2;
		waste=0;
		if(dfsid(mid,1)) l=mid+1;else r=mid-1;
	}
	cout<<(l+r)/2<<endl;
	
	return 0;
}
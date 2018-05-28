/*
DATE : 2013-5-16 
RATING : 3
TAG : DP
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

const int MAXN = 15;

int dp[MAXN][MAXN],a,b;

int Query(int x)
{
	int res=0;
	int num[MAXN],len=0;
	while(x)
	{
		num[++len]=x%10;
		x/=10;
	}
	num[len+1]=0;
	for(int i=1;i<len;i++)
		for(int j=1;j<10;j++) res+=dp[i][j];
	for(int i=1;i<num[len];i++) res+=dp[len][i];
	for(int i=len-1;i;i--)
	{
		for(int j=0;j<num[i];j++) if(abs(num[i+1]-j)>=2) res+=dp[i][j];
		if(abs(num[i]-num[i+1])<2) break;
	}
	return res;
}

int main()
{
	for(int i=0;i<10;i++) dp[1][i]=1;
	for(int i=2;i<=10;i++)
		for(int j=0;j<10;j++) 
			for(int k=0;k<10;k++) if(abs(j-k)>=2) dp[i][j]+=dp[i-1][k];
	scanf("%d%d",&a,&b);
	printf("%d\n",Query(b+1)-Query(a));
	
	return 0;
}

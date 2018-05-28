/*
DATE : 2013-1-20 
RATING : 1
TAG : DP 
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

string S;
int cost[30],n,m;
int dp[2005][2005];

int main()
{
	cin>>n>>m;
	cin>>S;
	for(int i=1;i<=n;i++)
	{
		char ch;
		int a,b;
		cin>>ch;
		cin>>a>>b;
		cost[ch-'a']=min(a,b);
	}
	for(int len=1;len<m;len++)
		for(int i=0;i+len<m;i++)
		{
			int j=i+len;
			if(i+1==j && S[i]==S[j]) continue;
			dp[i][j]=min(dp[i][j-1]+cost[S[j]-'a'],dp[i+1][j]+cost[S[i]-'a']);
			if(S[i]==S[j]) dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
		}
	cout<<dp[0][m-1]<<endl;;
	
	return 0;
}

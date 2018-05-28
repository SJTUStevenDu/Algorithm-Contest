/*
DATE : 2012-11-30 
RATING : 1
TAG : DP
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

int s1,s2,s3,ans;
int dp[3][200];

int main()
{
	scanf("%d%d%d",&s1,&s2,&s3);
	for(int i=1;i<=s1;i++) dp[0][i]=1;
	for(int i=1;i<=s1+s2;i++)
		for(int j=1;j<=s2;j++) if(i>j) dp[1][i]+=dp[0][i-j];
	for(int i=1;i<=s1+s2+s3;i++)
		for(int j=1;j<=s3;j++) if(i>j) dp[2][i]+=dp[1][i-j];
	for(int i=1;i<=s1+s2+s3;i++) if(dp[2][ans]<dp[2][i]) ans=i;
	printf("%d\n",ans);
	
	return 0;
}

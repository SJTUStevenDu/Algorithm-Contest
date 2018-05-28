/*
DATE : 2012-12-21 
RATING : DP
TAG : 1
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
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 2000 + 5;
int a[MAXN],sum[MAXN],n;
int dp[MAXN][MAXN];
 
int main()
{
    scanf("%d",&n);
    for(int i=n;i;i--) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=n;j++) 
        {
            dp[i][j]=max(dp[i][j-1],dp[i][j]);
            if(i>=2*j) dp[i][j]=max(dp[i][j],sum[i]-dp[i-2*j][2*j]);
            if(i>=2*j-1) dp[i][j]=max(dp[i][j],sum[i]-dp[i-2*j+1][2*j-1]);
        }
    printf("%d\n",dp[n][1]);
     
    return 0;
}
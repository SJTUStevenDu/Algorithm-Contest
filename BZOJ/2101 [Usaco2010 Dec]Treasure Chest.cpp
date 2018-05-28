/*
DATE : 2012-12-24 
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
#include <vector>
#include <fstream>
#include <string>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 5000 + 5;
 
int coins,dp[MAXN],sum[MAXN],n;
 
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) 
    {
        scanf("%d",&coins);
        sum[i+1]=sum[i]+coins;
    }
    for(int len=1;len<=n;len++)
        for(int i=0;i+len<=n;i++) 
            dp[i]=sum[i+len]-sum[i]-min(dp[i],dp[i+1]);
    printf("%d\n",dp[0]);
    return 0;
}

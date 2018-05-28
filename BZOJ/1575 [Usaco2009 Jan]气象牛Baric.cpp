/*
DATE : 2013-1-3 
RATING : 2
TAG : DP
*/
 
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 100 + 5;
 
int n,Lim,ans=0x7FFFFFFF;
int g[MAXN][MAXN],dp[MAXN][MAXN];
int a[MAXN];
 
int abs(int x)
{
    return x>0 ? x : -x;
}
 
int main()
{
    scanf("%d%d",&n,&Lim);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) 
        for(int j=i+1;j<=n;j++)
            for(int k=i+1;k<=j-1;k++) g[i][j]+=abs(2*a[k]-a[i]-a[j]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<i;j++) dp[1][i]+=abs(a[i]-a[j])*2;
        for(int j=i+1;j<=n;j++) g[i][n+1]+=abs(a[i]-a[j])*2;
    }
    for(int i=2;i<=n+1;i++)
    {
        for(int j=1;j<=n;j++) ans=min(ans,dp[i-1][j]+g[j][n+1]);
        if(ans<=Lim) 
        {
            printf("%d %d\n",i-1,ans);
            return 0;
        }   
        for(int j=1;j<=n;j++) 
        {
            dp[i][j]=dp[i-1][j];
            for(int k=i-1;k<=j-1;k++) dp[i][j]=min(dp[i][j],dp[i-1][k]+g[k][j]);
        }
    }
     
    return 0;
}
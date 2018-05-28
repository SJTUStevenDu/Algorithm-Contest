/*
DATE : 2012-12-20 
RATING : 2
TAG : DP
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
const int MAXN=2010;
int n,a[MAXN];
int dp[MAXN][MAXN];
int ans;
  
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int k=1;k<=n;k++)
    {
        for(int i=0;i<=k;i++)
        {
            int j=k-i; 
            int x=a[i]*k;
            int y=a[n-j+1]*k;
            if(i) x+=dp[i-1][j];
            if(j) y+=dp[i][j-1];
            dp[i][j]=max(x,y); 
        }
    }
    for(int i=0;i<=n;i++) ans=max(ans,dp[i][n-i]); 
    printf("%d\n",ans); 
    return 0;
}
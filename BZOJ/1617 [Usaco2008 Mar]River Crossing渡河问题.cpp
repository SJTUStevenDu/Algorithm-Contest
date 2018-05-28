/*
DATE : 2012-11-27 
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

int m,n,sum[2550];
int dp[2550];
 
int main()
{
    cin>>n>>m;
    sum[0]=m;
    for(int i=1;i<=n;i++) 
    {
        int a;
        cin>>a;
        sum[i]=sum[i-1]+a;
        dp[i]=sum[i]+m;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++) dp[i]=min(dp[i],dp[i-j]+m+sum[j]);
    cout<<dp[n]-m<<endl;
     
    return 0;
}
/*
DATE : 2013-01-20 
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
 
int n,m;
int a[25];
long long dp[10005];
 
int main()
{
    dp[0]=1;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)
        for(int j=a[i];j<=n;j++) dp[j]+=dp[j-a[i]];
    printf("%lld\n",dp[n]);
    return 0;
}

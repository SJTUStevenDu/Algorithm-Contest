/*
DATE : 2012-12-14 
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
 
const int MAXN = 10000 + 5;
 
long long dp[MAXN],a[MAXN],b[MAXN],ans;
int n,s;
 
int main()
{
    cin>>n>>s;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    dp[1]=a[1];
    for(int i=2;i<=n;i++) dp[i]=min(dp[i-1]+s,a[i]);
    for(int i=1;i<=n;i++) ans+=dp[i]*b[i];
    cout<<ans<<endl;
     
    return 0;
}

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
 
int n,l,len[605],dp[605];
string str[605],s;
 
int main()
{
    cin>>n>>l;
    cin>>s;
    for(int i=1;i<=n;i++) 
    {
        cin>>str[i];
        len[i]=str[i].size();
    }
    for(int i=0;i<l;i++)
    {
        for(int j=1;j<=n;j++)
            if(len[j]<=i+1)
            {
                int k=i;int t=len[j]-1;
                while(k>=0 && t>=0)
                {
                    if(s[k]==str[j][t]) t--;
                    k--;
                }
                if(t==-1)
                {
                    if(k==-1) dp[i]=max(dp[i],len[j]);
                    else if(k>=0) dp[i]=max(dp[k]+len[j],dp[i]);
                }
            }
    }
    cout<<l-dp[l-1]<<endl;
    return 0;
}

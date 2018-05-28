/*
DATE : 2013-3-18 
RATING : 1
TAG : Matrix
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
typedef long long int64;
 
int64 m,a,c,x0,n,g;
int64 mar[2][2][2],dp[65][2][2];

inline int64 mul(int64 a,int64 b,int64 c)
{
	int64 res=0;
	for (int i=0;i<=60;i++)
	{
		if ((1LL<<i)>b) break;
		if (b&(1LL<<i)) res=(res+a)%c;
		a=(a+a)%c;
	}
	return res;
}
 
int main()
{
    cin>>m>>a>>c>>x0>>n>>g;
    mar[0][0][0]=x0;
    mar[0][0][1]=c;
    dp[0][0][0]=a;
    dp[0][1][0]=dp[0][1][1]=1;
    for (int p=1;p<=60;p++)
        for (int i=0;i<=1;i++)
            for (int j=0;j<=1;j++)
                for (int k=0;k<=1;k++)
                {
                    dp[p][i][j]+=mul(dp[p-1][i][k],dp[p-1][k][j],m);
                    dp[p][i][j]%=m;
                }
    int now=0;
    for (int p=0;p<=60;p++)
        if (n&(1LL<<p))
        {
            now=1-now;
            memset(mar[now],0,sizeof(mar[now]));
            for (int i=0;i<=1;i++)
                for (int j=0;j<=1;j++)
                    for (int k=0;k<=1;k++)
                    {
                        mar[now][i][j]+=mul(mar[1-now][i][k],dp[p][k][j],m);
                        mar[now][i][j]%=m;
                    }
        }
    cout<<mar[now][0][0]%g<<endl;
    return 0;
}

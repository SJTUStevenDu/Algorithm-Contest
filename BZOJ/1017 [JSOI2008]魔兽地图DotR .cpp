/*
DATE : 2013-5-15 
RATING : 3
TAG : Ê÷ÐÍDP 
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

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50 + 10;
const int MAXM = 2000 + 10;
const int MAXV = 100 + 10;

struct Son
{
	int next,idx,num;
} g[MAXN];
int start[MAXN],gn;

inline void Add(int a,int b,int c)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].idx=b;g[gn].num=c;
}

int n,tot,ans;
int power[MAXN],can[MAXN],cost[MAXN],father[MAXN];
int dp[MAXN][MAXV][MAXM],G[MAXM];

void dfs(int p)
{
	if(start[p]==0) 
    { 
        can[p]=min(can[p],tot/cost[p]); 
        for(int i=0;i<=can[p];i++) 
            for(int j=i;j<=can[p];j++) 
				dp[p][i][j*cost[p]]=(j-i)*power[p]; 
        return; 
    } 
    can[p]=1<<30; 
    for(int i=start[p];i;i=g[i].next) 
        dfs(g[i].idx),can[p]=min(can[p],can[g[i].idx]/g[i].num); 
    for(int i=0;i<=can[p];i++) dp[p][i][0]=0; 
    for(int i=start[p],v=g[i].idx;i;i=g[i].next,v=g[i].idx) 
        for(int j=0;j<=can[p];j++) 
        { 
            memcpy(G,dp[p][j],sizeof(dp[p][j])); 
            memset(dp[p][j],-1,sizeof(dp[p][j])); 
            for(int k=tot;k>=0;k--) 
            { 
                for(int r=k;r>=0;r--) 
                    if(G[k-r]!=-1&&dp[v][j*g[i].num][r]!=-1) 
                        dp[p][j][k]=max(dp[p][j][k],G[k-r]+dp[v][j*g[i].num][r]); 
                ans=max(ans,dp[p][j][k]); 
            } 
        } 
    for(int i=0;i<=can[p];i++) 
        for(int j=i;j<=can[p];j++) 
            for(int k=0;k<=tot;k++) 
                if(dp[p][j][k]!=-1) 
                    dp[p][i][k]=max(dp[p][i][k],dp[p][j][k]+(j-i)*power[p]),ans=max(ans,dp[p][i][k]); 
}

int main()
{
	scanf("%d %d",&n,&tot);
	for(int i=1;i<=n;i++)
	{
		char type;
		scanf("%d %c",&power[i],&type);
		if(type=='A') 
		{
			int NUM;
			scanf("%d",&NUM);
			while(NUM--)
			{
				int a,b;
				scanf("%d %d",&a,&b);
				Add(i,a,b);
				father[a]=i;
			}
		}
		else scanf("%d %d",&cost[i],&can[i]);
	}
	memset(dp,-1,sizeof(dp)); 
    for(int i=1;i<=n;i++) 
        if(father[i]==0) dfs(i);
    printf("%d\n",ans); 
	
	return 0;
}

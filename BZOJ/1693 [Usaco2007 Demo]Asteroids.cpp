/*
DATE : 2012-12-26 
RATING : 1
TAG : Binary Map
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
 
const int MAXN = 500 + 5;
 
int map[MAXN][MAXN],match[MAXN];
bool vis[MAXN];
int n,ans,m;
 
bool Hungary(int p)
{
    for(int i=1;i<=n;i++) 
    {
        if(map[p][i] && !vis[i])
        {
            vis[i]=1;
            if(!match[i] || Hungary(match[i]))
            {
                match[i]=p;
                return 1;
            }
        }
    }
    return 0;
}
 
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) 
    {
        int x,y;
        scanf("%d%d",&x,&y);
        map[x][y]=1;
    }
    for(int i=1;i<=n;i++) 
    {
        memset(vis,0,sizeof(vis));
        if(Hungary(i)) ans++;
    }
    printf("%d\n",ans);
    return 0;
}

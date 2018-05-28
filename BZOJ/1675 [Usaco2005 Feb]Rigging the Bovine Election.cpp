/*
DATE : 2012-12-25 
RATING : 1
TAG : DFS
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
const int MAXN=9;
int n=5;
bool map[MAXN][MAXN];
int ans;
char a[10];
bool now[MAXN][MAXN];
bool vis[MAXN][MAXN];
 
void ff(int x,int y)
{
    if (x<1||x>n||y<1||y>n||vis[x][y]||!now[x][y]) return;
    vis[x][y]=true;
    ff(x-1,y),ff(x,y-1),ff(x+1,y),ff(x,y+1);
}
 
void check()
{
    memset(vis,false,sizeof(vis));
    int ck=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (!vis[i][j]&&now[i][j])
            {
                ck++;
                ff(i,j);
            }
    if (ck!=1) return;
    int B=0,J=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (now[i][j]&&map[i][j]) J++;
            else if (now[i][j]&&!map[i][j]) B++;
    if (J>B) ans++;
}
 
void dfs(int x,int y,int c)
{
    if (c==7)
    {
        check();
        return;
    }
    if (x>n) return;
    now[x][y]=true;
    if (y!=n) dfs(x,y+1,c+1);
    else dfs(x+1,1,c+1);
    now[x][y]=false;
    if (y!=n) dfs(x,y+1,c);
    else dfs(x+1,1,c);
}
 
int main()
{
    for (int i=1;i<=n;i++)
    {
        scanf("%s",a+1);
        for (int j=1;j<=n;j++)
            if (a[j]=='J') map[i][j]=true;
    }
    dfs(1,1,0);
    printf("%d\n",ans);
    return 0;
}
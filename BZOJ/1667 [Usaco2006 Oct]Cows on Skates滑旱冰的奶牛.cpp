/*
DATE : 2012-12-11 
RATING : 1
TAG : DFS
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
  
const int gx[4]={0,1,0,-1};
const int gy[4]={1,0,-1,0};
  
int r,c,step;
char map[120][100];
bool vis[120][100];
int a[120*100][2];
  
void dfs(int x,int y)
{
    if(x==r && y==c) 
    {
        exit(0); 
    }
    for(int i=0;i<4;i++) 
    {
        int px=gx[i]+x,py=gy[i]+y;
        if(px>0 && px<=r && py>0 && py<=c && map[px][py]!='*' && !vis[px][py])
        {
            vis[px][py]=1;
            a[++step][0]=px;
            a[step][1]=py;
            dfs(px,py);
            vis[px][py]=0;
            step--;
        }
    }
}
  
int main()
{
    cin>>r>>c;
    for(int i=1;i<=r;i++) 
        for(int j=1;j<=c;j++) cin>>map[i][j];
    a[++step][0]=1;a[step][1]=1;
   // dfs(1,1);
      
    return 0;
}
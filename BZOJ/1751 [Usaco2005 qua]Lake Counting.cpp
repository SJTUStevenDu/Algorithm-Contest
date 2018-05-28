/*
DATE : 2013-1-20 
RATING : 1
TAG : Flood_Fill
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int gx[8]={1,1,1,0,0,-1,-1,-1};
const int gy[8]={0,1,-1,1,-1,0,1,-1};
 
bool map[105][105];
bool vis[105][105];
int n,m,color;
 
void flood_fill(int x,int y)
{
    vis[x][y]=1;
    for(int i=0;i<8;i++)
    {
        int px=x+gx[i],py=y+gy[i];
        if(px>=1 && px<=n && py>=1 && py<=m && map[px][py] && !vis[px][py]) flood_fill(px,py);
    }
}
 
int main()
{
    cin>>n>>m;
    char ch=0;
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=m;j++)
        {
            cin>>ch;
            if(ch=='W') map[i][j]=1;else map[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++) 
    {
        for(int j=1;j<=m;j++) if(!vis[i][j] && map[i][j])
        {
            color++;
            flood_fill(i,j);
        }
    }
    cout<<color<<endl;
    return 0;
}

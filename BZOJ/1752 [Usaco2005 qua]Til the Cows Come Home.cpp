/*
DATE : 2013-1-17 
RATING : 1
TAG : SPFA
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
 
const int MAXN = 1000 + 5;
const int MAXE = 2000 + 5;
 
struct Edge
{
    int to,next,w;
} g[MAXE*2];
int start[MAXN],gn;
 
void AddEdge(int a,int b,int c)
{
    gn++;g[gn].w=c;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
    gn++;g[gn].w=c;g[gn].to=a;g[gn].next=start[b];start[b]=gn;
}
 
int n,m;
int dist[MAXN];
int vis[MAXN];
int q[MAXN],head,tail;
 
int main()
{
    scanf("%d%d",&m,&n);
    for(int a,b,c,i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        AddEdge(a,b,c);
    }
    memset(dist,20,sizeof(dist));
    q[head]=1;tail=1;vis[1]=1;dist[1]=0;
    while(head!=tail)
    {
        int p=q[head];
        head=(head+1)%MAXN;
        vis[p]=0;
        for(int i=start[p];i;i=g[i].next)
        {
            int v=g[i].to;
            if(dist[p]+g[i].w<dist[v])
            {
                dist[v]=dist[p]+g[i].w;
                if(!vis[v]) q[tail]=v,tail=(tail+1)%MAXN,vis[v]=1;
            }
        }
    }
    printf("%d\n",dist[n]);
     
    return 0;
}

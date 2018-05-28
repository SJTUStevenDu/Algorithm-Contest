/*
DATE : 2012-12-21 
RATING : 1
TAG : Shortest Path
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
 
using namespace std;
 
const int MAXM = 200000 + 5;
const int MAXN = 100000 + 5;
const int INF = 1000000000;
 
struct Edge
{
    int to,next,w;
} g[MAXM*2];
int gn,start[MAXN];
 
void AddEdge(int a,int b,int c)
{
    gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
    gn++;g[gn].to=a;g[gn].next=start[b];start[b]=gn;g[gn].w=c;
}
 
int n,pb,pa1,pa2,m,ans;
int dist1[MAXN],dist2[MAXN],q[MAXN],head,tail;
bool vis[MAXN];
 
int main()
{
    scanf("%d%d%d%d%d",&m,&n,&pb,&pa1,&pa2);
    for(int i=1;i<=m;i++) 
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        AddEdge(a,b,c);
    }
    for(int i=1;i<=n;i++) dist1[i]=dist2[i]=INF;
    head=0;tail=1;q[tail]=pa1;dist1[pa1]=0;vis[pa1]=1;
    while(head!=tail)
    {
        head=(head+1)%MAXN;
        int p=q[head];
        vis[p]=0;
        for(int i=start[p];i;i=g[i].next)
        {
            int u=g[i].to;
            if(dist1[u]>dist1[p]+g[i].w)
            {
                dist1[u]=dist1[p]+g[i].w;
                if(!vis[u]) 
                {
                    vis[u]=1;
                    if(dist1[q[(head+1)%MAXN]]>dist1[u]) q[head]=u,head=(head-1+MAXN)%MAXN;
                    else tail=(tail+1)%MAXN,q[tail]=u;
                }
            }
        }
    }
    memset(vis,0,sizeof(vis));
    head=0;tail=1;q[tail]=pa2;dist2[pa2]=0;vis[pa2]=1;
    while(head!=tail)
    {
        head=(head+1)%MAXN;
        int p=q[head];
        vis[p]=0;
        for(int i=start[p];i;i=g[i].next)
        {
            int u=g[i].to;
            if(dist2[u]>dist2[p]+g[i].w)
            {
                dist2[u]=dist2[p]+g[i].w;
                if(!vis[u]) 
                {
                    vis[u]=1;
                    if(dist2[q[(head+1)%MAXN]]>dist2[u]) q[head]=u,head=(head-1+MAXN)%MAXN;
                    else tail=(tail+1)%MAXN,q[tail]=u;
                }
            }
        }
    }
    ans=min(dist1[pa2]+dist1[pb],dist2[pa1]+dist2[pb]);
    printf("%d\n",ans);
     
    return 0;
}

/*
DATE : 2013-1-24
RATING : 3
TAG : ∑÷≤„Õº SPFA
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
 
const int MAXN = 10000 * 20 + 5;
const int MAXE = 50000 * 100 + 5;
 
struct Edge
{
    int to,next,w;
} g[MAXE];
int gn,start[MAXN];
 
void AddEdge(int a,int b,int c)
{
    gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;g[gn].w=c;
}
 
int n,m,k,ans,S,T;
int dist[MAXN];
bool vis[MAXN];
int q[MAXN],head,tail;
 
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    scanf("%d %d",&S,&T);
    S++;T++;
    T+=n*k;
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);a++;b++;
        AddEdge(a,b,c);AddEdge(b,a,c);
        for(int i=1;i<=k;i++)
        {
            AddEdge(i*n+a,i*n+b,c);
            AddEdge(i*n+b,i*n+a,c);
            AddEdge(i*n-n+a,i*n+b,0);
            AddEdge(i*n-n+b,i*n+a,0);
        }
    }
    memset(dist,30,sizeof(dist));
    q[head]=S;tail=1;vis[S]=1;dist[S]=0;
    while(head!=tail)
    {
        int p=q[head++];
        if(head==MAXN) head=0;
        vis[p]=0;
        for(int i=start[p];i;i=g[i].next)
        {
            int v=g[i].to;
            if(dist[v]>dist[p]+g[i].w)
            {
                dist[v]=dist[p]+g[i].w;
                if(!vis[v])
                {
                	vis[v]=1;
                    if(dist[q[head]]<dist[v])
                    {
                        q[tail++]=v;
                        if(tail==MAXN) tail=0;
                    }
                    else
                    {
                    	head--;
                    	if(head==-1) head=MAXN-1;
                        q[head]=v;
                    }
                }
            }
        }
    }
    ans=0x7FFFFFFF;
    for(int i=0;i<=k;i++) ans=min(ans,dist[T]);
    printf("%d\n",ans);
     
    return 0;
}

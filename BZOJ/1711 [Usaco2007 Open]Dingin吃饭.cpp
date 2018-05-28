/*
DATE : 2013-01-20 
RATING : 3
TAG : Maxflow
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
 
const int MAXN = 500 + 10;
 
int f,d,n,S,T;
int map[MAXN][MAXN];
int vh[MAXN],h[MAXN];
int maxflow,flow;
bool flag;
 
void aug(int p)
{
    if(p==T)
    {
        flag=true;
        maxflow+=flow;
        return;
    }
    int tmp=flow,minh=n-1,i;
    for(i=1;i<=n;i++) 
    {
        if(map[p][i]<=0) continue;
        if(h[p]==h[i]+1)
        {
            flow=min(flow,map[p][i]);
            aug(i);
            if(h[S]>=n) return;
            if(flag) break;
            flow=tmp;
        }
        minh=min(h[i],minh);
    }
    if(flag)
    {
        map[p][i]-=flow;
        map[i][p]+=flow;
    }
    else
    {
        vh[h[p]]--;
        if(vh[h[p]]==0) h[S]=n;
        h[p]=minh+1;
        vh[h[p]]++;
    }
}
 
int main()
{
    scanf("%d%d%d",&n,&f,&d);
    for(int i=1;i<=n;i++)
    {
        int a,b,c;
        scanf("%d%d",&a,&b);
        while(a--) scanf("%d",&c),map[c][i+f]=1;
        while(b--) scanf("%d",&c),map[i+f+n][c+2*n+f]=1;
    }
    for(int i=1;i<=n;i++) map[i+f][i+f+n]=1;
    S=2*n+d+f+1;T=S+1;
    for(int i=1;i<=f;i++) map[S][i]=1;
    n=2*n+d+f+1;
    for(int i=1;i<=d;i++) map[n-i][T]=1;
    n++;
    vh[0]=n;
    while(h[S]<n)
    {
        flag=false;
        flow=1000000000;
        aug(S);
    }
    printf("%d\n",maxflow);
     
    return 0;
}

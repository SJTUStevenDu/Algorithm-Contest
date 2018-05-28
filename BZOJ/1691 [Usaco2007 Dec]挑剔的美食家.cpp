/*
DATE : 2013-1-18 
RATING : 3
TAG : Size Balanced Tree
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
 
const int MAXN = 100000 + 5;
const int INF = 0x7FFFFFFF>>2;
 
struct Size_Balanced_Tree
{
    int data,size,left,right;
} SBT[MAXN];
 
int stk[MAXN],top,ro;
 
void Left_Rotate(int &p)
{
    int k=SBT[p].right;
    SBT[p].right=SBT[k].left;
    SBT[k].left=p;
    SBT[k].size=SBT[p].size;
    SBT[p].size=SBT[SBT[p].left].size+SBT[SBT[p].right].size+1;
    p=k;
}
 
void Right_Rotate(int &p)
{
    int k=SBT[p].left;
    SBT[p].left=SBT[k].right;
    SBT[k].right=p;
    SBT[k].size=SBT[p].size;
    SBT[p].size=SBT[SBT[p].left].size+SBT[SBT[p].right].size+1;
    p=k;
}
 
void Maintain(int &p,bool flag)
{
    if(!flag)
    {
        if(SBT[SBT[SBT[p].left].left].size>SBT[SBT[p].right].size) Right_Rotate(p);
        else if(SBT[SBT[SBT[p].left].right].size>SBT[SBT[p].right].size) Left_Rotate(SBT[p].left),Right_Rotate(p);
        else return;
    }
    else
    {
        if(SBT[SBT[SBT[p].right].right].size>SBT[SBT[p].left].size) Left_Rotate(p);
        else if(SBT[SBT[SBT[p].right].left].size>SBT[SBT[p].left].size) Right_Rotate(SBT[p].right),Left_Rotate(p);
        else return;
    }
    Maintain(SBT[p].left,false);
    Maintain(SBT[p].right,true);
    Maintain(p,true);
    Maintain(p,false);
}
 
void Insert(int &p,int v)
{
    if(!p)
    {
        p=stk[top--];
        SBT[p].left=SBT[p].right=0;
        SBT[p].size=1;
        SBT[p].data=v;
        return;
    }
    SBT[p].size++;
    if(v<SBT[p].data) Insert(SBT[p].left,v);
    else Insert(SBT[p].right,v);
    Maintain(p,v>SBT[p].data);
}
 
int Delete(int &p,int v)
{
    int k=SBT[p].data;
    SBT[p].size--;
    if(v==k || (v<k && SBT[p].left==0) || (v>k && SBT[p].right==0))
    {
        if(SBT[p].left==0 || SBT[p].right==0) 
        {
            stk[++top]=p;
            p=SBT[p].right+SBT[p].left;
        }
        else SBT[p].data=Delete(SBT[p].left,v+1);
        return k;
    }
    if(v<k) return Delete(SBT[p].left,v);
    else return Delete(SBT[p].right,v);
}
 
int Getsucc(int v)
{
    int re=INF,p=ro;
    while(p)
    {
        if(v<SBT[p].data) re=min(re,SBT[p].data);
        if(v<SBT[p].data) p=SBT[p].left;else p=SBT[p].right;
    }
    return re;
}
 
int n,m;
long long ans;
 
struct Feed
{
    int p,v;
} a[MAXN],b[MAXN];
 
bool cmp(Feed a,Feed b)
{
    return a.v>b.v;
}
 
int main()
{
    for(int i=1;i<MAXN;i++) stk[++top]=i;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].p,&a[i].v);
    for(int i=1;i<=m;i++) scanf("%d%d",&b[i].p,&b[i].v);
    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+m,cmp);
    if(n>m)
    {
        printf("-1\n");
        return 0;
    }
    int j=1;
    for(int i=1;i<=n;i++)
    {
        while(j<=m && b[j].v>=a[i].v) Insert(ro,b[j].p),j++;
        int k=Getsucc(a[i].p-1);
        if(k==INF)
        {
            printf("-1\n");
            return 0;
        }
        ans+=(long long)k;
        Delete(ro,k);
    }
    printf("%lld\n",ans);
    return 0;
}
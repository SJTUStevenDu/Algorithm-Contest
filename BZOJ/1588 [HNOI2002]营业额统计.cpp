/*
DATE : 2013-1-16 
RATING : 3
TAG : Size Balanced Tree
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 50000 + 5;
const int INF = 1000000000;
 
int stk[MAXN],top,ro;
 
struct Size_Balanced_Tree
{
    int left,right,data,size;
} SBT[MAXN];
 
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
    Maintain(p,false);
    Maintain(p,true);
}
 
void Insert(int &p,int v)
{
    if(!p)
    {
        p=stk[--top];
        SBT[p].left=SBT[p].right=0;
        SBT[p].data=v;
        SBT[p].size=1;
        return;
    }
    SBT[p].size++;
    if(SBT[p].data>v) Insert(SBT[p].left,v);
    else Insert(SBT[p].right,v);
    Maintain(p,v>SBT[p].data);
}
 
int Getpred(int v)
{
    int re=-INF,p=ro;
    while(p)
    {
        if(SBT[p].data<v) re=max(SBT[p].data,re);
        if(SBT[p].data<v) p=SBT[p].right;else p=SBT[p].left;
    }
    return re;
}
 
int Getsucc(int v)
{
    int re=INF,p=ro;
    while(p)
    {
        if(SBT[p].data>v) re=min(SBT[p].data,re);
        if(SBT[p].data>v) p=SBT[p].left;else p=SBT[p].right;
    }
    return re;
}
 
bool Exist(int v)
{
    int p=ro;
    while(p)
    {
        if(SBT[p].data==v) return 1;
        if(SBT[p].data<v) p=SBT[p].right;else p=SBT[p].left;
    }
    return 0;
}
 
int a[MAXN]={0},n,ans;
 
int abs(int x)
{
    if(x>=0) return x;else return -x;
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<MAXN;i++) stk[++top]=i;
    ans=abs(a[1]);
    Insert(ro,a[1]);
    for(int i=2;i<=n;i++) 
    {
        if(!Exist(a[i]))
        {
            int a1=Getsucc(a[i]),a2=Getpred(a[i]);
            ans+=min(abs(a1-a[i]),abs(a2-a[i]));
        }
        Insert(ro,a[i]);
    }
    printf("%d\n",ans);
     
    return 0;
}
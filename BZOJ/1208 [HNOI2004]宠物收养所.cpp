/*
DATE : 2013-1-16 
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
 
const int MAXN = 80000 + 5;
const int INF = 0x7FFFFFFF>>2;
const int MOD = 1000000;
 
int stk[MAXN],Top,ro,n,ans,type;
 
struct Size_Balanced_Tree
{
    int data,size,left,right;
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
        p=stk[Top--];
        SBT[p].left=SBT[p].right=0;
        SBT[p].size=1;
        SBT[p].data=v;
        return;
    }
    SBT[p].size++;
    if(SBT[p].data>v) Insert(SBT[p].left,v);else Insert(SBT[p].right,v);
    Maintain(p,v>SBT[p].data);
}
 
int Getpred(int v)
{
    int p=ro,re=-INF;
    while(p)
    {
        if(SBT[p].data<v) re=max(re,SBT[p].data);
        if(SBT[p].data<v) p=SBT[p].right;else p=SBT[p].left;
    }
    return re;
}
 
int Getsucc(int v)
{
    int p=ro,re=INF;
    while(p)
    {
        if(SBT[p].data>v) re=min(re,SBT[p].data);
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
        if(SBT[p].data>v) p=SBT[p].left;else p=SBT[p].right;
    }
    return 0;
}
 
int Delete(int &p,int v)
{
    int k=SBT[p].data;
    SBT[p].size--;
    if(v==k || (v>k && SBT[p].right==0) || (v<k && SBT[p].left==0))
    {
        if(SBT[p].right==0 || SBT[p].left==0) 
        {
            stk[++Top]=p;
            p=SBT[p].left+SBT[p].right;
        }
        else SBT[p].data=Delete(SBT[p].left,v+1);
        return k;
    }
    else
    {
        if(v<k) return Delete(SBT[p].left,v);
        else return Delete(SBT[p].right,v);
    }
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<MAXN;i++) stk[++Top]=i;
    for(int a,b,i=1;i<=n;i++) 
    {
        scanf("%d%d",&a,&b);
        if(!SBT[ro].size) type=a;
        if(a!=type)
        {
            if(!Exist(b))
            {
                int a1=Getsucc(b),a2=Getpred(b);
                if(a1-b>=b-a2) ans=(ans-a2+b)%MOD,Delete(ro,a2);
                else ans=(ans+a1-b)%MOD,Delete(ro,a1);
            }
            else Delete(ro,b);
        }
        else Insert(ro,b);
    }
    printf("%d\n",ans);
     
    return 0;
}
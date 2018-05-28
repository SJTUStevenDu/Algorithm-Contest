/*
DATE : 2013-1-17 
RATING : 3 
TAG : SBT 
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
 
int stk[MAXN],top,ro;
 
struct Size_Balanced_Tree
{
    int left,right,size,data;
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
    if (!flag)
    {
        if (SBT[SBT[SBT[p].left].left].size>SBT[SBT[p].right].size) Right_Rotate(p);
        else if (SBT[SBT[SBT[p].left].right].size>SBT[SBT[p].right].size) Left_Rotate(SBT[p].left),Right_Rotate(p);
        else return;
    }
    else
    {
        if (SBT[SBT[SBT[p].right].right].size>SBT[SBT[p].left].size) Left_Rotate(p);
        else if (SBT[SBT[SBT[p].right].left].size>SBT[SBT[p].left].size) Right_Rotate(SBT[p].right),Left_Rotate(p);
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
    if(SBT[p].data>v) Insert(SBT[p].left,v);
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
            p=SBT[p].left+SBT[p].right;
        }
        else SBT[p].data=Delete(SBT[p].left,v+1);
        return k;
    }
    if(v>k) return Delete(SBT[p].right,v);
    else return Delete(SBT[p].left,v);
}
 
int Getmax()
{
    if(!SBT[ro].size) return 0;
    int p=ro;
    while(SBT[p].right) p=SBT[p].right;
    return SBT[p].data;
}
 
struct Node
{
    int x,h;bool flag;
} Line[MAXN];
 
bool cmp(Node a,Node b)
{
    return a.x<b.x;
}
 
int n,cnt;
long long ans;
 
int main()
{
    for(int i=1;i<MAXN;i++) stk[++top]=i;
    scanf("%d",&n);
    while(n--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        Line[++cnt].x=a;Line[cnt].h=c;Line[cnt].flag=true;
        Line[++cnt].x=b;Line[cnt].h=c;Line[cnt].flag=false;
    }
    sort(Line+1,Line+1+cnt,cmp);
    for(int i=1;i<=cnt;i++) 
    {
        ans+=(Line[i].x-Line[i-1].x)*(long long)Getmax();
        if(Line[i].flag) Insert(ro,Line[i].h);else Delete(ro,Line[i].h);
    }
    printf("%lld\n",ans);
    
    return 0;
}

/*
DATE : 2013-1-16
RATING : 3
TAG : Size Balanced Tree
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 200005;
 
int ro,stk[MAXN],lowest,tot,n,top;
int delay;
 
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
        p=stk[top--];
        SBT[p].right=SBT[p].left=0;
        SBT[p].size=1;
        SBT[p].data=v;
        return;
    }
    SBT[p].size++;
    if(v<SBT[p].data) Insert(SBT[p].left,v);
    else Insert(SBT[p].right,v);
    Maintain(p,v>SBT[p].data);
}
 
int find_kth(int k)
{
    int p=ro;
    while(p)
    {
        if(SBT[SBT[p].left].size+1==k) return SBT[p].data;
        if(SBT[SBT[p].left].size+1>k) p=SBT[p].left;
        else k-=SBT[SBT[p].left].size+1,p=SBT[p].right;
    }
}
 
int Delete(int &p,int v)
{
    int k=SBT[p].data;
    SBT[p].size--;
    if(v==k || (SBT[p].left==0 && v<k) || (SBT[p].right==0 && v>k))
    {
        if(SBT[p].left==0 || SBT[p].right==0)
        {
            stk[++top]=p;
            p=SBT[p].left+SBT[p].right;
        }
        else SBT[p].data=Delete(SBT[p].left,v+1);
        return k;
    }
    if(v<k) return Delete(SBT[p].left,v);
    else return Delete(SBT[p].right,v);
}
 
int Getmin()
{
    if (!SBT[ro].size) return -1000000000;
    int p=ro;
    while(SBT[p].left) p=SBT[p].left;
    return SBT[p].data;
}
 
int main()
{
    for(int i=1;i<MAXN;i++) stk[++top]=i;
    scanf("%d%d",&n,&lowest);
    while(n--)
    {
        char ch=getchar();
        int a;
        while(ch!='I' && ch!='A' && ch!='S' && ch!='F') ch=getchar();
        scanf("%d",&a);
        if(ch=='I')
        {
            if(a<lowest) continue;
            Insert(ro,a-delay);
            tot++;
        }
        else if(ch=='A') delay+=a;
        else if(ch=='S')
        {
            delay-=a;
            int k=Getmin();
            while(k+delay<lowest && k!=-1000000000)
            {
                Delete(ro,k);
                k=Getmin();
            }
        }
        else if(ch=='F') 
        {
            if(a>SBT[ro].size) printf("-1\n");
            else printf("%d\n",find_kth(SBT[ro].size+1-a)+delay);
        }
    }
    printf("%d\n",tot-SBT[ro].size);
     
    return 0;
}
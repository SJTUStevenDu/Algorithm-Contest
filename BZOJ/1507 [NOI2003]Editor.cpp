/*
DATE : 2013-3-21
RATING : 2
TAG : Splay
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include <map>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 4000000 + 10;
 
struct Splay_Tree
{
    int left,right,size,fa;
    char data;
} spl[MAXN];
 
int n=1,m,stk[MAXN],top,ro;
 
inline void Pushup(int p)
{
    spl[p].size=spl[spl[p].right].size+spl[spl[p].left].size+1;
}
 
inline void NewNode(int &p,int f,char d)
{
    p=stk[top--];
    spl[p].left=spl[p].right=0;
    spl[p].fa=f;
    spl[p].data=d;
    spl[p].size=1;
}
 
inline void Left_Rotate(int p)
{
    int k=spl[p].right;
    spl[p].right=spl[k].left;
    spl[spl[k].left].fa=p;
    spl[k].left=p;
    spl[k].size=spl[p].size;
    spl[p].size=spl[spl[p].left].size+spl[spl[p].right].size+1;
    if(spl[p].fa)
    {
        if(spl[spl[p].fa].left==p) spl[spl[p].fa].left=k;
        else spl[spl[p].fa].right=k;
    }
    spl[k].fa=spl[p].fa;
    spl[p].fa=k;
    Pushup(p);
}
 
inline void Right_Rotate(int p)
{
    int k=spl[p].left;
    spl[p].left=spl[k].right;
    spl[spl[k].right].fa=p;
    spl[k].right=p;
    spl[k].size=spl[p].size;
    spl[p].size=spl[spl[p].left].size+spl[spl[p].right].size+1;
    if(spl[p].fa)
    {
        if(spl[spl[p].fa].left==p) spl[spl[p].fa].left=k;
        else spl[spl[p].fa].right=k;
    }
    spl[k].fa=spl[p].fa;
    spl[p].fa=k;
    Pushup(p);
}
 
void Splay(int p,int g)
{
    for(;spl[p].fa!=g;)
    {
        if(spl[spl[p].fa].fa==g)
        {
            if(spl[spl[p].fa].left==p) Right_Rotate(spl[p].fa);
            else Left_Rotate(spl[p].fa);
        }
        else if((spl[spl[spl[p].fa].fa].left==spl[p].fa) ^ (spl[spl[p].fa].left==p))
        {
            if(spl[spl[p].fa].left==p) Right_Rotate(spl[p].fa),Left_Rotate(spl[p].fa);
            else Left_Rotate(spl[p].fa),Right_Rotate(spl[p].fa);
        }
        else
        {
            if(spl[spl[p].fa].left==p) Right_Rotate(spl[spl[p].fa].fa),Right_Rotate(spl[p].fa);
            else Left_Rotate(spl[spl[p].fa].fa),Left_Rotate(spl[p].fa);
        }
    }
    if(!g) ro=p;
    Pushup(p);
}
 
void Rotate_to(int k,int g)
{
    int p=ro;
    while(spl[spl[p].left].size!=k-1)
    {
        if(k-1<spl[spl[p].left].size) p=spl[p].left;
        else k-=spl[spl[p].left].size+1,p=spl[p].right;
    }
    Splay(p,g);
}
 
char ch[MAXN];
int len;
 
void Build(int &p,int l,int r,int f)
{
    int mid=(l+r)>>1;
    NewNode(p,f,ch[mid]);
    if(l<mid) Build(spl[p].left,l,mid-1,p);
    if(mid<r) Build(spl[p].right,mid+1,r,p);
    Pushup(p);
}
 
void Insert(int pos,int tot)
{
    len=0;
    while(len<tot)
    {
        char cc=getchar();
        if(cc<32 || cc>126) continue;
        ch[++len]=cc;
    }
    Rotate_to(pos,0);
    Rotate_to(pos+1,ro);
    Build(spl[spl[ro].right].left,1,tot,spl[ro].right);
    Splay(spl[spl[ro].right].left,0);
}
 
int q[MAXN],head,tail;
 
void Delete(int pos,int tot)
{
    Rotate_to(pos,0);
    Rotate_to(min(pos+1+tot,spl[ro].size),ro);
    head=0;tail=1;
    q[head]=spl[spl[ro].right].left;
    while(head!=tail)
    {
        int p=q[head++];
        stk[++top]=p;
        if(spl[p].left) q[tail++]=spl[p].left;
        if(spl[p].right) q[tail++]=spl[p].right;
    }
    spl[spl[ro].right].left=0;
    Splay(spl[ro].right,0);
}
 
void Query(int p)
{
    if(!p) return;
    Query(spl[p].left);
    printf("%c",spl[p].data);
    Query(spl[p].right);
}
 
char opr[20];
int tmp;
 
int main()
{
    for(int i=MAXN-1;i;i--) stk[++top]=i;
    scanf("%d",&m);
    NewNode(ro,0,0);
    NewNode(spl[ro].right,ro,0);
    Pushup(ro);
    while(m--)
    {
        scanf("%s",opr);
        if(opr[0]!='P' && opr[0]!='N') scanf("%d",&tmp);
        if(opr[0]=='P') --n;
        else if(opr[0]=='N') ++n;
        else if(opr[0]=='M') n=tmp+1;
        else if(opr[0]=='G')
        {
            Rotate_to(n,0);
            Rotate_to(min(n+tmp+1,spl[ro].size),ro);
            Query(spl[spl[ro].right].left);
            Splay(spl[spl[ro].right].left,0);
            printf("\n");
        }
        else if(opr[0]=='I') Insert(n,tmp);
        else Delete(n,tmp);
    }
     
    return 0;
}

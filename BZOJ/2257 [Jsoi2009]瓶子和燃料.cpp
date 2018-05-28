#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
int n,k,ans,cnt;
int a;
int q[1000005];
 
void divide(int x)
{
    for(int i=1;i*i<x;i++) 
    {
        if(x%i==0) q[++cnt]=i,q[++cnt]=x/i;
    }
    int i=(int)sqrt(x);
    if(i*i==x) q[++cnt]=i;
}
 
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        divide(a);
    }
    sort(q+1,q+1+cnt);
    int num=1;
    for(int i=2;i<=cnt+1;i++) 
    {
        if(q[i]==q[i-1]) num++;
        else
        {
            if(num>=k) ans=max(q[i-1],ans);
            num=1;
        }
    }
    printf("%d\n",ans);
     
    return 0;
}
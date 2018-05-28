/*
DATE : 2012-12-17 
RATING : 1
TAG : Greedy
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
 
const int MAXN = 100000 + 5;
 
struct Node
{
    long long p,c;
} a[MAXN];
 
bool cmp(Node a,Node b)
{
    if(a.p!=b.p)return a.p<b.p;
    return a.c<b.c;
}
 
int n;
long long ans,b;
 
int main()
{
    scanf("%d %lld",&n,&b);
    for(int i=1;i<=n;i++) scanf("%lld %lld",&a[i].p,&a[i].c);
    sort(a+1,a+1+n,cmp);
    int i;
    for(i=1;i<=n;i++) if((double)b/a[i].p>=a[i].c) b-=(a[i].p*a[i].c),ans+=a[i].c;else break;
    if(i!=n+1) ans+=(b/a[i].p);
    printf("%lld\n",ans);
     
    return 0;
}
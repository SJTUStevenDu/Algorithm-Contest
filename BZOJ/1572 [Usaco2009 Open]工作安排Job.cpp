/*
DATE : 2012-12-25 
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
#include <queue>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
const int MAXN = 100000 + 5;
 
struct Node
{
    long long en,w;
} a[MAXN];
 
bool cmp(Node a,Node b)
{
    return a.en<b.en;
}
 
long long now=1000000000+10,ans;
int n;
 
priority_queue <long long> q;
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].en,&a[i].w);
    a[++n].en=a[n].w=0;
    sort(a+1,a+1+n,cmp);
    for(int i=n;i>=0;i--) 
    {
        while(q.size() && now>a[i].en)
        {
            ans+=q.top();
            q.pop();
            now--;
        }
        now=a[i].en;
        q.push(a[i].w);
    }
    printf("%lld\n",ans);
     
    return 0;
}
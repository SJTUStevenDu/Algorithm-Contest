/*
DATE : 2012-12-21 
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
 
const int MAXN = 500000 + 5;
 
struct Cow
{
    int w,u;
} cow[MAXN*3];
 
bool cmp(Cow a,Cow b)
{
    return a.u>b.u || (a.u==b.u && a.w<b.w);
}
 
long long power(long long x,long long y,long long z)
{
    long long p=1;
    for (int i = 1; i <= y; i++)
        p = (p*x) % z;
    return p;
}
 
long long n,a,b,c,d,e,f,g,h,mod,ans;
 
int main()
{
    cin>>n>>a>>b>>c>>d>>e>>f>>g>>h>>mod;
    for(int i=0;i<3*n;i++)
    {
        cow[i].w = (a*power(i,5,d) + b*power(i,2,d) + c) % d;
        cow[i].u = (e*power(i,5,h) + f*power(i,3,h) + g) % h;
    }
    sort(cow,cow+3*n,cmp);
    for(int i=0;i<n;i++) ans=(ans+cow[i].w)%mod;
    cout<<ans<<endl;
     
    return 0;
}
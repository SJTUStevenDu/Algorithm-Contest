/*
DATE : 2013-1-17 
RATING : 1
TAG : 
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
 
double s,l;
int y;
long long ans;
 
int main()
{
    scanf("%lf%lf%d",&l,&s,&y);
    l/=100;l+=1;
    for(int i=1;i<=y;i++) s=s*l;
    ans=(long long)floor(s);
    printf("%lld\n",ans);
    return 0;
}
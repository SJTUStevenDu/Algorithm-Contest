/*
DATE : 2013-1-17 
RATING : 1
TAG : Sort
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
 
const int MAXN = 10000 + 5;
 
int n,a[MAXN];
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    printf("%d\n",a[n/2+1]);
     
    return 0;
}
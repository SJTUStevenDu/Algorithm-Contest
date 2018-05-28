/*
DATE : 2012-12-14 
RATING : 1
TAG : simulation
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int n;
long long a[10001],s[10001];
long long ans;
 
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    for (int i=1;i<=n;i++)
    {
        ans+=(i-1)*a[i]-s[i-1];
        ans+=s[n]-s[i]-(n-i)*a[i];
    }
    cout<<ans<<endl;
    return 0;
}
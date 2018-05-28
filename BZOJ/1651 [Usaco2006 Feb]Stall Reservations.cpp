/*
DATE : 2012-12-10 
RATING : 1
TAG : Greedy
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

using namespace std;

int n,ans,h[1000005];

int main()
{
	cin>>n;
    for(int i=1;i<=n;i++) 
    {
        int a,b;
        cin>>a>>b;
        h[a]++;h[b+1]--;
    }
    for(int i=1;i<=1000000;i++)
    {
        h[i]+=h[i-1];
        ans=max(ans,h[i]);
    }
    cout<<ans<<endl;
	
	return 0;
}

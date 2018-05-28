/*
DATE : 2012-12-5 
RATING : 2
TAG : Monotone stack
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

const int MAXN = 50000 + 5;

int n,h[MAXN],ans,a,t;
int st[MAXN]={-1};

int main()
{
	cin>>n>>a;
	for(int i=1;i<=n;i++) cin>>a>>h[i];
	h[++n]=0;
	for(int i=1;i<=n;i++) 
	{
		while(t && st[t]>h[i]) t--,ans++;
		if(h[i]>st[t]) st[++t]=h[i];
	}
	cout<<ans<<endl;
	
	return 0;
}

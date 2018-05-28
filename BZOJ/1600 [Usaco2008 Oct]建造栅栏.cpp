/*
DATE : 2012-11-23 
RATING : 2
TAG : DP
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

int n,f[2550];

int main()
{
	cin>>n;
	int maxn=(n/2-1+(n&1));
	f[0]=1;
	for(int k=1;k<=4;k++)
	{
		for(int i=n;i>=0;i--)
		{
			f[i]=0;
			for(int j=1;j<=maxn;j++) 
				if(i>=j) f[i]+=f[i-j];
		}
	}
	cout<<f[n]<<endl;
	
	return 0;
}

/*
DATE : 2012-12-6 
RATING : 1
TAG : 
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

int n,ans;

int main()
{
	cin>>n;
	for(int i=0;i*i<=n;i++) 
		for(int j=0;j*j<=n;j++) 
			if(i*i+j*j>n*n) break;
			else for(int k=0;k*k<=n;k++)
				if(i*i+j*j+k*k>n*n) break;
				else for(int m=0;m*m<=n;m++) if(i*i+j*j+k*k+m*m==n) ans++; 
	cout<<ans<<endl;
		
	return 0;
}

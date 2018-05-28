/*
DATE : 2012-12-10 
RATING : 0
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

int ans;
long long n;

int main()
{
	cin>>n;
	while(n!=1)
	{
		if(n%2==1) n=n*3+1;
		else n/=2;
		ans++;
	}
	cout<<ans<<endl;
	
	return 0;
}

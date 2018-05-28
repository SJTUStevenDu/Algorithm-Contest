/*
DATE : 2012-11-27 
RATING : 1
TAG : MEMORIZATION SERACH
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

int sum[100005],n,k;

int cal(int n)
{
	if(n>100000) 
	{
		if((n-k)%2 || n<k+2) return 1;
		else return cal((n-k)/2)+cal((n-k)/2+k);
	}
	if(sum[n]==-1) 
	{
		if((n-k)%2 || n<k+2) 
		{
			sum[n]=1;
			return sum[n];
		}else  
		{
			sum[n]=cal((n-k)/2)+cal((n-k)/2+k);
			return sum[n];
		}
	}
	else return sum[n];
}

int main()
{
	cin>>n>>k;
	for(int i=1;i<=100000;i++) sum[i]=-1;
	cout<<cal(n)<<endl;
	
	return 0;
}

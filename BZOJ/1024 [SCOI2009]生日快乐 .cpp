/*
DATE : 2013-4-3 
RATING : 1
TAG : DFS
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
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

double x,y;
int n;
double ans;

double dfs(double x,double y,int n)
{
	if(x>y) swap(x,y);
	if(n==1) return y/x;
	double r=1.0/n,res=1e20;
	for(int i=1;i<n;i++)
	{
		res=min(res,max(dfs(x*i*r,y,i),dfs(x-x*i*r,y,n-i)));
		res=min(res,max(dfs(x,y*i*r,i),dfs(x,y-y*i*r,n-i)));
	}
	return res;
}

int main()
{
	cin>>x>>y>>n;
	cout<<setiosflags(ios::fixed)<<setprecision(6)<<dfs(x,y,n)<<endl;
	
	return 0;
}

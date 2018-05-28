/*
DATE : 2013-5-20 
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
#include <vector>
#include <fstream>
#include <string>
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 10;
const int T = 100;

int n,M[MAXN];
double f[MAXN],A;

int main()
{
	scanf("%d%lf",&n,&A);
	for(int i=1;i<=n;i++) scanf("%d",&M[i]);
	for(int i=1;i<=T;i++)
	{
		f[i]=0;
		int r=(int)(10e-8+floor(A*i));
		for(int j=1;j<=r;j++) f[i]+=1.0*M[i]*M[j]/(i-j);
	}
	for(int i=T+1;i<=n;i++)
	{
		f[i]=0;
		int r=(int)(10e-8+floor(A*i));
		int l=(int)(10e-8+floor(A*(i-T)));
		for(int j=l+1;j<=r;j++) f[i]+=1.0*M[i]*M[j]/(i-j);
		f[i]+=1.0*M[i]*(f[i-T]/M[i-T])*(i-T-1.0*l/2)/(i-1.0*l/2);
	}
	for(int i=1;i<=n;i++) printf("%.6lf\n",f[i]);
	
	return 0;
}

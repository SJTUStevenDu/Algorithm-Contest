/*
DATE : 2013-6-21 
RATING : 2
TAG : Suffix Array
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
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 200000 + 10;

int n,m;
char a[MAXN];
int rank[MAXN],sa[MAXN],wa[MAXN],wv[MAXN],wb[MAXN],ra[MAXN];

void BuildSA()
{
	a[n++]=0;
	int p=1,*x=wa,*y=wb;
	for(int i=0;i<m;i++) ra[i]=0;
	for(int i=0;i<n;i++) ra[x[i]=a[i]]++;
	for(int i=1;i<m;i++) ra[i]+=ra[i-1];
	for(int i=n-1;i>=0;i--) sa[--ra[x[i]]]=i;
	for(int j=1;p<n;j*=2)
	{
		p=0;
		for(int i=n-j;i<n;i++) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(int i=0;i<m;i++) ra[i]=0;
		for(int i=0;i<n;i++) ra[wv[i]=x[y[i]]]++;
		for(int i=1;i<m;i++) ra[i]+=ra[i-1];
		for(int i=n-1;i>=0;i--) sa[--ra[wv[i]]]=y[i];
		int *t=x;x=y;y=t;
		p=1;
		x[sa[0]]=0;
		for(int i=1;i<n;i++) 
			if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+j]==y[sa[i-1]+j]) x[sa[i]]=p-1;
			else x[sa[i]]=p++;
		m=p;
	}
}

int main()
{
	scanf("%s",a);
	n=strlen(a);
	for(int i=n;i<2*n;i++) a[i]=a[i-n];
	n=2*n-1;
	m=256;
	BuildSA();
	m=n/2;
	for(int i=0;i<n;i++) if(sa[i]<m) printf("%c",a[sa[i]+m-1]);
	printf("\n");
	
	return 0;
}

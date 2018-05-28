/*
DATE : 2013-03-22 
RATING : 3
TAG : Math
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 20000 + 10;

int t,n,d;
int sum;
int num[MAXN];
int prm[MAXN],top;
bool notPrime[MAXN];
int A[MAXN],B[MAXN];

void MakePrime()
{
	for(int i=2;i<=20010;i++)
	{
		if(!notPrime[i]) prm[++top]=i;
		for(int j=1;j<=top && i*j<=20010;j++) notPrime[i*j]=1;
	}
}

void Mul(int *S,int num)
{
	for(int i=1;i<=top;i++)
	{
		while(num%prm[i]==0) 
		{
			++S[i];
			num/=prm[i];
		}
		if(num==1) break;
	}
}

void Getgcd()
{
	for(int i=1;i<=top;i++) 
	{
		if(!A[i] || !B[i]) continue;
		if(A[i]>B[i]) A[i]-=B[i],B[i]=0;
		else B[i]-=A[i],A[i]=0;
	}
}

int arr[MAXN],len;

void Display(int *S)
{
	memset(arr,0,sizeof(arr));
	len=1;arr[1]=1;
	for(int i=1;i<=top;i++) 
	{
		for(int j=1;j<=S[i];j++) 
		{
			for(int k=1;k<=len;k++) arr[k]*=prm[i];
			for(int k=1;k<=len;k++) 
			{
				arr[k+1]+=arr[k]/10000;
				arr[k]%=10000;
				if(arr[len+1]) ++len;
			}
		}
	}
	printf("%d",arr[len]);
	for(int i=len-1;i;i--) printf("%04d",arr[i]);
}

int main()
{
	scanf("%d%d%d",&t,&n,&d);
	for(int i=1;i<=t;i++) scanf("%d",&num[i]),sum+=num[i];
	MakePrime();
	for(int a,b,i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		if(!num[b])
		{
			printf("0/0\n");
			return 0;
		}
		Mul(A,num[b]);
		Mul(B,sum);
		sum+=d;num[b]+=d;
	}
	Getgcd();
	Display(A);printf("/");Display(B);printf("\n");
	
	return 0;
}

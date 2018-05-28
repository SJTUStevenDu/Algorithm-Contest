#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

long long a,b,cnt1[15],cnt[15],Pow[15],ans,tmp,Digit[15];

void Solve(long long x,int y)
{
	if(x==0)
	{
		if(y!=0) tmp=0LL;
		else tmp=1LL;
		return;
	}
	long long sdifhdks=x;
	int len=0;
	while(sdifhdks) sdifhdks/=10,++len;
	long long Ttmp=x;
	int Llen=len;
	while(len)
	{
		int k=Ttmp/Pow[len];
		tmp+=k*Digit[len-1];
		if(y<k) tmp+=Pow[len];
		Ttmp=Ttmp%Pow[len];
		if(y==k) tmp+=Ttmp+1;
        len--;
	}
	if(!y)
	{
		for(int i=Llen;i>1;i--) tmp-=Pow[i];
	}
}

int main()
{
	scanf("%lld%lld",&a,&b);
	Pow[1]=1LL;
	for(int i=2;i<=12;i++) Pow[i]=Pow[i-1]*10;
	for(int i=2;i<=12;i++) Digit[i]=Pow[i]*i;
	Digit[1]=1LL;
	for(int i=0;i<=9;i++) 
	{
		tmp=0LL;
		Solve(a-1,i);
		ans=tmp;
		tmp=0LL;
		Solve(b,i);
		if(i!=9) printf("%lld ",tmp-ans);
		else printf("%lld\n",tmp-ans);
	}
	
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 500000 + 10;

int n,l,r,k,s[MAXN];
long long ans;

struct ST
{
	inline int min(int x,int y) {return s[x]<s[y] ? x : y;}
	int f[20][MAXN];
	void Build()
	{
		for(int i=1;i<=n;i++) f[0][i]=i;
		for(int j=1,p=2;p<=n+1;++j,p<<=1)
		{
			for(int i=0;i<=n-p+1;i++)
				f[j][i]=min(f[j-1][i],f[j-1][i+(p>>1)]);
		}
	}
	int ask(int x,int y)
	{
		int size=1,lgsize=0,len=y-x+1;
		while(size<=len) size<<=1,lgsize++;
		size>>=1;lgsize--;
		return min(f[lgsize][x],f[lgsize][y-size+1]);
	}
} T;

struct Heap_Node
{
	int sum,data,l,r,pos;
	bool operator<(const Heap_Node& p)const {return data<p.data;}
	bool operator>(const Heap_Node& p)const {return data>p.data;}
};

struct Heap
{
	Heap_Node Data[MAXN*4];
	int cnt;
	void Up(int x)
	{
		while(x!=1)
		{
			if(Data[x]>Data[x>>1]) swap(Data[x],Data[x>>1]),x>>=1;
			else break;
		}
	}
	void Down(int x)
	{
		while((x<<1)<=cnt)
		{
			x<<=1;
			if(x<cnt && Data[x+1]>Data[x]) x++;
			if(Data[x]>Data[x>>1]) swap(Data[x>>1],Data[x]);
			else break;
		}
	}
	void Insert(int sum,int l,int r)
	{
		++cnt;Data[cnt].sum=sum;Data[cnt].l=l;Data[cnt].r=r;
		Data[cnt].pos=T.ask(l,r);
		Data[cnt].data=Data[cnt].sum-s[Data[cnt].pos];
		Up(cnt);
	}
	void Pop()
	{
		swap(Data[1],Data[cnt]);
		--cnt;
		Down(1);
	}
	int Deal()
	{
		int d=Data[1].data;
		if(Data[1].pos>Data[1].l) Insert(Data[1].sum,Data[1].l,Data[1].pos-1);
		if(Data[1].pos<Data[1].r) Insert(Data[1].sum,Data[1].pos+1,Data[1].r);
		Pop();
		return d;
	}
} H;

int main()
{
	scanf("%d%d%d%d",&n,&k,&l,&r);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]),s[i]+=s[i-1];
	T.Build();
	for(int i=l;i<=n;i++) H.Insert(s[i],max(0,i-r),i-l);
	for(int i=1;i<=k;i++) ans+=H.Deal();
	printf("%lld\n",ans);
	
	return 0;
}

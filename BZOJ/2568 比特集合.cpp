#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

const int MAXN = (1<<16) + 10;

multiset <int> S;

char opr[20];
int n,s[20][MAXN],x,delay;

inline int lowbit(int x){return x&(-x);}

inline int Sum(int p,int x)
{
	int res=0;
	for(;x;x-=lowbit(x)) res+=s[p][x];
	return res;
}

inline void Add(int p,int x,int v)
{
	for(;x<=(1<<16);x+=lowbit(x)) s[p][x]+=v;
}

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",opr);
		scanf("%d",&x);
		if(opr[0]=='A') delay+=x;
		else if(opr[0]=='I')
		{
			S.insert(x-delay);
			for(int i=0;i<16;i++) Add(i,((x-delay)&((1<<(i+1))-1))+1,1);
		}
		else if(opr[0]=='D')
		{
			int t=S.count(x-delay);
			for(int i=0;i<16;i++) Add(i,((x-delay)&((1<<(i+1))-1))+1,-t);
			while(t--) S.erase(x-delay);
		}
		else 
		{
			int l=1<<x,r=(1<<x+1)-1,ans=0;
            ans += Sum(x, min(max(r - (delay & ((1 << x + 1) - 1)) + 1, 0), 1 << 16));
            ans -= Sum(x, min(max(l - (delay & ((1 << x + 1) - 1)), 0), 1 << 16));
            l+=1<<x+1,r+=1<<x+1;
            ans += Sum(x, min(max(r - (delay & ((1 << x + 1) - 1)) + 1, 0), 1 << 16));
            ans -= Sum(x, min(max(l - (delay & ((1 << x + 1) - 1)), 0), 1 << 16));
            printf("%d\n",ans);
		}
	}
	return 0;
}

/*
DATE : 2013-3-13 
RATING : 2
TAG : Binary Map
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000000 + 10;

struct Node 
{
	int to,next;
} g[MAXN*2];
int start[MAXN],gn;

int n,stk[MAXN],top,m;
int Link[MAXN];
bool vis[MAXN];

bool Find(int p)
{
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		if(vis[v]) continue;
		vis[v]=true;
		stk[++top]=v;
		if(!Link[v] || Find(Link[v]))
		{
			Link[v]=p;
			return true;
		}
	}
	return false;
}

inline int GetInt()
{
	char ch;
	int re=0;
	for(ch=getchar();ch<'0' || ch>'9';ch=getchar());
	for(;ch>='0' && ch<='9';ch=getchar()) re=re*10+ch-'0';
	return re;
}

inline void AddEdge(int a,int b)
{
	gn++;g[gn].to=b;g[gn].next=start[a];start[a]=gn;
}

int main()
{
	n=GetInt();
	for(int i=1;i<=n;++i)
	{
		int a,b;
		a=GetInt();b=GetInt();
		AddEdge(a,i);
		AddEdge(b,i);
		m=std::max(a,m);
		m=std::max(b,m);
	}
	++m;
	for(int i=1;i<=m;++i)
	{
		while(top)
		{
			int p=stk[top--];
			vis[p]=false;
		}
		if(!Find(i))
		{
			printf("%d\n",i-1);
			return 0;
		}
	}
	
	return 0;
}

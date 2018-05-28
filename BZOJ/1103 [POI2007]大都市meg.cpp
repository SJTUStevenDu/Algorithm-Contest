/*
DATE : 2013-3-3 
RATING : 2
TAG : BIT + DFS
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN=250005;

struct Edge{
	int to,next;
}g[MAXN*2];
int gn,start[MAXN];

void AddEdge(int a,int b)
{
	gn++,g[gn].to=b,g[gn].next=start[a],start[a]=gn;
}

inline int getint()
{
	int res=0;
	char t=getchar();
	for (;t>'9'||t<'0';t=getchar());
	for (;t>='0'&&t<='9';t=getchar()) res=res*10-'0'+t;
	return res;
}

int n,m;
int st[MAXN],en[MAXN];
int dep[MAXN];
int stk[MAXN][2];
bool vis[MAXN];
int num[MAXN];
int c[MAXN];

void Update(int x,int y)
{
	for (int i=x;i<=n;i+=i&(-i)) c[i]+=y;
}

int Query(int x)
{
	int res=0;
	for (int i=x;i;i-=i&(-i)) res+=c[i];
	return res;
}

void dfs()
{
	int top=1,len=1;
	stk[1][0]=1,stk[1][1]=start[1];
	vis[1]=true;
	while (top)
	{
		int p=stk[top][0];
		int k=stk[top][1];
		if (!st[p]) st[p]=len;
		en[p]=max(en[p],len);
		bool f=false;
		for (int i=k;i;i=g[i].next)
		{
			int v=g[i].to;
			if (vis[v]) continue;
			vis[v]=true;
			dep[v]=dep[p]+1;
			top++;
			len++;
			stk[top][0]=v;
			stk[top][1]=start[v];
			stk[top-1][1]=g[i].next;
			f=true;
			break;
		}
		if (f) continue;
		top--;
	}
	for (int i=1;i<=n;i++) num[st[i]]=dep[i];
	for (int i=1;i<=n;i++) Update(i,num[i]-num[i-1]);
}

int main()
{
	n=getint();
	for (int i=1;i<n;i++)
	{
		int a=getint(),b=getint();
		AddEdge(a,b);
		AddEdge(b,a);
	}
	dfs();
	m=n-1+getint();
	while (m--)
	{
		char opr=getchar();
		while (opr!='A'&&opr!='W') opr=getchar();
		if (opr=='W')
		{
			int x=getint();
			printf("%d\n",Query(st[x]));
		}
		else
		{
			int x=getint(),y=getint();
			if (dep[x]>dep[y]) swap(x,y);
			Update(st[y],-1);
			if (en[y]!=n) Update(en[y]+1,1);
		}
	}
	return 0;
}

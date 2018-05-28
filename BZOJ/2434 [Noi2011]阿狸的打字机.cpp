#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

const int MAXN = 100000 + 10;

typedef vector<pair<int,int> > PII;

struct Edge
{
	int next,to;
} g[MAXN];
int gn,start[MAXN];

inline void AddEdge(int a,int b)
{
	gn++;g[gn].next=start[a];start[a]=gn;g[gn].to=b;
}

int n,m,pn,head,tail;
int sum[MAXN],pos[MAXN],idx,Fail[MAXN],ans[MAXN],q[MAXN],nxt[MAXN][26],father[MAXN],dfn1[MAXN],dfn2[MAXN];
char opr[MAXN];
PII v[MAXN];

inline int lowbit(int x) {return x&(-x);}

inline void Add(int x,int v)
{
	for(;x<=idx;x+=lowbit(x)) sum[x]+=v;
}

inline int Query(int x)
{
	int res=0;
	for(;x;x-=lowbit(x)) res+=sum[x];
	return res;
}

void dfs(int p)
{
	dfn1[p]=dfn2[p]=++idx;
	for(int i=start[p];i;i=g[i].next)
	{
		int v=g[i].to;
		dfs(v);
		dfn2[p]=dfn2[v];
	}
}

int main()
{
	scanf("%s",opr);
	for(int i=0,x=0;opr[i]!='\0';i++)
	{
		if(opr[i]=='B')
		{
			x=father[x];
		}
		else if(opr[i]=='P')
		{
			pos[++n]=x;
		}
		else 
		{
			if(!nxt[x][opr[i]-'a']) nxt[x][opr[i]-'a']=++pn,father[pn]=x;
			x=nxt[x][opr[i]-'a'];
		}
	}
	for(int i=0;i<26;i++) if(nxt[0][i]) q[tail++]=nxt[0][i],AddEdge(0,nxt[0][i]);
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=0;i<26;i++)
		{
			if(nxt[p][i])
			{
				int x=Fail[p];
				for(;x && !nxt[x][i];x=Fail[x]);
				q[tail++]=nxt[p][i];
				Fail[q[tail-1]]=nxt[x][i];
				AddEdge(Fail[q[tail-1]],q[tail-1]);
			}
		}
	}
	dfs(0);
	scanf("%d",&m);
	for(int x,y,i=1;i<=m;i++) 
	{
		scanf("%d%d",&x,&y);
		v[y].push_back(make_pair(pos[x],i));
	}
	n=0;
	Add(dfn1[0],1);
	for(int x=0,i=0;opr[i]!='\0';i++)
	{
		if(opr[i]=='B')
		{
			Add(dfn1[x],-1);
			x=father[x];
		}
		else if(opr[i]=='P')
		{
			for(PII::iterator it=v[++n].begin();it!=v[n].end();it++) ans[it->second]+=Query(dfn2[it->first])-Query(dfn1[it->first]-1);
		}
		else 
		{
			Add(dfn1[nxt[x][opr[i]-'a']],1);
			x=nxt[x][opr[i]-'a'];
		}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	
	return 0;
}

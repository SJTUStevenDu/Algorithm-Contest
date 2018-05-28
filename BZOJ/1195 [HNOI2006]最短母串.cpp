#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

const int MAXN = 50 * 12 + 10;
const int MAXS = MAXN * (1<<12);

int n,head,tail,ans[MAXN],pn;
int nxt[MAXN][26],g[MAXN],lst[MAXS],Fail[MAXN];
short rst[MAXS],c[MAXS],q[MAXS];
bool vis[MAXN][1<<13];
char str[MAXN];

int main()
{
	scanf("%d",&n);
	for(int z=0;z<n;z++)
	{
		scanf("%s",str);
		int x=0;
		for(int i=0;str[i]!='\0';i++)
		{
			if(!nxt[x][str[i]-'A']) nxt[x][str[i]-'A']=++pn;
			x=nxt[x][str[i]-'A'];
		}
		g[x] |= (1<<z);
	}
	for(int k=0;k<26;k++) if(nxt[0][k]) q[tail++]=nxt[0][k];
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=0;i<26;i++) if(nxt[p][i])
		{
			int x=Fail[p];
			for(;x && !nxt[x][i];x=Fail[x]);
			Fail[nxt[p][i]]=nxt[x][i];
			q[tail++]=nxt[p][i];
			g[nxt[p][i]]|=g[nxt[x][i]];
		}
		else 
		{
			int x=Fail[p];
			for(;x && !nxt[x][i];x=Fail[x]);
			nxt[p][i]=nxt[x][i];
		}
	}
	head=tail=0;
	q[tail++]=0;
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=0;i<26;i++)
			if(!vis[nxt[p][i]][rst[head] | g[nxt[p][i]]])
			{
				q[tail++]=nxt[p][i];
				rst[tail] = rst[head] | g[nxt[p][i]];
				lst[tail] = head;
				c[tail]=i;
				vis[nxt[p][i]][rst[tail]]=1;
				if(rst[tail]==(1<<n)-1)
				{
					for(int z=tail;z;z=lst[z]) ans[++ans[0]]=c[z];
					for(int z=ans[0]-1;z;z--) printf("%c",ans[z]+'A');
					printf("\n");
					return 0;
				}
			}
	}
	
	return 0;
}

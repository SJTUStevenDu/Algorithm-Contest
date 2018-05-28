/*
DATE : 2013-3-31 
RATING : 3
TAG : AC×Ô¶¯»ú 
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

const int MAXN = 60 * 100 + 10;
const int MAXL = 100 + 10;
const int MOD = 10007;

struct Trie
{
	int son[26],fail;
	bool flag;
} AC[MAXN];

int pn,n,m,dp[MAXL][MAXN][2],ro,ans;
char S[MAXL];

inline void NewNode(int &p) {p=++pn;}

void Insert()
{
	int len=strlen(S);
	int p=ro;
	for(int i=0;i<len;i++)
	{
		int x=S[i]-'A';
		if(!AC[p].son[x]) NewNode(AC[p].son[x]);
		p=AC[p].son[x];
	}
	
	AC[p].flag=1;
}

int q[MAXN],head,tail=1;

void Build()
{
	q[head]=ro;
	while(head!=tail)
	{
		int p=q[head++];
		for(int i=0;i<26;i++)
		{
			int v=(p==ro) ? ro : AC[AC[p].fail].son[i];
			if(!AC[p].son[i]) AC[p].son[i]=v;
			else AC[AC[p].son[i]].fail=v,AC[AC[p].son[i]].flag|=AC[v].flag,q[tail++]=AC[p].son[i];
		}
	}
}

int main()
{
	scanf("%d%d",&m,&n);
	NewNode(ro);
	while(m--)
	{
		scanf("%s",S);
		Insert();
	}
	Build();
	dp[0][ro][0]=1;
	for(int i=0;i<n;i++) 
	{
		for(int j=1;j<=pn;j++) 
		{
			for(int x=0;x<26;x++)
			{
				int p=AC[j].son[x];
				if(AC[p].flag) dp[i+1][p][1]=(dp[i+1][p][1]+(dp[i][j][0]+dp[i][j][1])%MOD)%MOD;
				else dp[i+1][p][0]=(dp[i+1][p][0]+dp[i][j][0])%MOD,dp[i+1][p][1]=(dp[i+1][p][1]+dp[i][j][1])%MOD;
			}
		}
	}
	for(int i=1;i<=pn;i++) ans=(ans+dp[n][i][1])%MOD;
	printf("%d\n",ans);
	
	return 0;
}

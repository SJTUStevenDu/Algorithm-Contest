/*
DATE : 2012-11-30 
RATING : 1
TAG : 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 1000000 + 5;

int n,dat[MAXN],cnt[MAXM],ans[MAXM],maxx;
bool vis[MAXM],ex[MAXM];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&dat[i]);
		ex[dat[i]]=1;
		cnt[dat[i]]++;
		maxx=max(maxx,dat[i]);
	}
	for(int i=1;i<=n;i++) if(!vis[dat[i]])
	{
		int tmp=dat[i]*2;
		ans[dat[i]]+=cnt[dat[i]]-1;
		while(tmp<=maxx)
		{
			if(ex[tmp]) ans[tmp]+=cnt[dat[i]];
			tmp+=dat[i];
		}
		vis[dat[i]]=1;
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[dat[i]]);

	return 0;
}

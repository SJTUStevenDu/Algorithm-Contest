/*
DATE : 2013-5-23 
RATING : 2
TAG : Enum
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <map>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 50 + 10;

int n[5],sum;
char ch[4][MAXN];
int ans=0x7FFFFFFF;

int main()
{
	for(int i=1;i<=3;i++) 
	{
		scanf("%d",&n[i]);
		getchar();
		for(int j=1;j<=n[i];j++) ch[i][j]=getchar();
	}
	for(int i=1;i<=3;i++)
		for(int j=1;j<i;j++)
		{
			int len=1;
			while(ch[i][len]==ch[j][len] && len<=n[i] && len<=n[j]) len++;
			len--;
			sum=0;
			for(int k=1;k<=3;k++) if(i==k || j==k) sum+=n[k]-len;
			else 
			{
				int l;
				for(l=1;l<=n[k];l++) if(ch[k][l]!=ch[i][l] || ch[k][l]!=ch[j][l]) break;
				--l;
				sum+=(n[k]-l);
				sum+=(len-l);
			}
			ans=min(ans,sum);
		}
	printf("%d\n",ans);
	
	return 0;
}

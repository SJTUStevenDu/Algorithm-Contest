/*
DATE : 2012-12-12 
RATING : 1
TAG : Ã¶¾Ù 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 100 + 5;

int n,map[MAXN][MAXN];
int ans;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++)
		{
			char ch;
			cin>>ch;
			if(ch=='J') map[i][j]=1;
			else if(ch=='B') map[i][j]=-100;
		}
	for(int x1=1;x1<=n;x1++) 
		for(int y1=1;y1<=n;y1++)
			for(int x2=1;x2<=n;x2++)
				for(int y2=1;y2<=n;y2++)
				{
					int S=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
					if(S<=ans) continue;
					int dx=abs(x1-x2);
					int dy=abs(y1-y2);
					int x3=x1+dy,y3=y1+dx;
					int x4=x2+dy,y4=y2+dx;
					int tmp=0;
					if(x1>0 && x1<=n && y1>0 && y1<=n) tmp+=map[x1][y1];else tmp=-100;
					if(x2>0 && x2<=n && y2>0 && y2<=n) tmp+=map[x2][y2];else tmp=-100;
					if(x3>0 && x3<=n && y3>0 && y3<=n) tmp+=map[x3][y3];else tmp=-100;
					if(x4>0 && x4<=n && y4>0 && y4<=n) tmp+=map[x4][y4];else tmp=-100;
					if(tmp>=3) ans=S;
				}
	printf("%d\n",ans);
	
	return 0;
}

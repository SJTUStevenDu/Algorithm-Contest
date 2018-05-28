/*
DATE : 2013-5-22 
RATING : 2
TAG : BFS
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

const int MAXN = 1<<17;
const int gx[4]={1,0,-1,0};
const int gy[4]={0,1,0,-1};

int dist[MAXN];
int q[MAXN],head,tail;
int st,en;

inline int f(int i,int j) {return (i-1)*4+j-1;}

int main()
{
	char ch=getchar();
	for(int i=1;i<=4;i++)
	{
		for(;ch!='0' && ch!='1';ch=getchar());
		for(int j=1;j<=4;j++) {if(ch=='1') st|=(1<<f(i,j)); ch=getchar();}
	}
	for(int i=1;i<=4;i++)
	{
		for(;ch!='0' && ch!='1';ch=getchar());
		for(int j=1;j<=4;j++) {if(ch=='1') en|=(1<<f(i,j)); ch=getchar();}
	}
	q[head=0]=st;tail=1;
	while(head!=tail)
	{
		int p=q[head++];
		if(p==en) break;
		for(int x=1;x<=4;x++)
			for(int y=1;y<=4;y++) if(p & (1<<f(x,y)))
				for(int k=0;k<4;k++)
				{
					int px=gx[k]+x;
					int py=gy[k]+y;
					if(p & (1<<f(px,py))) continue;
					if(px<1 || px>4 || py<1 || py>4 || dist[p ^ (1<<f(x,y)) | (1<<f(px,py))]) continue;
					dist[p ^ (1<<f(x,y)) | (1<<f(px,py))]=dist[p]+1;
					q[tail++]=(p ^ (1<<f(x,y)) | (1<<f(px,py)));
				}
	}
	printf("%d\n",dist[en]);
	
	return 0;
}

/*
DATE : 2013-2-12 
RATING : 3
TAG : ·Ö²ãÍ¼×î¶ÌÂ· 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXV=10005;
const int MAXE=100005;
const int MAXK=25;
const int INF=1000000000;
 
struct G{
	int to,next,d;
}g[MAXE];
int gn,start[MAXV];

struct H{
	int d,num;
}heap[MAXV*MAXK];
int hlen; 
int pos[MAXV*MAXK];

int n,m,k,N,S,T;

inline void Add(int a,int b,int d)
{
	gn++,g[gn].to=b,g[gn].d=d,g[gn].next=start[a],start[a]=gn; 
}

inline void Swap(int a,int b)
{
	swap(heap[a],heap[b]);
	pos[heap[a].num]=a;
	pos[heap[b].num]=b; 
}

inline void Up(int x)
{
	while (x>1&&heap[x].d<heap[x/2].d)
	{
		Swap(x,x/2);
		x/=2; 
	} 
}

inline void Down(int x)
{
	int y; 
	while ((x*2<=hlen&&heap[x*2].d<heap[x].d)||(x*2+1<=hlen&&heap[x*2+1].d<heap[x].d))
	{
		y=x*2;
		if (x*2+1<=hlen&&heap[x*2+1].d<heap[x*2].d) y++;
		Swap(x,y);
		x=y; 
	} 
}

inline void Relax(int a,int b,int d)
{
	if (heap[pos[b]].d>heap[pos[a]].d+d)
	{
		heap[pos[b]].d=heap[pos[a]].d+d;
		Up(pos[b]); 
	}
}

void Build_Heap()
{
	for (int i=1;i<=N;i++)
	{
		heap[i].d=INF;
		heap[i].num=i;
		pos[i]=i; 
	}
	hlen=N; 
	for (int i=S;i<=N;i+=n)
	{
		heap[i].d=0;
		Up(pos[i]); 
	}
}
 
void Init()
{ 
	scanf("%d%d%d",&n,&m,&k); 
	N=n*(k+1);
	scanf("%d %d",&S,&T);
	S++;T++;
	T+=n*k;
	int a,b,c;
	while (m--)
	{
		scanf("%d%d%d",&a,&b,&c);
		a++;b++;
		Add(a,b,c);
		Add(b,a,c);
	}
	Build_Heap(); 
}

void Solve()
{
	while (hlen>1)
	{
		int p=heap[1].num;
		int p0=p-((p-1)/n)*n;
		Swap(1,hlen--);
		Down(1);
		for (int i=start[p0];i;i=g[i].next)
		{
			int v=g[i].to,d=g[i].d;
			for (int j=v;j<=N;j+=n)
			{
				int f=(j-1)/n-(p-1)/n;
				if (f==0) Relax(p,j,d);
				if (f>0) Relax(p,j,0); 
			} 
		} 
	} 
	printf("%d\n",heap[pos[T]].d); 
}

int main()
{
	Init(); 
	Solve();
	return 0;
}

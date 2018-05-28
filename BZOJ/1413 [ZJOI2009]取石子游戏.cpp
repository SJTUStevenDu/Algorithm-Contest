/*
DATE : 2013-4-3 
RATING : 3
TAG : DP
*/

#include <cstdio>
#include <cstring>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 1000 + 10;

int n,left[MAXN][MAXN],right[MAXN][MAXN],a[MAXN],T;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=n;i++) left[i][i]=right[i][i]=a[i];
		for(int l=1;l<n;l++) 
			for(int i=1;i<=n-l;i++) 
			{
				int j=i+l;
				int L,R,X;
				L=left[i][j-1];R=right[i][j-1];X=a[j];
				if(R==X) left[i][j]=0;
				else if((L<X && R<X) || (L>X && R>X)) left[i][j]=X;
				else if(L>R) left[i][j]=X-1;
				else left[i][j]=X+1;
				L=left[i+1][j];R=right[i+1][j];X=a[i];
				if(L==X) right[i][j]=0;
				else if((L<X && R<X) && (L>X && R>X)) right[i][j]=X;
				else if(L<R) right[i][j]=X-1;
				else right[i][j]=X+1;
			}
		if(n==1) printf("1\n");
		else printf("%d\n",a[1]!=left[2][n]);
	}
	
	
	return 0;
}

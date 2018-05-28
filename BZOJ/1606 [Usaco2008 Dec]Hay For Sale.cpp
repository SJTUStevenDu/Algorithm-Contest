/*
DATE : 2012-09-20
RATING : 1
TAG : Greedy
*/

#include <cstdio>
 
bool f[50009];
int a[5009];
 
int main()
{
    int c,n;
    while(scanf("%d%d",&c,&n)!=EOF)
    {
        for(int i=1;i<=c;i++)
        f[i]=0;
        for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
        f[0]=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=c;j>=a[i];j--)
            {
                if(f[j-a[i]]==1)
                f[j]=1;
            }
        if(f[c]==1) break;
        }
        for(int i=c;i>0;i--) if(f[i]==1) {printf("%d\n",i);break;}
    }   
    return 0;
}
/*
DATE : 2013-3-25 
RATING : 2
TAG : Math
*/
 
#include <cstdio>
#include <cstring>
 
//Orz WJMZBMR && sevenkplus

using namespace std;

unsigned long long Pow[61],ans,tmp;
int T,a;

int main()
{
	scanf("%d",&T);
	Pow[0]=1ULL;
    for(int i=1;i<=60;i++) Pow[i]=Pow[i-1]<<1;
    while(T--)
    {
        ans=0ULL;
        for(int i=1;i<=8;i++) 
        {
            scanf("%d",&a);
            ans+=Pow[a];
        }
        scanf("%llu",&tmp);
        if(ans==9223372036854775808ULL && tmp==9223372036854775808ULL) printf("18446744073709551616\n");
        else if(ans==9223372036854775807ULL && tmp==9223372036854775808ULL) printf("18446744073709551615\n");
        else if(ans==9223372036854775808ULL && tmp==9223372036854775807ULL) printf("18446744073709551615\n");
        else printf("%llu\n",ans+tmp);
    }
    return 0;
}

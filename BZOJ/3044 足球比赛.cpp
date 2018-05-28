#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int a, b, c, d, x, y, t;
char pos[10];

int main()
{
	scanf("%d\n", &t);
	while (t--)
	{
		scanf("%*s%*s%*s"); scanf("%s", pos); scanf("%*s%*s"); scanf("%d", &x); scanf("%*s%*s%*s"); scanf("%d",&y); scanf("%*s");
		if(pos[0]=='h')
		{
			a = x, b = y, d = 0;
			c = b + d - a;
			if (c < b) c++;
			c = max(c, 0);
			printf("%d ", c);
			d = 30; c = b + d - a;
			if (c > b) c--;
			c = max(min(c, 30), 0);
			printf("%d\n", c);
		}
		else
		{
			c = x, d = y; b = 0;
			a = max(b + d - c, 0);
			printf("%d ", a);
			b = 30;
			a = max(min(b + d - c, 30), 0);
			printf("%d\n", a);
		}
	}
	return 0;
}

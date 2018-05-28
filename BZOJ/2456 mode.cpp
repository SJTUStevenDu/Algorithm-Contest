#include <cstdio>

using namespace std;

int n, ans, cnt, x;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &x);
		if (cnt == 0) 
		{
			ans = x;
			cnt = 1;
		}
		else if (ans == x) ++cnt;
		else --cnt;
	}
	printf("%d\n", ans);
	
	return 0;
}

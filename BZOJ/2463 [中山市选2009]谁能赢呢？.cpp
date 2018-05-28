#include <cstdio>

using namespace std;

int n;

int main()
{
	while (scanf("%d", &n))
	{
		if (!n) break;
		if (n & 1) puts("Bob");
		else puts("Alice");
	}
	
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAXN = 100000 + 10;

int n = 100000, l = 13;
char s[MAXN];

int main()
{
	for (int i = 0; i < n; ++i) s[i] = rand() % 26 + 'a';
	s[n] = '\0';
	printf("%d %d\n", n, l);
	printf("%s", s);
	
	return 0;
}

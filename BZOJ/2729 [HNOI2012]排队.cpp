#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
const int BASE = 100000;
const int MAXN = 10000 + 10;
 
struct BigNum
{
    int a[MAXN];
    int len;
    BigNum() {memset(a, 0, sizeof(a)); len = 1;}
    void Minus(BigNum A)
    {
        for (int i = 1; i <= len; ++i) a[i] -= A.a[i];
        for (int i = 1; i <= len; ++i) while(a[i] < 0) a[i] += BASE, a[i + 1]--;
        for (; len > 1 && !a[len]; --len);
    }
    void Mul(int x)
    {
        for (int i = 1; i <= len; ++i) a[i] *= x;
        for (int i = 1; i <= len; ++i)
        {
            a[i + 1] += a[i] / BASE;
            a[i] %= BASE;
            if (a[len + 1]) ++len;
        }
    }
    void Print()
    {
        printf("%d", a[len]);
        for (int i = len - 1; i; --i) printf("%05d", a[i]);
        putchar('\n');
    }
} ans, ans2;
 
int n, m;
 
int main()
{
    scanf("%d%d", &n, &m);
    ans.a[1] = 1;
    for (int i = 1; i <= n + 2; ++i) ans.Mul(i);
    for (int i = n - m + 4; i <= n + 3; ++i) ans.Mul(i);
    ans2.a[1] = 2;
    for (int i = 1; i <= n + 1; ++i) ans2.Mul(i);
    for (int i = n - m + 3; i <= n + 2; ++i) ans2.Mul(i);
    ans.Minus(ans2);
    ans.Print();
    return 0;
}

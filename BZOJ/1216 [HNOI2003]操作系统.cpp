#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct node 
{
    int Nu,Ti,Co,Ad;
    node (int _Nu, int _Ti, int _Co, int _Ad):Nu(_Nu), Ti(_Ti), Co(_Co), Ad(_Ad) {}
};

struct cmp 
{
    bool operator()(node x, node y) {return (x.Ad < y.Ad) || (x.Ad == y.Ad && x.Ti > y.Ti);}
};

priority_queue<node,vector<node>,cmp>Q; 
int Time, N, T, C, A;
 
void Move()
{
    int delta;
    while (Time < T && (!Q.empty()))
	{
        node u = Q.top();
        Q.pop();
        Time = max(Time, u.Ti);
        delta = min(u.Co, T - Time);
        u.Co -= delta; Time += delta;
        if (u.Co) Q.push(u); else printf("%d %d\n", u.Nu, Time);
    }
}
 
int main() 
{
	while (!Q.empty()) Q.pop();
    while (scanf("%d%d%d%d", &N, &T, &C, &A) != EOF) 
	{
        Move();
        Q.push(node(N, T, C, A));
    }
    while (!Q.empty())
	{
        node u = Q.top();
        Q.pop();
        printf("%d %d\n", u.Nu, Time += u.Co);
    }
    return 0;
}

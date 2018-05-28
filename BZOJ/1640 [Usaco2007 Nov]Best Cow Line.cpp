/*
DATE : 2012-12-6 
RATING : 1
TAG : Greedy
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

//Orz WJMZBMR && sevenkplus

using namespace std;

const int MAXN = 2000 + 5;

int n,head,tail;
char ch[MAXN];
string s;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>ch[i];
	head=1;tail=n;
	while(head<=tail)
	{
		if(ch[head]<ch[tail]) s+=ch[head++];
		else if(ch[head]>ch[tail]) s+=ch[tail--];
		else
		{
			int x=head+1,y=tail-1;
			while(ch[x]==ch[y]) x++,y--;
			if(ch[x]>ch[y]) s+=ch[tail--];
			else s+=ch[head++];
		}
	}
	for(int i=0;i<s.size();i++) 
	{
		cout<<s[i];
		if(i%80==79) cout<<endl;
	}
	if(s.size()%80!=0) cout<<endl;
	
	return 0;
}

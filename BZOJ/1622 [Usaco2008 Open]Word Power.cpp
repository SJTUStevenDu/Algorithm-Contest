#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

int n,m;
string a[1005],b[105];

char lower(char a)
{
	if(a<='Z') return a-'A'+'a';
	else return a;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=n;i++)
		for(int j=0;j<a[i].size();j++) a[i][j]=lower(a[i][j]);
	for(int i=1;i<=m;i++)
		for(int j=0;j<b[i].size();j++) b[i][j]=lower(b[i][j]);
	for(int i=1;i<=n;i++) 
	{
		int ans=0;
		for(int j=1;j<=m;j++) 
		{
			int pa=0,pb=0;
			while(pa<a[i].size())
			{
				//if(pb==b[j].size()) break;
				if(a[i][pa]==b[j][pb]) pb++;
				pa++;
			}
			if(pb==b[j].size()) ans++;
		}
		cout<<ans<<endl;
	}
	
	return 0;
}

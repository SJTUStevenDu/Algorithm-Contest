/*
DATE : 2013-3-5 
RATING : 1
TAG : 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
 
using namespace std;
 
const int MAXN=105;
int n,tot;
int len[MAXN];
string tmp[MAXN][MAXN];
string ans[MAXN];
 
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>len[i];len[i]++;tot=max(tot,len[i]);
        for (int j=1;j<=len[i];j++) cin>>tmp[i][j];
    }
    for(int i=1;i<=n;i++)
    {
        int cntmax=0,cnt[MAXN]; memset(cnt,0,sizeof(cnt));
        for(int j=1;j<=tot;j++)
        {
            ans[j]+=tmp[i][j];
            int ll=tmp[i][j].length();
            for (int k=0;k<ll;k++) if (tmp[i][j][k]==',') cnt[j]++;
            cntmax=max(cntmax,cnt[j]);
        }
        if(i!=n) cntmax++;
        for(int j=1;j<=tot;j++) for(int k=cnt[j]+1;k<=cntmax;k++) ans[j]+=',';
    }
    for(int i=1;i<=tot;i++) cout<<ans[i]<<endl;
    return 0;
}

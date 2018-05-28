/*
DATE : 2013-1-18 
RATING : 1
TAG : High
*/
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
 
//Orz WJMZBMR && sevenkplus
 
using namespace std;
 
string numa,numb;
int a[100],b[100],ans[200],len;
 
int main()
{
    cin>>numa;
    cin>>numb;
    for(int i=numa.size()-1;i>=0;i--) a[numa.size()-i]=numa[i]-'0';
    for(int i=numb.size()-1;i>=0;i--) b[numb.size()-i]=numb[i]-'0';
    for(int i=1;i<=numa.size();i++)
        for(int j=1;j<=numb.size();j++)
            ans[i+j-1]+=a[i]*b[j];
    len=numa.size()+numb.size()-1;
    for(int i=1;i<=len;i++)
    {
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
        if(ans[len+1]) len++;
    }
    for(int i=len;i;i--) cout<<ans[i];
    cout<<endl;
     
    return 0;
}

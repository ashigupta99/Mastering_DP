#include<bits/stdc++.h>
using namespace std;
int fun(unordered_map<int,int> &m, int n){
    if(n==1) return 0;
    if(m.find(n)!=m.end()) return m[n];
    if(n%2==0) return m[n]=1+fun(m,n/2);
    else return m[n]=1+min(fun(m,n-1),fun(m,n+1));
}
int main(){
    int n;
    cin>>n;
    unordered_map<int,int> m;
    int ans= fun(m,n);
    cout<<ans;
}
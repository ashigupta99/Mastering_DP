#include<bits/stdc++.h>
using namespace std;
unordered_map<long long int,long long int> m;
const long long int cons= 998244353;
const int maxe= 100001;
vector<long long int> powe(maxe);
void precomp(){
    powe[0]=1;
    for(int i=1;i<maxe;i++) powe[i]=(2LL*powe[i-1])%cons;
}
void fun(int n, vector<int> &p, vector<int> &q, vector<long long int> &ans){
    int pmx=p[0],qmx=q[0],pmx_ind=0,qmx_ind=0;
    for(int i=0;i<n;i++){
        if(p[i]>pmx){
            pmx=p[i];
            pmx_ind=i;
        }
        if(q[i]>qmx){
            qmx=q[i];
            qmx_ind=i;
        }
        if(pmx>qmx) ans[i]=(powe[pmx]+powe[q[i-pmx_ind]])%cons;
        else if(qmx>pmx) ans[i]=(powe[qmx]+powe[p[i-qmx_ind]])%cons;
        else{
            int l=(p[i-qmx_ind]>q[i-pmx_ind])?p[i-qmx_ind]:q[i-pmx_ind];
            int r=(p[i-qmx_ind]>q[i-pmx_ind])?qmx:pmx;
            ans[i]=(powe[l]+powe[r])%cons;
        }
    }
}
int main(){
    int t;
    cin>>t;
    precomp();
    while(t--){
        int n;
        cin>>n;
        vector<int> p(n);
        for(int i=0;i<n;i++) cin>>p[i];
        vector<int> q(n);
        for(int i=0;i<n;i++) cin>>q[i];
        vector<long long int> ans(n);
        fun(n,p,q,ans);
        for(int i=0;i<n;i++) cout<<ans[i]<<" ";
        cout<<endl;
    }
}
// TC- O(n.log n)
// SC- O(n)

#include<bits/stdc++.h>
using namespace std;

int max_loc(int, vector<int>&);

int main(){
    int n;
    cout<<"Enter the number of elements in the array: ";
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) {
        cout<<"Enter elem "<<i+1<<": ";
        cin>>arr[i];
    }
    int ans= max_loc(n,arr);
    cout<<"The maximum number of locations are: "<<ans;
}


int max_loc(int n, vector<int>& arr){
    vector<int> dp;
    for(int i=0;i<n;i++){
        auto it= lower_bound(dp.begin(),dp.end(), arr[i]);
        if(it==dp.end()) dp.push_back(arr[i]);
        else *it=arr[i];
    }
    return dp.size();
}

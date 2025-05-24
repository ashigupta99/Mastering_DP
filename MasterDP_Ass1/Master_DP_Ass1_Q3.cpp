// TC- O(n+k) where k is the maximum element
// SC- O(k)

#include<bits/stdc++.h>
using namespace std;

void sort_count(int, vector<int>&);

int main(){
    int n;
    cout<<"Enter the number of elements in the array: ";
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) {
        cout<<"Enter elem "<<i+1<<": ";
        cin>>arr[i];
    }
    cout<<"\nOriginal array:"<<endl;
    for(int i=0;i<n;i++) {
        cout<<arr[i]<<" ";
    }
    sort_count(n,arr);
    cout<<"\nSorted array:"<<endl;
    for(int i=0;i<n;i++) {
        cout<<arr[i]<<" ";
    }
}


void sort_count(int n, vector<int>& arr){
    int maxm= *max_element(arr.begin(),arr.end());
    vector<int> dp(maxm+1, 0);
    for(int i=0;i<n;i++){
        dp[arr[i]]++;
    }
    int ind=0;
    for(int i=0;i<=maxm;i++){
        while(dp[i]){
            arr[ind++]=i;
            dp[i]--;
        }
    }
}
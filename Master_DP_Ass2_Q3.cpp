#include<bits/stdc++.h>
using namespace std;
int robb(vector<int>&nums, int s, int e){
    int curr=0,prev=0;
    for(int i=s;i<=e;i++){
        int temp=curr;
        curr=max(curr,prev+nums[i]);
        prev=temp;
    }
    return curr;
}
int rob(vector<int>& nums) {
    if(nums.size()==1) return nums[0];
    if(nums.size()==2) return max(nums[0],nums[1]);
    return max(robb(nums,0,nums.size()-2),robb(nums,1,nums.size()-1));
}
int main(){
    vector<int> nums;
    int c;
    while(1){
        cin>>c;
        if(c==-1) break;
        else nums.push_back(c);
    }
    int ans=rob(nums);
    cout<<ans;
}
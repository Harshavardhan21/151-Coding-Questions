class Solution {
public:

    void check(vector<int>&candidates, int target, vector<vector<int>>&ans, vector<int>temp, int sum, int index){
        if(sum==target){
            ans.push_back(temp);
            return;
        }
        if(sum>target || index>=candidates.size()){
            return;
        }
        for(int i=index;i<candidates.size();i++){
            // i > index added because to avoid duplicates.
            if(i>index&&candidates[i-1]==candidates[i]){
                continue;
            }
            temp.push_back(candidates[i]);
            check(candidates,target,ans,temp,sum+candidates[i],i+1);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>>ans;
        vector<int>temp;
        sort(candidates.begin(),candidates.end());
        int sum=0;
        check(candidates,target, ans,temp,sum,0);
        return ans;
    }
};
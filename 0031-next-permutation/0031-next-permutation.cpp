class Solution {
public:
    vector<int> nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int ind = -1;
        if (n==1) return nums;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) { // overflow solution required
                ind = i;
                break;
            }
            // else if(nums[i]>nums[i+1]){
            //     return {0};
            // }
        }
        if(ind==-1) {
            reverse(nums.begin(),nums.end());
            return nums;
        }
        for (int i = n - 1; i >ind; i--) {
            if (nums[i] > nums[ind]) {
                swap(nums[i], nums[ind]);
                break;
            }
        }
        reverse(nums.begin()+ind+1,nums.end());
        return nums;
    }
};
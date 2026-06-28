class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cn1 = 0, cn2 = 0;
        int el1 = nums[0], el2 = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (cn1 == 0 && nums[i] != el2) {
                cn1 = 1, el1 = nums[i];
            } else if (cn2 == 0 && nums[i] != el1) {
                cn2 = 1, el2 = nums[i];
            } else if (el1 == nums[i])
                cn1++;
            else if (el2 == nums[i])
                cn2++;
            else
                cn1--, cn2--;
        }
        int count1 = 0, count2 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == el1)
                count1++;
            else if (nums[i] == el2)
                count2++;
        }

        if (count1 > n / 3 && count2 > n / 3)
            return {el1, el2};
        else if (count1 > n / 3 && count2 <= n / 3)
            return {el1};
        else if (count2 > n / 3 && count1 <= n / 3)
            return {el2};
        else return {};

       
    }
};
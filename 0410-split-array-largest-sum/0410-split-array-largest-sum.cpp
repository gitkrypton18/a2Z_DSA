class Solution {
public:
    bool isValid(vector<int>& nums, int barrier, int k) {
        int parts = 1;
        long long sum = 0;

        for (int num : nums) {
            if (sum + num > barrier) {
                parts++;
                sum = num;

                if (parts > k)
                    return false;
            } else {
                sum += num;
            }
        }

        return true;
    }

    int splitArray(vector<int>& nums, int k) {
        int low = *max_element(nums.begin(), nums.end());
        long long high = accumulate(nums.begin(), nums.end(), 0LL);

        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isValid(nums, mid, k)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
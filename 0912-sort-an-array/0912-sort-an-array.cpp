class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {

        vector<int> freq(100001, 0);

        for(int x : nums) {
            freq[x + 50000]++;
        }

        int idx = 0;

        for(int i = 0; i < 100001; i++) {

            while(freq[i]--) {
                nums[idx++] = i - 50000;
            }
        }

        return nums;
    }
};
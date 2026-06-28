class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();
        if (k==0||k%n==0) return;

        // Normalize k if greater than n
        k = k % n;

        // Store last k elements in a temporary array
        int temp[k];
        for (int i = n - k; i < n; i++) {
            temp[i - n + k] = nums[i];
        }

        // Shift the first n-k elements to the right by k steps
        for (int i = n - k - 1; i >= 0; i--) {
            nums[i + k] = nums[i];
        }

        // Copy back the k elements to the start
        for (int i = 0; i < k; i++) {
            nums[i] = temp[i];
        }
    }
};
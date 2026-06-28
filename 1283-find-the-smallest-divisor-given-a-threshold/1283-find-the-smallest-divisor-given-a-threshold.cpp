class Solution {
public:
    int sumofdivisor(vector<int>& arr, int div) {
        long long sum = 0, n = arr.size();
        for (int i = 0; i < n; i++) {
            sum = sum + (arr[i] + div - 1) / div;
        }
        return sum;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n = nums.size();
        long long low = 1, high = *max_element(nums.begin(), nums.end());
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if ((sumofdivisor(nums, mid)) <= threshold)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return low;
    }
};
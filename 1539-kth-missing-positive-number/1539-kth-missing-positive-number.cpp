class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int n = arr.size();
        int low = 0, high = n - 1, missing = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            missing = arr[mid] - (mid + 1);
            if (missing < k)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low + k;
    }
};
class Solution {
public:
    int daysReq(vector<int>& weights, int capacity) {
        int day = 1, load = 0;
        int n = weights.size();
        for (int i = 0; i < n; i++) {
            if (load + weights[i] > capacity) {
                day += 1;
                load = weights[i];
            } else
                load += weights[i];
        }
        return day;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        long long low = *max_element(weights.begin(), weights.end());
        long long high = accumulate(weights.begin(), weights.end(), 0LL);
        while (low <= high) {
            long long mid = (low + high) / 2;
            if (daysReq(weights, mid) <= days)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return low;
    }
};
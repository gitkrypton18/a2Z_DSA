#include <algorithm>
class Solution {
public:
    bool possible(vector<int>& arr, int day, int m, int k) {
        int cnt = 0, no_boq = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] <= day)
                cnt++;
            else
                no_boq += cnt / k, cnt = 0;
        }
        no_boq += cnt / k;
        return (no_boq >= m);
           
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if (n < 1LL * m * k)
            return -1;
        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());
        int ans = high;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (possible(bloomDay, mid, m, k) == true)
                ans = mid, high = mid - 1;
            else
                low = mid + 1;
        }
        return low;
    }
};
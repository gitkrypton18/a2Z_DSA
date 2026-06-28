class Solution {
public:
    int maxProfit(vector<int>& a) {
        int n = a.size();
        int cost;
        int mini = a[0], profit = 0;
        for (int i = 1; i < n; i++) {
            cost=a[i]-mini;
            profit=max(profit,cost);
            mini=min(mini,a[i]);

        }
        return profit;
    }
};
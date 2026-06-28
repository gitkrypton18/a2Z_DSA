class Solution {
public:
    // Function to calculate total hours at given speed
    long long calculateTotalHours(vector<int>& piles, long long speed) {
        long long totalH = 0;
        for (long long bananas : piles) {
            totalH += ceil((double)bananas / speed);
        }
        return totalH;
    }

    // Function to find minimum eating speed
    long long minEatingSpeed(vector<int>& piles, long long h) {
        // Find maximum element
        long long maxPile = *max_element(piles.begin(), piles.end());

        // Initialize low and high polong longers
        long long low = 1, high = maxPile;
        long long ans = maxPile;

        // Binary search on answer space
        while (low <= high) {
            long long mid = low + (high-low) / 2;
            long long totalH = calculateTotalHours(piles, mid);

            // If possible, try smaller speed
            if (totalH <= h) {
                ans = mid;
                high = mid - 1;
            }
            // Otherwise, try larger speed
            else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
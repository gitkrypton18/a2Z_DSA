class Solution {
public:
    int fib(int n) {
        return solve(n);
    }

    int solve(int n) {
        static int dp[31];

        if(n <= 1)
            return n;

        if(dp[n])
            return dp[n];

        return dp[n] = solve(n-1) + solve(n-2);
    }
};
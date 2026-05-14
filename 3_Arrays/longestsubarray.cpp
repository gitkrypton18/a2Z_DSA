#include <bits/stdc++.h>
using namespace std;

int longestSubarray(vector<int> a, long long k)
{

    int left = 0, right = 0;
    long long sum = a[0];
    int maxLen = 0;
    int n = a.size();
    while (right < n)
    {
        while (left <= right && sum > k)
        {
            sum -= a[left];
            left++;
        } //
        if (sum == k)
        {
            maxLen = max(maxLen, right - left + 1);
        }
        right++;
        if (right < n)
            sum += a[right];
    }
    return maxLen;
}

int main()
{
    vector<int> vt = {1, 2, 3, 1, 1, 1, 1, 3, 3};
    cout << longestSubarray(vt, 6);
}
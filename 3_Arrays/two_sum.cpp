#include <bits/stdc++.h>
using namespace std;

// Approach 1: Using HashMap (Optimal for unsorted arrays)
class HashMapApproach
{
public:
    pair<bool, vector<int>> twoSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        map<int, int> mpp;
        for (int i = 0; i < n; i++)
        {
            int a = nums[i];
            int more = target - a;
            if (mpp.find(more) != mpp.end())
            {
                return {true, {mpp[more], i}};
            }
            mpp[a] = i;
        }
        return {false, {-1, -1}};
    }
};

// Approach 2: Using Two Pointers (Optimal for sorted arrays)
class TwoPointerApproach
{
public:
    pair<bool, vector<int>> twoSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        vector<pair<int, int>> numsWithIndex;
        for (int i = 0; i < n; i++)
        {
            numsWithIndex.push_back({nums[i], i});
        }
        sort(numsWithIndex.begin(), numsWithIndex.end());
        int left = 0, right = n - 1;
        while (left < right)
        {
            int sum = numsWithIndex[left].first + numsWithIndex[right].first;
            if (sum == target)
            {
                return {true, {numsWithIndex[left].second, numsWithIndex[right].second}};
            }
            else if (sum > target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        return {false, {-1, -1}};
    }
};

int main()
{
    vector<int> vc = {2, 6, 5, 8, 11};
    int target = 14;

    // Test Approach 1: HashMap
    HashMapApproach hashSolution;
    auto result1 = hashSolution.twoSum(vc, target);
    cout << "HashMap Approach:\n";
    cout << "Pair Found: " << (result1.first ? "YES" : "NO") << "\n";
    if (result1.first)
    {
        cout << "Indices: [" << result1.second[0] << ", " << result1.second[1] << "]\n\n";
    }

    // Test Approach 2: Two Pointers
    TwoPointerApproach twoPointerSolution;
    auto result2 = twoPointerSolution.twoSum(vc, target);
    cout << "Two Pointer Approach:\n";
    cout << "Pair Found: " << (result2.first ? "YES" : "NO") << "\n";
    if (result2.first)
    {
        cout << "Indices: [" << result2.second[0] << ", " << result2.second[1] << "]\n";
    }

    return 0;
}
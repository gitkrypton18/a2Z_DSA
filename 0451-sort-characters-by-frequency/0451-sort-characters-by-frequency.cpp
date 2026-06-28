class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> freq;

        // Count frequencies
        for (char ch : s) {
            freq[ch]++;
        }

        // Store {character, frequency}
        vector<pair<char, int>> arr(freq.begin(), freq.end());

        // Sort by frequency descending
        sort(arr.begin(), arr.end(),
             [](const pair<char, int>& a, const pair<char, int>& b) {
                 return a.second > b.second;
             });

        string ans = "";

        // Build answer
        for (auto &p : arr) {
            ans.append(p.second, p.first);
        }

        return ans;
    }
};
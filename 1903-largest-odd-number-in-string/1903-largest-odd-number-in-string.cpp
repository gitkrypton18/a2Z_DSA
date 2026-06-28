class Solution {
public:
    string largestOddNumber(string s) {
        string result = {};
        int idx = s.size() - 1;
        while (idx >= 0) {
            if ((s[idx] - '0') % 2 == 1)
                return s.substr(0, idx + 1);
            idx--;
        }
        return "";
    }
};
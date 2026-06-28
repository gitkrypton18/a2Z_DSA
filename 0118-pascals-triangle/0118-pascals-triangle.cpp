class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal;
        for (int i = 1; i <= numRows; i++) {
            long long ans=1;
            vector<int> temp;
            temp.push_back(1);
            for (int j = 1; j < i; j++) {
                ans = ans * (i - j);
                ans = ans / j;
                temp.push_back(ans);
            }
            pascal.push_back(temp);
        }

        return pascal;
    }
};
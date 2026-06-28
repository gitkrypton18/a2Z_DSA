class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = m * m;

        vector<int> hash(n + 1, 0);

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < m; j++) {
                hash[grid[i][j]]++;
            }
        }

        int repeat = -1, miss = -1;

        for(int i = 1; i <= n; i++) {
            if(hash[i] == 2)
                repeat = i;

            else if(hash[i] == 0)
                miss = i;

            if(repeat != -1 && miss != -1)
                break;
        }

        return {repeat, miss};
    }
};
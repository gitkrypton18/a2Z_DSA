class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;

        unordered_set<int> st;
        st.reserve(n * 2);
        st.max_load_factor(0.7);

        for(int x : nums)
            st.insert(x);

        int longest = 1;

        for(int x : st){

            // Start only from beginning of sequence
            if(!st.count(x - 1)){

                int curr = x;
                int len = 1;

                while(st.count(curr + 1)){
                    curr++;
                    len++;
                }

                longest = max(longest, len);
            }
        }

        return longest;
    }
};
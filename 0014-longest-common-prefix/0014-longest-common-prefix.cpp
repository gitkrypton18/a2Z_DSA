class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) { 
        string ans ={};
        if(strs.empty()) return " ";
        sort(strs.begin(),strs.end()); // lexicographically 
        string first= strs[0],last=strs[strs.size()-1];
        int minlength= min (first.size(),last.size());
        for(int i=0;i<minlength;i++){
            if(first[i]!=last[i]) break;
            ans+=first[i];
        }
        return ans;
        
        
        
    }
};
class Solution {
public:
    string removeOuterParentheses(string s) {
        int n=s.size();
        string result={};
        int cnt=0;
        for(int i=0;i<n;i++){
            if(s[i]=='('){
                cnt++;
                if(cnt>1) result+=s[i];

            } 
            else if(s[i]==')'){
                cnt--;
                if(cnt>0) result+=s[i];
            }

        }
        return result;
    }
};
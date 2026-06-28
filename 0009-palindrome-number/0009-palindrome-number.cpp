class Solution {
public:
    bool isPalindrome(int x) {
        long o = x;
        long rev = 0;
        if (x <= INT_MAX  && x > 0) {

            {
                while (x > 0) {
                    rev = rev * 10 + x % 10;
                    x = x / 10;
                }
            }
        }
        if (rev == o) {
            return true;
        } else
            return false;
    }
};
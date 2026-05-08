class Solution
{
public:
    bool isPalindrome(int x)
    {
        int o = x;
        if (x > INT_MAX / 10 || x < INT_MIN / 10)
        {
            return 0;
        }

        else
        {

            while (x >= 0)
            {
                int rev = 0;
                rev = rev * 10 + x % 10;
                x = x / 10;
            }
        }
        if (rev == o)
    };
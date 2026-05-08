#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Function to reverse digits of a number
    int reverseNumber(int n)
    {
        // Variable to store reversed number
        int revNum = 0;

        // Loop until all digits are processed
        while (n > 0)
        {
            // Get the last digit
            int lastDigit = n % 10;

            // Append it to the reversed number
            revNum = revNum * 10 + lastDigit;

            // Remove the last digit from n
            n = n / 10;
        }

        // Return the reversed number
        return revNum;
    }
};

// Driver code
int main()
{
    Solution obj;
    int num = 12345;
    cout << obj.reverseNumber(num) << endl; // Output: 54321
    return 0;
}

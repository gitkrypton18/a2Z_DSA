#include <iostream>
using namespace std;

// Function to check if a given integer is a palindrome
bool palindrome(int n)
{
    int revNum = 0; // Initialize a variable to store the reverse of the number
    int dup = n;    // Create a duplicate variable to store the original number

    // Iterate through each digit of the number until it becomes 0
    while (n > 0)
    {
        int ld = n % 10;             // Extract the last digit of the number
        revNum = (revNum * 10) + ld; // Build the reverse number by appending the last digit
        n = n / 10;                  // Remove the last digit from the original number
    }

    // Check if the original number is equal to its reverse
    if (dup == revNum)
    {
        return true; // If equal, return true indicating it's a palindrome
    }
    else
    {
        return false; // If not equal, return false indicating it's not a palindrome
    }
}

int main()
{
    int number = 4554; // Example number

    if (palindrome(number))
    { // Check if the number is a palindrome
        cout << number << " is a palindrome." << endl;
    }
    else
    {
        cout << number << " is not a palindrome." << endl;
    }

    return 0;
}

#include <iostream>
#include <math.h>
using namespace std;

// BRUTE FORCE APPROACH: Count digits using modulo division
// Time: O(log n), Space: O(1)
int main()
{
    int a;
    cin >> a;

    // Alternative: Using logarithm to calculate digit count
    int k = int(log10(a) + 1); // O(1) approach using math formula

    // Brute force: Divide by 10 repeatedly until number becomes 0
    int cn = 0;
    while (a > 0)
    {
        a % 10;  // Extract last digit (not used here, just for iteration)
        cn++;    // Increment digit count
        a /= 10; // Remove last digit
    }
    cout << cn << endl; // Output brute force result
    cout << k;          // Output logarithm approach result
}

// OPTIMAL APPROACH: TODO - Implement using logarithm directly
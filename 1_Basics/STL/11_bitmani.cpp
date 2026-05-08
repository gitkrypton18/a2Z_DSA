
// STL + Bit Manipulation quick notes (learning purpose)
#include <algorithm> // next_permutation, max_element, min_element
#include <iostream>  // cout
#include <string>    // string
#include <vector>    // vector

using namespace std;

int main() {
    // 1) Count Set Bits (number of 1s in binary form)
    int num = 7; // Binary: 111
    cout << "Set bits in " << num << " = " << __builtin_popcount(num) << '\n'; // 3

    long long num2 = 165786578687LL;
    cout << "Set bits in " << num2 << " = " << __builtin_popcountll(num2) << '\n';

    // 2) Next Dictionary Permutation
    // Always keep string sorted initially if you want all permutations in order.
    string s = "123";
    cout << "Permutations: ";
    do {
        cout << s << ' '; // 123 132 213 231 312 321
    } while (next_permutation(s.begin(), s.end()));
    cout << '\n';

    // 3) Max/Min element from a container
    vector<int> v = {4, 9, 1, 7, 3};
    int max_val = *max_element(v.begin(), v.end());
    int min_val = *min_element(v.begin(), v.end());
    cout << "Max = " << max_val << ", Min = " << min_val << '\n';

    return 0;
}
#include <algorithm> // for std::sort
#include <iostream>  // for std::cout, std::endl
#include <utility>   // for std::pair

using namespace std;

// Custom comparator function used by std::sort.
// Parameters:
//   p1, p2 - pairs to compare. Each pair contains two integers.
// Ordering rules implemented below:
// 1) Primarily sort by the second element in ascending order.
// 2) If the second elements are equal, sort by the first element
//    in descending order (so larger first-values come earlier).
// The comparator returns true when p1 should go before p2.
bool comp(pair<int, int> p1, pair<int, int> p2) {
    // Compare second elements first (ascending)
    if (p1.second < p2.second) return true;
    if (p1.second > p2.second) return false;

    // If second elements are equal, compare first elements (descending)
    return p1.first > p2.first;
}

int main() {
    // Example array of pairs to demonstrate custom sorting
    pair<int, int> a[] = {{1, 2}, {2, 1}, {4, 1}, {3, 2}, {5, 1}};
    int n = sizeof(a) / sizeof(a[0]); // number of elements in the array

    // Sort the array using the custom comparator 'comp'
    sort(a, a + n, comp);

    // Output the sorted pairs to the console
    cout << "Sorted pairs: ";
    for (int i = 0; i < n; i++) {
        // Print each pair in the format {first, second}
        cout << "{" << a[i].first << ", " << a[i].second << "} ";
    }
    cout << '\n';

    return 0;
}
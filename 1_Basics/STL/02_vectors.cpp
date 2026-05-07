#include <iostream>
#include <vector>
#include <algorithm> // For sort, reverse

using namespace std;

int main() {
    // 1. CONSTRUCTORS & INITIALIZATION
    vector<int> v1;                     // Empty vector
    vector<int> v2(5, 100);             // {100, 100, 100, 100, 100}
    vector<int> v3 = {1, 2, 3};         // Initializer list
    vector<int> v4(v3.begin(), v3.end()); // Copy range

    // 2. MODIFIERS (Insert/Delete)
    v1.push_back(10);                   // Add to end: {10}
    v1.emplace_back(20);                // Faster, constructs in-place: {10, 20}
    v1.insert(v1.begin(), 5);           // Insert at start: {5, 10, 20}
    v1.insert(v1.begin() + 1, 2, 7);    // Insert two 7s at pos 1: {5, 7, 7, 10, 20}
    
    v1.pop_back();                      // Remove end: {5, 7, 7, 10}
    v1.erase(v1.begin() + 1);           // Remove pos 1: {5, 7, 10}
    v1.erase(v1.begin(), v1.begin() + 2); // Remove range [0, 2): {10}

    // 3. CAPACITY CONTROL
    v1.reserve(100);                    // Reserve memory (prevents reallocations)
    v1.resize(5, 1);                    // Resize to 5, fill with 1: {10, 1, 1, 1, 1}
    v1.shrink_to_fit();                 // Reduce capacity to fit actual size
    
    // 4. ACCESSORS
    cout << v1[0] << endl;              // Direct access
    cout << v1.at(0) << endl;           // Bounds-checked access
    cout << v1.front() << endl;         // First element
    cout << v1.back() << endl;          // Last element
    int* dataPtr = v1.data();           // Get raw pointer to array

    // 5. ASSIGNMENT & SWAP
    vector<int> v5;
    v5.assign(3, 50);                   // Fill with {50, 50, 50}
    v1.swap(v5);                        // Fast swap content of two vectors

    // 6. ITERATORS
    // Forward: begin(), end()
    // Reverse: rbegin(), rend()
    for(auto it = v1.rbegin(); it != v1.rend(); ++it) {
        cout << *it << " ";             // Prints vector in reverse
    }

    // 7. CLEAR
    v1.clear();                         // Size becomes 0
    return 0;
}
#include <iostream>
#include <map>
using namespace std;

int main() {
    // MAP BASICS
    map<int, int> mpp;           // map<key_type, value_type>
    map<pair<int, int>, int> mpp2;

    mpp[1] = 2;                  // Key 1 -> Value 2
    mpp.emplace(3, 1);           // Key 3 -> Value 1
    mpp.insert({2, 4});          // Stored as: {1:2, 2:4, 3:1} (Sorted by key)

    // Iteration
    cout << "Map contents (sorted by key):" << endl;
    for(auto it : mpp) {
        cout << it.first << " -> " << it.second << endl; 
    }

    cout << "\nAccess elements:" << endl;
    cout << "mpp[1] = " << mpp[1] << endl; // Prints 2
    cout << "mpp[5] = " << mpp[5] << endl; // If key doesn't exist, prints 0 (default value)

    cout << "\nFind element:" << endl;
    auto it = mpp.find(3); // Returns iterator. Access value via it->second
    if(it != mpp.end()) {
        cout << "Key 3 found with value: " << it->second << endl;
    }

    // MULTIMAP BASICS
    cout << "\n--- MULTIMAP ---" << endl;
    multimap<int, string> students;
    students.insert({1, "Alice"});
    students.insert({2, "Bob"});
    students.insert({1, "Charlie"});  // Duplicate key allowed
    students.insert({2, "David"});

    cout << "Multimap contents:" << endl;
    for(auto& p : students) {
        cout << p.first << " -> " << p.second << endl;
    }

    cout << "\nFind all values for key 1:" << endl;
    auto range = students.equal_range(1);
    for(auto it = range.first; it != range.second; ++it) {
        cout << it->first << " -> " << it->second << endl;
    }

    return 0;
}
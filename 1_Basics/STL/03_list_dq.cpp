#include <iostream>
#include <list>
#include <deque>

using namespace std;

int main() {
    cout << "--- LIST (Doubly Linked List) ---\n";
    list<int> ls;
    
    ls.push_back(20);       // {20}
    ls.emplace_back(30);    // {20, 30}
    ls.push_front(10);      // {10, 20, 30} -> O(1) time!
    ls.emplace_front(5);    // {5, 10, 20, 30}
    
    ls.pop_back();          // {5, 10, 20}
    ls.pop_front();         // {10, 20}

    cout << "List elements: ";
    for(auto it : ls) cout << it << " "; 
    cout << "\n\n";

    // Note: ls[0] will cause an ERROR. No random access in list.


    cout << "--- DEQUE (Double-Ended Queue) ---\n";
    deque<int> dq;
    
    dq.push_back(20);       // {20}
    dq.push_front(10);      // {10, 20}
    dq.push_back(30);       // {10, 20, 30}
    
    dq.pop_back();          // {10, 20}
    dq.pop_front();         // {20}
    
    dq.push_front(10);      // {10, 20}
    dq.push_back(30);       // {10, 20, 30}

    // Deque ALLOWS random access (unlike list)
    cout << "Deque element at index 1: " << dq[1] << "\n"; // Output: 20

    cout << "Deque elements: ";
    for(auto it : dq) cout << it << " "; 
    cout << "\n";

    return 0;
}
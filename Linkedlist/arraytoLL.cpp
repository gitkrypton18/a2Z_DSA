#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;   // Data value
    Node *next; // Pointer to next node

    // Constructor with data and next
    Node(int data1, Node *next1)
    {
        data = data1;
        next = next1;
    }
};

Node *arraytoLL(vector<int> &arr)
{
    Node *head = new Node(arr[0]);
    Node *temp = head;
    for (int i = 1; i < arr.size(); i++)
    {
    }
}

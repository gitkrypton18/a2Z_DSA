#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list
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

    // Constructor with only data
    Node(int data1)
    {
        data = data1;
        next = nullptr;
    }
};

Node *arraytoLL(vector<int> &arr)
{
    if (arr.size() == 0)
        return nullptr;

    Node *head = new Node(arr[0]);
    Node *temp = head;

    for (int i = 1; i < arr.size(); i++)
    {
        Node *newNode = new Node(arr[i]);
        temp->next = newNode;
        temp = newNode;
    }

    return head;
}
void printLL(Node *head)
{
    Node *temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    vector<int> arr = {10, 20, 30, 40, 50};

    Node *head = arraytoLL(arr);

    printLL(head);

    return 0;
}

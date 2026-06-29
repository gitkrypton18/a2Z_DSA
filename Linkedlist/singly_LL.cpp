/*
=========================================================
            SINGLY LINKED LIST MASTER NOTEBOOK
=========================================================

Contents
--------
1. Node Class
2. Array -> Linked List
3. Traversal
4. Print Linked List
5. Length of LL
6. Search in LL

Deletion
--------
7. Delete Head
8. Delete Tail
9. Delete Kth Node (Position)
10. Delete Given Value

Insertion
---------
11. Insert Head
12. Insert Tail
13. Insert at Kth Position
14. Insert Before Given Value

---------------------------------------------------------
Core Idea

head    -> Always points to the first node.
temp    -> Used for traversal.
prev    -> Used during deletion.
newNode -> Newly created node.

Never move 'head' while traversing.
Always use 'temp'.

Time Complexities
-----------------
Traversal      O(n)
Length         O(n)
Search         O(n)

Insert Head    O(1)
Delete Head    O(1)

Insert Tail    O(n)
Delete Tail    O(n)

=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

//=====================================================
//                  NODE CLASS
//=====================================================

class Node
{
public:
    int data;
    Node *next;

    // Constructor with data and next pointer
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

//=====================================================
//              ARRAY -> LINKED LIST
//=====================================================

// Converts an array into a linked list.
// Returns the head of the linked list.

Node *arrayToLL(vector<int> &arr)
{
    if (arr.empty())
        return nullptr;

    // First element becomes head.
    Node *head = new Node(arr[0]);

    // temp always points to the last node.
    Node *temp = head;

    for (int i = 1; i < arr.size(); i++)
    {
        Node *newNode = new Node(arr[i]);

        // Link previous node to new node.
        temp->next = newNode;

        // Move temp forward.
        temp = newNode;
    }

    return head;
}

//=====================================================
//                  TRAVERSAL
//=====================================================

// Visits every node exactly once.

void traverse(Node *head)
{
    Node *temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}

//=====================================================
//              PRINT LINKED LIST
//=====================================================

// Printing is simply traversal.

void printLL(Node *head)
{
    traverse(head);
}

//=====================================================
//              LENGTH OF LL
//=====================================================

int lengthLL(Node *head)
{
    int cnt = 0;

    Node *temp = head;

    while (temp != nullptr)
    {
        cnt++;
        temp = temp->next;
    }

    return cnt;
}

//=====================================================
//              SEARCH IN LL
//=====================================================

bool searchLL(Node *head, int key)
{
    Node *temp = head;

    while (temp != nullptr)
    {
        if (temp->data == key)
            return true;

        temp = temp->next;
    }

    return false;
}

//=====================================================
//              DELETE HEAD
//=====================================================

Node *deleteHead(Node *head)
{
    if (head == nullptr)
        return head;

    Node *temp = head;

    head = head->next;

    delete temp;

    return head;
}

//=====================================================
//              DELETE TAIL
//=====================================================

Node *deleteTail(Node *head)
{
    if (head == nullptr)
        return nullptr;

    if (head->next == nullptr)
    {
        delete head;
        return nullptr;
    }

    Node *temp = head;

    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    delete temp->next;

    temp->next = nullptr;

    return head;
}

//=====================================================
//          DELETE Kth NODE
//=====================================================

Node *deleteKth(Node *head, int k)
{
    if (head == nullptr)
        return head;

    if (k == 1)
        return deleteHead(head);

    Node *temp = head;
    Node *prev = nullptr;

    int cnt = 1;

    while (temp != nullptr)
    {
        if (cnt == k)
        {
            prev->next = temp->next;
            delete temp;
            break;
        }

        prev = temp;
        temp = temp->next;
        cnt++;
    }

    return head;
}

//=====================================================
//          DELETE GIVEN VALUE
//=====================================================

Node *deleteValue(Node *head, int value)
{
    if (head == nullptr)
        return head;

    if (head->data == value)
        return deleteHead(head);

    Node *temp = head;

    while (temp->next != nullptr)
    {
        if (temp->next->data == value)
        {
            Node *delNode = temp->next;

            temp->next = temp->next->next;

            delete delNode;

            break;
        }

        temp = temp->next;
    }

    return head;
}

//=====================================================
//              INSERT AT HEAD
//=====================================================

Node *insertHead(Node *head, int value)
{
    Node *newNode = new Node(value);

    newNode->next = head;

    return newNode;
}

//=====================================================
//              INSERT AT TAIL
//=====================================================

Node *insertTail(Node *head, int value)
{
    Node *newNode = new Node(value);

    if (head == nullptr)
        return newNode;

    Node *temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;

    return head;
}

//=====================================================
//          INSERT AT Kth POSITION
//=====================================================

Node *insertKth(Node *head, int value, int k)
{
    if (k == 1)
        return insertHead(head, value);

    Node *temp = head;

    int cnt = 1;

    while (temp != nullptr)
    {
        if (cnt == k - 1)
        {
            Node *newNode = new Node(value);

            newNode->next = temp->next;

            temp->next = newNode;

            break;
        }

        cnt++;
        temp = temp->next;
    }

    return head;
}

//=====================================================
//      INSERT BEFORE GIVEN VALUE
//=====================================================

Node *insertBeforeValue(Node *head, int value, int before)
{
    if (head == nullptr)
        return nullptr;

    if (head->data == before)
        return insertHead(head, value);

    Node *temp = head;

    while (temp->next != nullptr)
    {
        if (temp->next->data == before)
        {
            Node *newNode = new Node(value);

            newNode->next = temp->next;

            temp->next = newNode;

            break;
        }

        temp = temp->next;
    }

    return head;
}

//=====================================================
//                      MAIN
//=====================================================

int main()
{
    vector<int> arr = {2, 5, 8, 7};

    // Create Linked List
    Node *head = arrayToLL(arr);

    cout << "Initial Linked List : ";
    printLL(head);

    cout << "\nTraversal : ";
    traverse(head);

    cout << "\nLength : " << lengthLL(head) << endl;

    cout << "Search 8 : ";
    cout << (searchLL(head, 8) ? "Found" : "Not Found") << endl;

    cout << "\nDelete Head\n";
    head = deleteHead(head);
    printLL(head);

    cout << "\nDelete Tail\n";
    head = deleteTail(head);
    printLL(head);

    cout << "\nInsert Head (100)\n";
    head = insertHead(head, 100);
    printLL(head);

    cout << "\nInsert Tail (500)\n";
    head = insertTail(head, 500);
    printLL(head);

    cout << "\nInsert 300 at Position 3\n";
    head = insertKth(head, 300, 3);
    printLL(head);

    cout << "\nInsert 50 Before Value 500\n";
    head = insertBeforeValue(head, 50, 500);
    printLL(head);

    cout << "\nDelete 3rd Node\n";
    head = deleteKth(head, 3);
    printLL(head);

    cout << "\nDelete Value 500\n";
    head = deleteValue(head, 500);
    printLL(head);

    return 0;
}

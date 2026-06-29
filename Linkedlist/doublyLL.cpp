// Doubly Linked List Master Notebook (starter)
// Based on the user's preferred coding style.

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
    Node *back;

    Node(int data1, Node *next1, Node *back1)
    {
        data = data1;
        next = next1;
        back = back1;
    }

    Node(int data1)
    {
        data = data1;
        next = nullptr;
        back = nullptr;
    }
};

//=====================================================
//              ARRAY -> DOUBLY LL
//=====================================================

Node *arrayToDLL(vector<int> &arr)
{
    if (arr.empty())
        return nullptr;

    Node *head = new Node(arr[0]);
    Node *prev = head;

    for (int i = 1; i < arr.size(); i++)
    {
        Node *temp = new Node(arr[i], nullptr, prev);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

//=====================================================
//                  TRAVERSAL
//=====================================================

void traverseDLL(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void printDLL(Node *head)
{
    traverseDLL(head);
}

//=====================================================
//                  LENGTH
//=====================================================

int lengthDLL(Node *head)
{
    int cnt = 0;
    while (head)
    {
        cnt++;
        head = head->next;
    }
    return cnt;
}

//=====================================================
//                  SEARCH
//=====================================================

bool searchDLL(Node *head, int key)
{
    while (head)
    {
        if (head->data == key)
            return true;
        head = head->next;
    }
    return false;
}

//=====================================================
//              DELETE HEAD
//=====================================================

Node *deleteHead(Node *head)
{
    if (head == nullptr)
        return nullptr;

    if (head->next == nullptr)
    {
        delete head;
        return nullptr;
    }

    Node *temp = head;
    head = head->next;
    head->back = nullptr;
    temp->next = nullptr;
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

    Node *tail = head;
    while (tail->next)
        tail = tail->next;

    Node *newTail = tail->back;
    newTail->next = nullptr;
    tail->back = nullptr;
    delete tail;
    return head;
}

//=====================================================
//          DELETE KTH NODE
//=====================================================

Node *deleteKth(Node *head, int k)
{
    if (head == nullptr)
        return nullptr;

    Node *kNode = head;
    int cnt = 1;

    while (kNode && cnt < k)
    {
        kNode = kNode->next;
        cnt++;
    }

    if (kNode == nullptr)
        return head;

    Node *prev = kNode->back;
    Node *front = kNode->next;

    if (prev == nullptr && front == nullptr)
    {
        delete kNode;
        return nullptr;
    }

    if (prev == nullptr)
        return deleteHead(head);

    if (front == nullptr)
        return deleteTail(head);

    prev->next = front;
    front->back = prev;

    kNode->next = nullptr;
    kNode->back = nullptr;
    delete kNode;

    return head;
}

//=====================================================
//          DELETE GIVEN VALUE
//=====================================================

Node *deleteValue(Node *head, int value)
{
    Node *temp = head;

    while (temp)
    {
        if (temp->data == value)
            break;
        temp = temp->next;
    }

    if (temp == nullptr)
        return head;

    if (temp->back == nullptr)
        return deleteHead(head);

    if (temp->next == nullptr)
        return deleteTail(head);

    temp->back->next = temp->next;
    temp->next->back = temp->back;

    delete temp;
    return head;
}

//=====================================================
//          DELETE GIVEN NODE
//=====================================================

void deleteNode(Node *temp)
{
    if (temp == nullptr)
        return;

    Node *prev = temp->back;
    Node *front = temp->next;

    if (prev)
        prev->next = front;
    if (front)
        front->back = prev;

    delete temp;
}

//=====================================================
//              INSERT HEAD
//=====================================================

Node *insertHead(Node *head, int value)
{
    Node *newNode = new Node(value, head, nullptr);

    if (head)
        head->back = newNode;

    return newNode;
}

//=====================================================
//              INSERT TAIL
//=====================================================

Node *insertTail(Node *head, int value)
{
    Node *newNode = new Node(value);

    if (head == nullptr)
        return newNode;

    Node *temp = head;

    while (temp->next)
        temp = temp->next;

    temp->next = newNode;
    newNode->back = temp;

    return head;
}

//=====================================================
//                      MAIN
//=====================================================

int main()
{
    vector<int> arr = {2, 5, 20, 44, 65, 88, 7, 8, 7};

    Node *head = arrayToDLL(arr);

    cout << "Initial DLL : ";
    printDLL(head);

    cout << "Length : " << lengthDLL(head) << endl;

    cout << "Search 44 : " << (searchDLL(head, 44) ? "Found" : "Not Found") << endl;

    head = deleteHead(head);
    printDLL(head);

    head = deleteTail(head);
    printDLL(head);

    head = deleteKth(head, 3);
    printDLL(head);

    head = deleteValue(head, 65);
    printDLL(head);

    head = insertHead(head, 100);
    printDLL(head);

    head = insertTail(head, 500);
    printDLL(head);

    return 0;
}

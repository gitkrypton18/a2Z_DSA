#include <bits/stdc++.h>
using namespace std;

//=====================================================
//                  NODE CLASS
//=====================================================

class Node
{
public:
    int data;
    Node *next, *back;

    Node(int val)
    {
        data = val;
        next = nullptr;
        back = nullptr;
    }

    Node(int val, Node *next1, Node *back1)
    {
        data = val;
        next = next1;
        back = back1;
    }
};

//=====================================================
//              ARRAY -> DLL
//=====================================================

Node *arrayToDLL(vector<int> &arr)
{
    if (arr.empty())
        return nullptr;

    Node *head = new Node(arr[0]);
    Node *prev = head;

    for (int i = 1; i < (int)arr.size(); i++)
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

void printDLL(Node *head)
{
    while (head)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
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

    Node *prev = tail->back;
    prev->next = nullptr;
    delete tail;

    return head;
}

//=====================================================
//              DELETE KTH
//=====================================================

Node *deleteKth(Node *head, int k)
{
    if (head == nullptr)
        return nullptr;

    Node *temp = head;
    int cnt = 1;

    while (temp && cnt < k)
    {
        temp = temp->next;
        cnt++;
    }

    if (temp == nullptr)
        return head;

    Node *prev = temp->back;
    Node *front = temp->next;

    if (prev == nullptr && front == nullptr)
    {
        delete temp;
        return nullptr;
    }

    if (prev == nullptr)
        return deleteHead(head);
    if (front == nullptr)
        return deleteTail(head);

    prev->next = front;
    front->back = prev;

    delete temp;
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

    Node *prev = temp->back;
    Node *front = temp->next;

    if (prev == nullptr)
        return deleteHead(head);
    if (front == nullptr)
        return deleteTail(head);

    prev->next = front;
    front->back = prev;

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
//              INSERT KTH
//=====================================================

Node *insertKth(Node *head, int value, int k)
{
    if (k == 1)
        return insertHead(head, value);

    Node *temp = head;
    int cnt = 1;

    while (temp && cnt < k)
    {
        temp = temp->next;
        cnt++;
    }

    if (temp == nullptr)
    {
        if (cnt == k)
            return insertTail(head, value);
        return head;
    }

    Node *prev = temp->back;
    Node *newNode = new Node(value, temp, prev);

    prev->next = newNode;
    temp->back = newNode;

    return head;
}

//=====================================================
//          INSERT BEFORE GIVEN NODE
//=====================================================

void insertBeforeNode(Node *node, int value)
{
    if (node == nullptr)
        return;

    Node *prev = node->back;
    Node *newNode = new Node(value, node, prev);

    node->back = newNode;
    if (prev)
        prev->next = newNode;
}

//=====================================================
//              REVERSE DLL
//=====================================================

Node *reverseDLL(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    Node *current = head;
    Node *last = nullptr;

    while (current)
    {
        last = current;
        swap(current->next, current->back);
        current = current->back;
    }

    return last;
}

//=====================================================
//                  MAIN
//=====================================================

int main()
{

    vector<int> arr = {2, 5, 20, 44, 65, 88, 7, 8};

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

    head = insertKth(head, 300, 3);
    printDLL(head);

    if (head && head->next)
        insertBeforeNode(head->next, 50);

    printDLL(head);

    head = reverseDLL(head);

    cout << "Reversed DLL : ";
    printDLL(head);

    return 0;
}

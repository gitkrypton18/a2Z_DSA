#include <bits/stdc++.h>
using namespace std;

int leftRotate(int arr[], int n, int d)
{
    reverse(arr, arr + d);
    reverse(arr + d, arr + n);
    reverse(arr, arr + n);
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    cout << "Enter the array" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << endl
         << "enter the no of rotations";
    int k;
    cin >> k;
    leftRotate(arr, n, k);
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
    }
}
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Bubble Sort: repeatedly step through the list,
    // compare adjacent elements and swap them if they are in the wrong order.
    // After each outer pass the largest unsorted element is bubbled to its final position.
    int n;
    cin >> n;
    int arr[n];
    cout << "Enter the array" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int didSwap = 0;
    // Outer loop: reduce the range of unsorted elements each pass
    for (int i = n - 1; i >= 1; i--)
    {

        // Inner loop: bubble the largest element of [0..i] to index i
        for (int j = 0; j <= i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                didSwap += 1;
            }
        }
        if (didSwap == 0)
            break;
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl
         << didSwap;

    return 0;
}
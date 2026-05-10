#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Insertion Sort: build the sorted portion one element at a time.
    // Insert each element into its correct position among the already sorted elements.
    int n;
    cin >> n;
    int arr[n];
    cout << "Enter the array" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i <= n - 1; i++)
    {
        // Move the current element left until it reaches the correct position.
        int j = i;
        {
            while (j > 0 && arr[j - 1] > arr[j])
            {
                swap(arr[j - 1], arr[j]);
                j--;
            }
        }
    }
    // Print the sorted array.
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "\t";
    }

    return 0;
}
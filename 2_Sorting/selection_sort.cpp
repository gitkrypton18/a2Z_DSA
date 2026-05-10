#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Read input size
    int n;
    cin >> n;
    int arr[n];
    cout << "Enter the array" << endl;

    // Read array elements from user
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Selection Sort Algorithm
    // Time Complexity: O(n²), Space Complexity: O(1)
    // Find minimum element in unsorted portion and place it at correct position
    for (int i = 0; i <= n - 2; i++) // Iterate till n-2 (last element is automatically sorted)
    {
        int min = i; // Initialize min index as current position

        // Find minimum element in remaining unsorted array
        for (int j = i; j <= n - 1; j++)
        {
            if (arr[j] < arr[min])
                min = j; // Update min index if smaller element found
        }

        // Swap minimum element with current position
        swap(arr[i], arr[min]);
    }

    // Print sorted array
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "\t";
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// Partitions the array around a pivot and returns the pivot's final index.
// Elements smaller than or equal to the pivot are moved to the left side,
// and elements greater than the pivot are moved to the right side.
int f(int arr[], int low, int high)
{
    // Use the first element as the pivot value.
    int pivot = arr[low];

    // 'i' moves from left to right, 'j' moves from right to left.
    int i = low, j = high;

    // Keep scanning until both pointers cross each other.
    while (i < j)
    {
        // Move 'i' forward while values are already on the correct side.
        while (arr[i] <= pivot && i <= high)

        {
            i++;
        }

        // Move 'j' backward while values are greater than the pivot.
        while (arr[j] > pivot && j >= low)

        {
            j--;
        }

        // Swap the two misplaced elements if the pointers have not crossed.
        if (i < j)
            swap(arr[i], arr[j]);
    }

    // Place the pivot in its correct sorted position.
    swap(arr[low], arr[j]);
    return j;
}

// Recursively sorts the array using the Quick Sort algorithm.
void QS(int arr[], int low, int high)
{
    // A subarray with 0 or 1 element is already sorted.
    if (low < high)
    {
        // Partition the current subarray and get the pivot index.
        int pIndex = f(arr, low, high);

        // Sort the left half.
        QS(arr, low, pIndex - 1);

        // Sort the right half.
        QS(arr, pIndex + 1, high);
    }
}

int main(int argc, char const *argv[])
{
    int n;
    // Read the number of elements.
    cout << "Enter the length of array" << endl;
    cin >> n;

    // Create the array to store user input.
    int arr[n];

    // Read array elements from the user.
    cout << "Enter the contents" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Sort the full array.
    QS(arr, 0, n - 1);

    // Display the sorted array.
    cout << endl
         << "The new array is" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "\t";
    }

    return 0;
}

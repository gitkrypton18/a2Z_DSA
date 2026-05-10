#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Function to merge two halves of the array
    void merge(int arr[], int low, int mid, int high)
    {
        // Create temp array
        int temp[high - low + 1];
        int left = low, right = mid + 1, k = 0;

        // Merge two sorted halves
        while (left <= mid && right <= high)
        {
            if (arr[left] <= arr[right])
                temp[k++] = arr[left++];
            else
                temp[k++] = arr[right++];
        }

        // Copy remaining elements from left half
        while (left <= mid)
            temp[k++] = arr[left++];

        // Copy remaining elements from right half
        while (right <= high)
            temp[k++] = arr[right++];

        // Copy sorted elements back to original array
        for (int i = low; i <= high; i++)
            arr[i] = temp[i - low];
    }

    // Recursive merge sort function
    void mergeSort(int arr[], int low, int high)
    {
        if (low >= high)
            return;

        // Find the middle index
        int mid = (low + high) / 2;

        // Recursively sort left half
        mergeSort(arr, low, mid);

        // Recursively sort right half
        mergeSort(arr, mid + 1, high);

        // Merge the two sorted halves
        merge(arr, low, mid, high);
    }
};

int main()
{
    int arr[] = {5, 2, 8, 4, 1};
    int n = 5;
    Solution sol;
    sol.mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}

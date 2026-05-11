#include <bits/stdc++.h>
using namespace std;

void BS(int n, int arr[])
{

    if (n == 1)
    {
        return;
    }
    int didSwap = 0; // Flag to check if any swap occurred in this pass
    // perform one pass of bubble sort up to index n-1
    for (int j = 0; j < n - 1; ++j)
    {
        if (arr[j] > arr[j + 1])
            swap(arr[j], arr[j + 1]);
        didSwap = 1;
    }
    // If no swap happened, array is already sorted
    if (didSwap == 0)
        return;
    BS(n - 1, arr);
}

int main(int argc, char const *argv[])
{
    int arr[5] = {2, 6, 1, 3, 4};
    BS(5, arr);
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << "\t";
    }

    return 0;
}

// Optimised :

#include <bits/stdc++.h>
using namespace std;

void IS(int arr[], int n, int i)
{
    if (i == n)
    {
        return;
    }
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j])
    {
        swap(arr[j - 1], arr[j]);
        j--;
    }
    IS(arr, n, i + 1);
}

int main(int argc, char const *argv[])
{
    int arr[7] = {14, 9, 15, 12, 6, 8, 13};
    IS(arr, 7, 0);
    for (int i = 0; i < 7; i++)
    {
        cout << arr[i] << "\t";
    }

    return 0;
}

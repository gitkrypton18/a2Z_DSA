
#include <bits/stdc++.h>
using namespace std;

int Big(int arr[], int n)
{
    int largest = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > largest)
            largest = arr[i];
    }
    return largest;
}
int main()
{

    int arr[5] = {1, 4, 3, 6, 5};
    cout << Big(arr, 5);
}
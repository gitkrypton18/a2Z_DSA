
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int largest = arr[0], slargest = INT_MIN;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > largest)
            slargest = largest, largest = arr[i];
        else
            slargest = arr[i];
    }

    cout << "Largest " << largest << "  Second Largest " << slargest << endl;
}
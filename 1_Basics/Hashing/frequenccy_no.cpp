#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter tbhe length of array :" << endl;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << "The arrray is :" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
    }
    // precompute
    int hash[100] = {0};
    for (int i = 0; i < n; i++)
    {
        hash[arr[i]] += 1;
    }

    int q;
    cout << endl
         << "Enter how many no whose freq required" << endl;

    cin >> q;
    cout << "start entering the numbers";
    while (q--)
    {
        int number;
        cin >> number;
        // fetch
        cout << "Freq of " << number << " is : " << hash[number] << endl;
    }

    return 0;
}

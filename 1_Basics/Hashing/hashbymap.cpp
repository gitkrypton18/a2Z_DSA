#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter the length of array :" << endl;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << "The arrray is :" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
    }
    // precompute using map
    map<int, int> mpp;
    for (int i = 0; i < n; i++)
    {
        mpp[arr[i]]++;
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
        cout << "Freq of " << number << " is : " << mpp[number] << endl;
    }

    // Display all map contents in sorted order
    cout << "\nMap contents (key -> value) in sorted key order:" << endl;
    for (auto it : mpp)
    {
        cout << it.first << " -> " << it.second << endl;
    }

    // Find and display the number with maximum frequency
    int maxFreq = 0;
    int mostOccurring = -1;

    // Iterate through map to find the element with highest frequency
    for (auto it : mpp)
    {
        if (it.second > maxFreq)
        {
            maxFreq = it.second;
            mostOccurring = it.first;
        }
    }

    cout << "\nMost occurring number is: " << mostOccurring << " with frequency: " << maxFreq << endl;

    return 0;
}

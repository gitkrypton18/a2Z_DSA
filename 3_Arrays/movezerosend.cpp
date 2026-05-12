#include <bits/stdc++.h>
using namespace std;
void moveZeroes(vector<int> &nums)
{
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 0)
        {
            count++;
        }
    }
    if (count == 0)
    {
        return;
    }
    int n = nums.size();
    int j = -1;

    for (int i = 0; i < n; i++)
    {
        if (nums[i] == 0)
        {
            j = i;
            break;
        }
    }

    for (int i = j + 1; i < n; i++)
    {
        if (nums[i] != 0)
        {
            swap(nums[i], nums[j]);
            j++;
        }
    }
}

void moveZeroesTwoPointer(vector<int> &nums)
{
    int i = 0, j = 0;
    int n = nums.size();

    while (j < n)
    {
        if (nums[j] != 0)
        {
            swap(nums[i], nums[j]);
            i++;
        }
        j++;
    }
}

int main()
{

    vector<int> arr = {5, 0, 3, 0, 7, 0, 2};
    moveZeroesTwoPointer(arr);

    cout << "Array after moving zeroes: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
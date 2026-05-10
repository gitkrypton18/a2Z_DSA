// Sum of n numbers using parameterised way

#include <bits/stdc++.h>
using namespace std;

void f(int i, int sum)
{
    if (i < 1)
    {
        cout << (sum);
        return;
    }

    return f(i - 1, sum + i);
}

// Sum of n numbers by function way

int f1(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return n + f1(n - 1);
}
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    cout << f1(n);
    // f(n,0);

    return 0;
}

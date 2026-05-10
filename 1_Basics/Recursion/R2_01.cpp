#include <bits/stdc++.h>
using namespace std;
// Print name n times using recursion

// void f(int i, int n)
// {
//     if (i > n)
//         return;

//     cout << "Kalpit" << endl;
//     f(i + 1, n);
// }

// print 1 to n using recursion
void f1ton(int i, int n)
{
    if (i > n)
        return;

    cout << i << endl;
    f1ton(i + 1, n);
}

int main()
{
    int n;
    cin >> n;
    cout << "Output" << endl;

    // f(1, n);
    f1ton(1, n);
}

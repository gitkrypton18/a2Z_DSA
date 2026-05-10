#include <bits/stdc++.h>
using namespace std;

// void f1n(int i, int n)
// {
//     if (i < 1)
//         return;

//     f1n(i - 1, n);
//     cout << i;
// }

// print n to 1 backtracking
void fn1(int i, int n)
{
    if (i > n)
        return;

    fn1(i + 1, n);
    cout << i;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    cout << "Output" << endl;

    fn1(1, n);
    // f1n(n,n);

    return 0;
}

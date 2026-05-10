// to checck a given string is palindrome or not

#include <bits/stdc++.h>
using namespace std;

bool f(int i, string &s)
{
    if (i >= s.size() / 2)
        return true;

    if (s[i] != s[s.size() - i - 1])
        return false;

    f(i + 1, s);
}
int main(int argc, char const *argv[])
{
    int n;
    string s = "madam";
    cout << f(0, s);
    string s2 = "msdam";
    cout << endl
         << f(0, s2);

    return 0;
}

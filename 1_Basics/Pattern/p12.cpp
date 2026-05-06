#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << j;
        }
        
       for (int k = n+2; k <i ; k++)
       {
        cout<<" ";
       }
       
        
        for (int j = i; j >=1; j--)
        {
            cout<<j;

        }
        cout<<endl;

    }

    return 0;
}
// 6420
// 1234

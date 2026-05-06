#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin>>N;

        // Outer loop for rows
        for (int i = 0; i < N; i++) {
            
            // Print leading spaces (increases with row number)
            for (int j = 0; j < i; j++) {
                cout << " ";
            }

            // Print stars (decreases with row number)
            // Formula: total stars = 2*N - (2*i + 1)
            for (int j = 0; j < 2 * N - (2 * i + 1); j++) {
                cout << "*";
            }

            // Print trailing spaces (same as leading spaces)
            for (int j = 0; j < i; j++) {
                cout << " ";
            }
            cout<<endl;
            

        }
    }
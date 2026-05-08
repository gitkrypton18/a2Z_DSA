#include <iostream>
#include <stack>

using namespace std;

int main() {
	stack<int> st;
	st.push(1);
	st.push(2);
	st.emplace(5);

	cout << st.top(); // Prints 5
	st.pop();         // Deletes 5 (the top element)
	cout << st.top(); // Prints 2
	cout << st.size(); // Number of elements
	return 0;
}
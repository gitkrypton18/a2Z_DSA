#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {
	priority_queue<int> pq;
	pq.push(5);
	pq.push(2);
	pq.push(8);
	pq.emplace(10); // 10 stays at the top internally

	cout << pq.top() << endl; // Prints 10
	pq.pop();                 // Removes 10
	cout << pq.top() << endl; // Prints 8

	cout << "the above is max heap" << endl;
	cout << "the below is min heap" << endl;

	priority_queue<int, vector<int>, greater<int>> pq_min;
	pq_min.push(5);
	pq_min.push(2);
	pq_min.push(8);

	cout << pq_min.top() << endl; // Prints 2

	return 0;
}
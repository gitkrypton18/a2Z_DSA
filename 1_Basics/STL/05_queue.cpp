#include <iostream>
#include <queue>

int main() {
	std::queue<int> q;
	q.push(1);
	q.push(2);
	q.emplace(4);

	q.back() += 5; // The last element pushed (4) becomes 9.
	std::cout << q.back() << std::endl; // Prints 9
	std::cout << q.front() << std::endl; // Prints 1
	q.pop(); // Removes the FIRST element (1)

	// Show remaining elements
	while (!q.empty()) {
		std::cout << q.front() << ' ';
		q.pop();
	}
	std::cout << std::endl;
	return 0;
}
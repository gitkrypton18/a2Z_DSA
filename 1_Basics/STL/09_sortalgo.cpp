#include <bits/stdc++.h>
using namespace std;

int main() {
	// std::sort works on iterator ranges: [first, last)

	int a[] = {1, 5, 3, 2};

	// Sort the array in ascending order.
	sort(a, a + 4);

	// Sort the array in descending order using a comparator.
	sort(a, a + 4, greater<int>());

	// Sort a vector using iterators.
	vector<int> v = {1, 5, 3, 2};
	sort(v.begin(), v.end());

	return 0;
}
#include <iostream>
#include <set>

int main() {
	// -------------------------
	// std::set (unique elements)
	// -------------------------
	std::set<int> st;
	st.insert(1);
	st.emplace(2);
	st.insert(2); // Ignored, duplicates are not allowed
	st.insert(4);
	st.insert(3); // Internally stored as: {1, 2, 3, 4}

	// Find iterator
	auto it = st.find(3); // Points to 3 if found
	auto it2 = st.find(6); // If not found, returns st.end()

	// Count
	std::cout << "Count of 1 in set: " << st.count(1) << '\n'; // 1 or 0
	std::cout << "Count of 9 in set: " << st.count(9) << '\n';

	// lower_bound / upper_bound
	auto lb = st.lower_bound(2); // first element >= 2
	auto ub = st.upper_bound(2); // first element > 2
	if (lb != st.end()) {
		std::cout << "lower_bound(2): " << *lb << '\n';
	}
	if (ub != st.end()) {
		std::cout << "upper_bound(2): " << *ub << '\n';
	}

	// Erase
	st.erase(4); // O(log N): deletes key 4
	auto it3 = st.find(2);
	if (it3 != st.end()) {
		st.erase(it3); // Erase by iterator
	}

	std::cout << "Set elements: ";
	for (int x : st) {
		std::cout << x << ' ';
	}
	std::cout << "\n";

	// -------------------------------
	// std::multiset (allows duplicates)
	// -------------------------------
	std::multiset<int> ms;
	ms.insert(1);
	ms.insert(1);
	ms.insert(1); // Stored as {1, 1, 1}
	ms.insert(2);
	ms.insert(2);

	// ms.erase(1); // Removes ALL occurrences of 1

	// Erase only one occurrence safely
	auto mit = ms.find(1);
	if (mit != ms.end()) {
		ms.erase(mit); // Removes only one occurrence
	}

	std::cout << "Count of 1 in multiset: " << ms.count(1) << '\n';
	std::cout << "Count of 2 in multiset: " << ms.count(2) << '\n';

	// Erase all occurrences of 2
	ms.erase(2);

	std::cout << "Multiset elements: ";
	for (int x : ms) {
		std::cout << x << ' ';
	}
	std::cout << "\n";

	// Demonstrate not found check
	if (it != st.end()) {
		std::cout << "Found 3 in set\n";
	}
	if (it2 == st.end()) {
		std::cout << "6 not found in set\n";
	}

	return 0;
}
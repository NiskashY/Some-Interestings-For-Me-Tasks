#include "FindMaxSubarray.h"
#include <iostream>
#include <vector>


int main() {
	int n = 0;
	std::cin >> n;
	std::vector<int> vec(n);
	

	for (int i = 0, prev_number = 0; i < n; ++i) {
		std::cin >> vec[i];
		int tmp = vec[i];
		vec[i] -= prev_number;
		prev_number = tmp;
	}

	std::cout <<"(after_input): ";
	for (auto item : vec) {
		std::cout << item << ' ';
	}
	std::cout << '\n';


	auto [left, right, sum] = O_n_FindMaxSubarray(vec, 1, n - 1);
	std::cout << "left_index = " << left << '\n'
			  << "right_index = " << right << '\n' 
			  << "sum = " << sum << '\n';

	return 0;
}

#include "FindMaxSubarray.h"
#include <iostream>
#include <vector>

void Testing(const std::vector<int>& vec, int n) {
	double seconds_O_n2 = 0;
	double seconds_n = 0;
	{
		clock_t start = clock();
		auto [left, right, sum] = O_n2_FindMaxSubarray(vec, 1, n - 1);
		clock_t end = clock();
		seconds_O_n2 = (double)(end - start) / CLOCKS_PER_SEC;	
	}
	
	
	{
		clock_t start = clock();
		auto [left, right, sum] = O_n_FindMaxSubarray(vec, 1, n - 1);
		clock_t end = clock();
		seconds_n = (double)(end - start) / CLOCKS_PER_SEC;	
	}
	
	if (seconds_n <= seconds_O_n2) {
		std::cout << n << '\n';
	}
}

int main() {
	std::vector<int> vec = {100};
	srand(time(nullptr));
	
	int prev_number = vec.back();

	for (int n = 2; n <= 1000; ++n) {
		int tmp = rand() % 100 + 1;
		vec.push_back(tmp - prev_number);
		prev_number = tmp;

		Testing(vec, n);
	}

	return 0;
}

#pragma once
#include <iostream>
#include <tuple>
#include <climits>

struct MaxSubArray {
	int left = 0;
	int right = 0;
	int sum = 0;
};

template <class IndexType, class ContainerType>
// std::tuple<IndexType, IndexType, IndexType>  // returning value
MaxSubArray
FindMaxCrossingSubarray(const ContainerType& container, IndexType low, IndexType mid, IndexType high) { 
	IndexType left_sum = 0;
	IndexType max_left_index = mid;
	IndexType sub_sum = 0;
	
	for (IndexType i = mid; i >= low; --i) {
		sub_sum += container[i];
		if (sub_sum > left_sum) {
			left_sum = sub_sum;
			max_left_index = i;
		}
	}

	IndexType right_sum = 0;
	IndexType max_right_index = mid + 1;
	sub_sum = 0;

	for (IndexType i = mid + 1; i <= high; ++i) {
		sub_sum += container[i];
		if (sub_sum > right_sum) {
			right_sum = sub_sum;
			max_right_index = i;
		}
	}
	
//	return std::make_tuple(max_left_index, max_right_index, left_sum + right_sum);
	return {max_left_index, max_right_index, left_sum + right_sum};
}


template <class IndexType, class ContainerType>
// std::tuple<IndexType, IndexType, IndexType> // returning value
MaxSubArray
FindMaxSubarray(const ContainerType& container, IndexType low, IndexType high) {
	if (high == low) {
//		return std::tie(low, high, container[low]);
			return {low, high, container[low]};
	}

	IndexType mid = (low + high) / 2;

	auto [left_low, left_high, left_sum] = FindMaxSubarray(container, low, mid);
	auto [right_low, right_high, right_sum] = FindMaxSubarray(container, mid + 1, high);
	auto [cross_low, cross_high, cross_sum] = FindMaxCrossingSubarray(container, low, mid, high);

	if (left_sum >= right_sum && left_sum >= cross_sum) {
//		return std::tie(left_low, left_high, left_sum);
			return {left_low, left_high, left_sum};
	} else if (right_sum >= left_sum && right_sum >= cross_sum) {
//		return std::tie(right_low, right_high, right_sum);
			return {right_low, right_high, right_sum};
	} else {
//		return std::tie(cross_low, cross_high, cross_sum);
		return {cross_low, cross_high, cross_sum};
	}
}

template <class IndexType, class ContainerType> 
std::tuple<IndexType, IndexType, IndexType> // returning value
O_n2_FindMaxSubarray(const ContainerType& container, IndexType low, IndexType high) {

	// O(n^2) algorithm

	IndexType max_left_index = low, max_right_index = high;
	IndexType max_sum = 0;
	
	for (IndexType i = low; i <= high; ++i) {
		IndexType sub_sum = 0;
		IndexType max_sub_sum = INT_MIN;
		IndexType max_right_sub_index = i;

		for (IndexType j = i; j <= high; ++j) {
			sub_sum += container[j];
			if (sub_sum > max_sub_sum) {
				max_sub_sum = sub_sum;
				max_right_sub_index = j;
			}
		}

		if (max_sub_sum > max_sum) {
			max_sum = max_sub_sum;
			max_left_index = i;
			max_right_index = max_right_sub_index;
		}
	}
	return std::tie(max_left_index, max_right_index, max_sum);
}



template <class IndexType, class ContainerType>
MaxSubArray 
O_n_FindMaxSubarray(const ContainerType& container, IndexType low, IndexType high) {
	
	// O(n) solution
	
	MaxSubArray max_sub_array{low, low, container[low]};
	IndexType current_left = low;
	IndexType container_sum = 0;

	for (IndexType i = low; i <= high; ++i) {
		container_sum += container[i];
		if (container_sum > max_sub_array.sum) {		
			max_sub_array.left = current_left;
			max_sub_array.right = i;
			max_sub_array.sum = container_sum;	
		}
		if (container_sum < 0) {
			container_sum = 0;
			current_left = i + 1;
		}
	}
	return max_sub_array;
}


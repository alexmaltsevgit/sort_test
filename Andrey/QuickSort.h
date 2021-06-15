#pragma once
#include "ISort.h"

class QuickSort : public ISort {
public:
  QuickSort() {
    name = "БЫСТРАЯ СОРТИРОВКА";
  }

	virtual void operator()(int* array, const size_t length) override {
		int left_border = 0;
		int right_border = length - 1;
		int temp = 0;
		int comparing_element = array[0];

		while (left_border <= right_border) {
			comparisons_count++;
			while (array[left_border] > comparing_element) {
				left_border++;
				reassignments_count++;
				comparisons_count++;
			}
			comparisons_count++;
			while (array[right_border] < comparing_element) {
				right_border--;
				reassignments_count++;
				comparisons_count++;
			}
			if (left_border <= right_border) {
				std::swap(array[right_border], array[left_border]);
				left_border++;
				right_border--;

				reassignments_count += 5;
				comparisons_count++;
			}
		}
		if (right_border > 0) {
			operator()(array, right_border + 1);
		}
		if (left_border < length) {
			operator()(array + left_border, length - left_border);
		}
	}
};
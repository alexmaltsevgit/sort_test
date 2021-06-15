#pragma once
#include "ISort.h"

class QuickSort : public ISort {
public:
  QuickSort() {
    name = "БЫСТРАЯ СОРТИРОВКА";
  }

	virtual void operator()(int* array, const size_t length) override {
    int low = array[0];
    int high = array[length - 1];
    
		int left = low;
    int right = high;
    int mid = array[length / 2];

    while (left <= right) {
      while (array[left] < mid) {
        left++;
        comparisons_count += 1;
      }
      while (array[right] > mid) {
        right--;
        comparisons_count += 1;
      }

      if (left <= right) {
        swap(left, right);
        left++;
        right--;

        comparisons_count += 1;
      }

      comparisons_count += 3;
    }

    if (right > low)
      operator()(array, right + 1);
    if (left < high)
      operator()(array + left, length - left);

    comparisons_count += 3; // 2 per if, 1 per while
	}
};


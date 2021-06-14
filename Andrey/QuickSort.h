#pragma once
#include "ISort.h"

class QuickSort : public ISort {
private:
  //int partition(int* arr, int low, int high) {
  //  int pivot = arr[high];    // pivot 
  //  int i = (low - 1);

  //  for (int j = low; j <= high - 1; j++) {
  //    //if current element is smaller than pivot, increment the low element
  //    //swap elements at i and j
  //    if (arr[j] <= pivot) {
  //      i++;    // increment index of smaller element 
  //      swap(&arr[i], &arr[j]);
  //    }
  //  }
  //  swap(&arr[i + 1], &arr[high]);
  //  return (i + 1);
  //}

public:
  QuickSort() {
    name = "БЫСТРАЯ СОРТИРОВКА";
  }

	virtual void operator()(int* array, int length) override {
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


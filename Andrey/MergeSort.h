#pragma once
#include "ISort.h"
class MergeSort : public ISort {
private:
  void merge_sort(int a[], int low, int high) {
    if (low >= high)
      return;
    
    comparisons_count++;
    int mid = (low + high) / 2;
    merge_sort(a, low, mid);  
    merge_sort(a, mid + 1, high);
    merge(a, low, mid, mid + 1, high); 
  }

  void merge(int a[], int left_low, int left_high, int right_low, int right_high) {
    int length = right_high - left_low + 1;
    int* temp = new int[length];
    int left = left_low;
    int right = right_low;

    for (int i = 0; i < length; ++i) {
      if (left > left_high) {
        temp[i] = a[right++];
        comparisons_count += 2;
      }
      else if (right > right_high) {
        temp[i] = a[left++];
        comparisons_count += 3;
      }
      else if (a[left] <= a[right]) {
        temp[i] = a[left++];
        comparisons_count += 4;
      }
      else {
        temp[i] = a[right++];
        comparisons_count += 5;
      }

      reassignments_count++;
    }

    for (int i = 0; i < length; ++i)
      a[left_low++] = temp[i];

    delete[] temp;
  }

public:
	MergeSort() {
		name = "СОРТИРОВКА СЛИЯНИЕМ";
	}

	virtual void operator()(int* array, const size_t length) override {
    merge_sort(array, 0, length - 1);
	}
};


#pragma once
#include "ISort.h"
#include <algorithm>
#include <forward_list>

class RadixSort : public ISort {
private:
  int get_max_element(int* array, int length) {
    int mx = array[0];
    for (int i = 1; i < length; i++)
      if (array[i] > mx) {
        mx = array[i];
				comparisons_count++;
				reassignments_count++;
			}
		comparisons_count += 2;
    return mx;
  }

  int count_digits(int num) {
    int i = 1;
    if (num < 10)
      return 1;

    while (num > (int)pow(10, i)) {
      i++;
			reassignments_count++;
			comparisons_count++;
		}
		comparisons_count++;

    return i;
  }

public:
	RadixSort() {
		name = "ПОРАЗРЯДНАЯ СОРТИРОВКА";
	}

	virtual void operator()(int* array, const size_t length) override {
		int* temp_arr = new int[length];
		int temp = 0;
		const int divider = 10;
		size_t integer = 1;

		for (int k = 0; k < 10; k++) {
			int count[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			for (size_t i = 0; i < length; i++) {
				count[(array[i] / integer) % divider]++;

				comparisons_count++;
				reassignments_count++;
			}
			for (int i = 1; i < 10; i++) {
				count[i] = count[i] + count[i - 1];

				comparisons_count++;
				reassignments_count++;
			}
			for (int i = length - 1; i >= 0; i--) {
				temp = (array[i] / integer) % divider;
				count[temp]--;
				temp_arr[count[temp]] = array[i];

				comparisons_count++;
				reassignments_count += 3;
			}
			integer *= 10;
			std::swap(array, temp_arr);

			comparisons_count += 3;
			reassignments_count += 4;
		}

		comparisons_count++;
		delete[] temp_arr;
	}
};


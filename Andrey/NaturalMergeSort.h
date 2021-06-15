#pragma once
#include "ISort.h"
class NaturalMergeSort : public ISort {
private:
  void merge(int* arr, int first, int mid, int last) {
    // Merges two contigous sub-arrays and sorts them out-of-place
    // Condition Required: Sub-arrays must be sorted individually
    int* l = new int[mid - first];
    int* r = new int[last - mid];
    int* tempArr = new int[last - first];

    // copying into new arrays
    for (int i = 0, j = first; i < mid - first; ++i, ++j) {
      l[i] = arr[j];
      reassignments_count++;
    }
    for (int i = 0, j = mid; i < last - mid; ++i, ++j) {
      r[i] = arr[j];
      reassignments_count++;
    }

    // merge
    for (int i = 0, j = 0, k = 0; k < last - first; ++k) {
      if (i == mid - first) {
        tempArr[k] = r[j++];
        comparisons_count++;
      } else if (j == last - mid) {
        tempArr[k] = l[i++];
        comparisons_count += 2;
      } else {
        (l[i] < r[j]) ? (tempArr[k] = l[i++]) : (tempArr[k] = r[j++]);
        comparisons_count += 3;
      }
    }

    // copy into original array
    for (int i = first, j = 0; j < last - first; ++i, ++j) {
      arr[i] = tempArr[j];
      reassignments_count++;
    }

    delete[] l;
    delete[] r;
    delete[] tempArr;
  }

public:
	NaturalMergeSort() {
		name = "СОРТИРОВКА ЕСТЕСТВЕННЫМ СЛИЯНИЕМ";
	}

	virtual void operator()(int* array, const size_t length) override {
    if (length == 0) return;
    // width determines the length of the 2 arrays, the contiguous
    // arrays which are sent to the mergeOutOfPlace function.
    size_t width = 2;
    // we select arrays with length = power of 2.
    for (; width < length; width *= 2) {
      // iterating backwards as iterating forward 
      // does not work. mergeOutOfPlace is common 
      // for different merge algorithms. When iterating 
      // forward the left array has a bug
      int next = length - width, curr = length;
      for (; next >= 0; curr = next, next -= width) {
        int mid = (curr + next) / 2;
        merge(array, next, mid, curr);
      }
      // whenever array of length = pow2 is not selectable
      // we select varied length array, which is always near
      // the end of iteration
      if (curr >= 2) {
        merge(array, 0, (length % (width >> 1)), curr);
        comparisons_count++;
      }
    }
    // if array not power of 2
    if ((length % (width >> 1)) != 0)
      merge(array, 0, length % (width >> 1), length);
    // if array power of 2
    else merge(array, 0, length / 2, length);
	}
};

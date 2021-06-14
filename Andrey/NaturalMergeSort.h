#pragma once
#include "ISort.h"
class NaturalMergeSort : public ISort {
public:
	NaturalMergeSort() {
		name = "СОРТИРОВКА ЕСТЕСТВЕННЫМ СЛИЯНИЕМ";
	}

	virtual void operator()(int* arr, int length) override {

	}
};


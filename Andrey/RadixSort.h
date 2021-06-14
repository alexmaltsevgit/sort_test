#pragma once
#include "ISort.h"
class RadixSort : public ISort {
public:
	RadixSort() {
		name = "Поразрядная сортировка";
	}

	virtual void operator()(int* array, int length) override {
		
	}
};


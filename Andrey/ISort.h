#pragma once
#include <string>

class ISort {
public:
	std::string name = "";
	int comparisons_count = 0;
	int permutations_count = 0;

protected:
	ISort() {}

	virtual void swap(int& a, int& b) {
		int t = a;
		a = b;
		b = t;

		permutations_count += 1;
	}

public:
	virtual void operator()(int* array, const size_t length) = 0;
};


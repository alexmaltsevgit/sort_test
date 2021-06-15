#pragma once
#include <string>

class ISort {
public:
	std::string name = "";
	unsigned int comparisons_count = 0;
	unsigned int reassignments_count = 0;

protected:
	ISort() {}

public:
	virtual void operator()(int* array, const size_t length) = 0;
};


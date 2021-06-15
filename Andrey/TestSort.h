#pragma once
#include "ISort.h"
#include "Timer.h"
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>
#include <filesystem>

class TestSort {
private:
	std::vector<ISort*> sorts;
	std::filesystem::path unordered = "../unordered.txt";
	std::filesystem::path ordered = "../ordered.txt";
	std::filesystem::path reversed_ordered = "../reversed_ordered.txt";

public:

	#pragma region CONSTRUCTOR

	TestSort();

	TestSort(std::initializer_list<ISort*> init);

	#pragma endregion

	#pragma region MAIN

	void start(int elements_count);

	void test_few(
		ISort* sort,
		std::vector<std::filesystem::path> paths, 
		int elements_count,
		std::string_view message = ""
	);

	void test_one(
		ISort* sort,
		const std::filesystem::path& path,
		int elements_count,
		std::string_view message = ""
	);

	void add_sort(ISort* sort);

	#pragma endregion

	#pragma region FILE

	void generate_all_files(int elements_count);

	void generate_unordered(int elements_count, const std::filesystem::path& path);

	void generate_ordered(int elements_count, const std::filesystem::path& path);

	void generate_reversed_ordered(int elements_count, const std::filesystem::path& path);

	#pragma endregion

	#pragma region UTIL

private:
	int* get_array_from_file(const std::filesystem::path& path, int size);

	#pragma endregion
};

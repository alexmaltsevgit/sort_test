#pragma once
#include "ISort.h"
#include "Timer.h"
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>

class TestSort {
private:
	std::vector<ISort> sorts;
	std::fstream* unordered = nullptr;
	std::fstream* ordered = nullptr;
	std::fstream* reversed_ordered = nullptr;

public:

	#pragma region CONSTRUCTOR

	TestSort() :
		sorts()
	{};

	TestSort(std::initializer_list<ISort> init) :
		sorts(init)
	{}

	#pragma endregion

	#pragma region MAIN

	void start(int elements_count) {
		if (!(unordered && ordered && reversed_ordered))
			throw std::runtime_error("NOT ALL FILES OPENED");

		for (auto& sort : sorts) {
			test_few(
				sort,
				{unordered, ordered, reversed_ordered},
				elements_count,
				'\t' + sort.name
			);
		}
	}

	void test_few(ISort& sort, std::vector<std::fstream*> data, int elements_count, std::string_view message = "") {
		for (const auto& datum : data) {
			test_one(sort, datum, elements_count, message);
		}
	}

	void test_one(ISort& sort, std::fstream* data, int elements_count, std::string_view message = "") {
		using std::cout, std::endl;

		cout << message << '\n';
		cout << "Получаем данные..." << '\n';
		auto unord_vec = get_array_from_fstream(data, elements_count);
		Timer timer;
		sort(unord_vec, elements_count);
		cout << "Затраченное время: " << timer.elapse() << " секунд.\n";
		cout << "Количество сравнений: " << sort.comparisons_count << '\n';
		cout << "Количество перестановок: " << sort.permutations_count << '\n' << endl;
	}

	void add_sort(ISort sort) {
		sorts.push_back(sort);
	}

	#pragma endregion

	#pragma region FILE

	void set_unordered_file(std::fstream* file) {
		unordered = file;
	}

	void set_ordered_file(std::fstream* file) {
		ordered = file;
	}

	void set_ordered_file(std::fstream* file) {
		reversed_ordered = file;
	}

	void generate_all_files(int elements_count, const std::string& path) {
		generate_unordered(elements_count, path);
		generate_ordered(elements_count, path);
		generate_reversed_ordered(elements_count, path);
	}

	void generate_unordered(int elements_count, const std::string& path) {
		std::srand(std::time(nullptr));

		unordered->open(path + "unordered.txt", std::ios::in || std::ios::out);
		for (int i = 0; i < elements_count; i++) {
			*unordered << -100 + rand() % 100;
		}
	}

	void generate_ordered(int elements_count, const std::string& path) {
		std::srand(std::time(nullptr));
		std::vector<int> tmp{elements_count};

		unordered->open(path + "ordered.txt", std::ios::in || std::ios::out);
		for (int i = 0; i < elements_count; i++) {
			std::sort(tmp.begin(), tmp.end());
		}
	}

	void generate_reversed_ordered(int elements_count, const std::string& path) {
		std::srand(std::time(nullptr));
		std::vector<int> tmp{ elements_count };

		unordered->open(path + "ordered_reversed.txt", std::ios::in || std::ios::out);
		for (int i = 0; i < elements_count; i++) {
			std::sort(tmp.begin(), tmp.end(), [](int a, int b) {a > b;});
		}
	}

	#pragma endregion

	#pragma region UTIL

private:
	int* get_array_from_fstream(std::fstream* stream, int size) {
		int* arr = new int[size];
		for (int i = 0; i < size; i++) {
			*stream >> arr[i];
		}
		return arr;
	}

	#pragma endregion

	#pragma region DESTRUCTOR

	~TestSort() {
		if (unordered) unordered->close();
		if (ordered) ordered->close();
		if (reversed_ordered) reversed_ordered->close();
	}

	#pragma endregion
};

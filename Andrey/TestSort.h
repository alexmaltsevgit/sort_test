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

	TestSort() :
		sorts()
	{};

	TestSort(std::initializer_list<ISort*> init) :
		sorts(init)
	{}

	#pragma endregion

	#pragma region MAIN

	void start(int elements_count) {
		for (auto& sort : sorts) {
			test_few(
				sort,
				{unordered, ordered, reversed_ordered},
				elements_count,
				'\t' + sort->name
			);
		}
	}

	void test_few(
		ISort* sort,
		std::vector<std::filesystem::path> paths, 
		int elements_count,
		std::string_view message = ""
	) {
		for (auto& path : paths) {
			test_one(sort, path, elements_count, message);
		}
	}

	void test_one(
		ISort* sort,
		const std::filesystem::path& path,
		int elements_count,
		std::string_view message = ""
	) {
		using std::cout, std::endl;

		cout << message << '\n';
		int* arr = get_array_from_file(path, elements_count);
		Timer timer;
		sort->operator()(arr, elements_count);
		cout << "Файл: " << path << '\n';
		cout << "Затраченное время: " << timer.elapse() << " секунд.\n";
		cout << "Количество сравнений: " << sort->comparisons_count << '\n';
		cout << "Количество переприсваиваний: " << sort->reassignments_count << '\n' << endl;

		delete[] arr;
	}

	void add_sort(ISort* sort) {
		sorts.push_back(sort);
	}

	#pragma endregion

	#pragma region FILE

	void generate_all_files(int elements_count) {
		generate_unordered(elements_count, unordered);
		generate_ordered(elements_count, ordered);
		generate_reversed_ordered(elements_count, reversed_ordered);
	}

	void generate_unordered(int elements_count, const std::filesystem::path& path) {
		std::srand(std::time(nullptr));

		std::ofstream out;
		out.open(path, std::ios::out);

		for (int i = 0; i < elements_count; i++) {
			out << -50 + rand() % 100 << " ";
		}

		out.close();
	}

	void generate_ordered(int elements_count, const std::filesystem::path& path) {
		std::srand(std::time(nullptr));
		std::vector<int> tmp;
		tmp.resize(elements_count);

		std::ofstream out;
		out.open(path, std::ios::out);

		for (auto& i : tmp)
			i = -50 + rand() % 100;
		std::sort(tmp.begin(), tmp.end());
		for (const auto& i : tmp)
			out << i << " ";

		out.close();
	}

	void generate_reversed_ordered(int elements_count, const std::filesystem::path& path) {
		std::srand(std::time(nullptr));
		std::vector<int> tmp;
		tmp.resize(elements_count);

		std::ofstream out;
		out.open(path, std::ios::out);

		for (auto& i : tmp)
			i = -50 + rand() % 100;
		std::sort(tmp.begin(), tmp.end(), [](const int& a, const int& b) -> bool { return a > b; });
		for (const auto& i : tmp)
			out << i << " ";

		out.close();
	}

	#pragma endregion

	#pragma region UTIL

private:
	int* get_array_from_file(const std::filesystem::path& path, int size) {
		int* arr = new int[size];
		std::ifstream in{path};
		for (int i = 0; i < size; i++) {
			in >> arr[i];
		}
		in.close();
		return arr;
	}

	#pragma endregion
};

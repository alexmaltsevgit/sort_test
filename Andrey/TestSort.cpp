#include "TestSort.h"

TestSort::TestSort() :
	sorts() {}

TestSort::TestSort(std::initializer_list<ISort*> init) :
	sorts(init) {}

void TestSort::start(int elements_count) {
	for (auto& sort : sorts) {
		test_few(
			sort,
			{ unordered, ordered, reversed_ordered },
			elements_count,
			'\t' + sort->name
		);
	}
}

void TestSort::test_few(ISort* sort, std::vector<std::filesystem::path> paths, int elements_count, std::string_view message) {
	for (auto& path : paths) {
		test_one(sort, path, elements_count, message);
	}
}

void TestSort::test_one(ISort* sort, const std::filesystem::path& path, int elements_count, std::string_view message) {
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

void TestSort::add_sort(ISort* sort) {
	sorts.push_back(sort);
}

void TestSort::generate_all_files(int elements_count) {
	generate_unordered(elements_count, unordered);
	generate_ordered(elements_count, ordered);
	generate_reversed_ordered(elements_count, reversed_ordered);
}

void TestSort::generate_unordered(int elements_count, const std::filesystem::path& path) {
	std::srand(std::time(nullptr));

	std::ofstream out;
	out.open(path, std::ios::out);

	for (int i = 0; i < elements_count; i++) {
		out << -50 + rand() % 100 << " ";
	}

	out.close();
}

void TestSort::generate_ordered(int elements_count, const std::filesystem::path& path) {
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

void TestSort::generate_reversed_ordered(int elements_count, const std::filesystem::path& path) {
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

int* TestSort::get_array_from_file(const std::filesystem::path& path, int size) {
	int* arr = new int[size];
	std::ifstream in{ path };
	for (int i = 0; i < size; i++) {
		in >> arr[i];
	}
	in.close();
	return arr;
}

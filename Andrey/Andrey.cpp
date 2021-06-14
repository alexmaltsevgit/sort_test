#include "TestSort.h"
#include "QuickSort.h"
#include <filesystem>

#define N1 10000
#define N2 60000
#define N3 110000
#define N4 160000

int main() {
	std::filesystem::path path = "../";
	std::string absolute_path = std::filesystem::absolute(path).string();
	TestSort test{
		new QuickSort()
	};

	test.generate_all_files(N1, absolute_path);
	test.start(N1);
}

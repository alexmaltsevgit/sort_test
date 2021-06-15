#include "TestSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "NaturalMergeSort.h"
#include "RadixSort.h"
#include <filesystem>

enum class Modes : int {
	N1 = 10000,
	N2 = 60000,
	N3 = 110000,
	N4 = 160000
};

int main() {
	// change this to test for another array size
	constexpr int mode = static_cast<int>(Modes::N1);

	// change this to choose another path
	std::filesystem::path path = "../";

	std::string absolute_path = std::filesystem::absolute(path).string();
	TestSort test{
		new QuickSort(),
		new MergeSort(),
		new NaturalMergeSort(),
		new RadixSort()
	};

	test.generate_all_files(mode, absolute_path);
	test.start(mode);
}

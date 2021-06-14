#pragma once
#include <chrono>

class Timer {
	using highres = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

private:
	std::chrono::time_point<highres> time;

public:
	Timer() : time(highres::now()) {}

	void reset() {
		time = highres::now();
	}

	double elapse() const {
		return std::chrono::duration_cast<second_t>(highres::now() - time).count();
	}
};

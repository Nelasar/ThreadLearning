#include "randomizer.h"

void int_randomizer::randomize(std::vector<int>& vec, int from, int to) {
	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };
	std::uniform_int_distribution<int> dist(from, to);

	auto gen = [&mersenne_engine, &dist]() {return dist(mersenne_engine); };
	std::generate(std::begin(vec), std::end(vec), gen);
}
#include "thread_summator.h"

void thread_summator::compute_sum(std::vector<std::thread>& threads, std::vector<std::vector<int>>& splits,
	int size, int& result) {
	for (int i = 0; i < size; i++) {
		threads.push_back((std::move(std::thread([&result, &splits, i]() mutable {
			result += std::accumulate(splits[i].begin(), splits[i].end(), 0);//func(splits[i]);
			}))));
	}
}

void thread_summator::perform(std::vector<std::thread>& vec){
	std::for_each(vec.begin(), vec.end(), [](std::thread& t1) { t1.join(); });
}
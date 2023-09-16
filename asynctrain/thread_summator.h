#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <algorithm>
#include <numeric>
#include <future>

class thread_summator
{
public:
	static void compute_sum(std::vector<std::thread>&, std::vector<std::vector<int>>&, int, int&);
	static void perform(std::vector<std::thread>&);
};


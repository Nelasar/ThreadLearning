#include "for_summator.h"

void for_summator::compute_sum(std::vector<int>& const vec, int& result){
	int size = vec.size();
	for (int i = 0; i < size; i++) {
		result += vec[i];
	}
}
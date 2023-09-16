#include "vector_splitter.h"

void vector_splitter::split(std::vector<int>& vector, std::vector<std::vector<int>>& result, int size, int elems) {

	for (int i = 0; i < size; i++) {
		std::vector<int>::iterator first = vector.begin() + elems * i;
		std::vector<int>::iterator second = first + (elems - 1);

		result[i] = std::vector<int>(first, second + 1);
	}
}
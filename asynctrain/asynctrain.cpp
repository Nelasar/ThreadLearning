#include <iostream>
#include <thread>
#include <numeric>
#include <chrono>
#include "randomizer.h"
#include "vector_splitter.h"
#include "thread_summator.h"
#include "for_summator.h"

// функции для печати массивов, использовались при тестах, можно использовать при малых значениях n
void print_1d_array(std::vector<int>& vec) {
	for (auto i : vec) {
		std::cout << vec[i] << ' ';
	}
	std::cout << std::endl;
}
// функции для печати массивов, использовались при тестах, можно использовать при малых значениях n
void print_2d_array(std::vector<std::vector<int>>& vec) {
	int len = vec.size();
	for (int i = 0; i < len; i++) {
		int sublen = vec[i].size();
		for (int j = 0; j < sublen; j++) {
			std::cout << vec[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

const int SIZE = 2;		// кол-во измерений, всего два - для потоков и цикла
const int TESTS = 8;	// 

std::chrono::microseconds test_results[TESTS][SIZE]; // результаты производительности

int main()
{
	int result = 0;			// результат для ПОТОКОВ
	int for_result = 0;		// результат для ЦИКЛА
	int n = 0;				// кол-во чисел
	int m = 0;				// кол-во потоков (частей)
	int num_of_elems = 0;	// кол-во элементов в потоке

	/*
	std::cout << "Input N: " << std::endl;
	std::cin >> n;
	std::cout << "Input M: " << std::endl;
	std::cin >> m;*/

	int n_array[TESTS] = { 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000, 100'000'000 }; // массив размерностей исходного вектора
	int m_array[TESTS] = { 5,  10,   10,  10,  10,   10,  10,  10 };							  // массов частей 

	for (int i = 0; i < TESTS; i++) {
		std::cout << "C O M P U T I N G . . . " << i + 1 << " OF " << TESTS << '\n' << std::endl;

		n = n_array[i];
		m = m_array[i];
		num_of_elems = n / m;
		std::cout << "Setup data:\nN = " << n << "\nM = " << m << "\nNum of Elements = " << num_of_elems << std::endl;

		std::vector<int> vec(n, 0);
		std::vector<std::thread> threads;
		std::vector<std::vector<int>> vec_2(m);

		int_randomizer::randomize(vec, 0, 9);
		vector_splitter::split(vec, vec_2, m, num_of_elems);
		thread_summator::compute_sum(threads, vec_2, m, result);

		auto start = std::chrono::high_resolution_clock::now();
		thread_summator::perform(threads);
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "\nTime taken by THREADS: " << duration.count() << " microseconds" << std::endl;

		test_results[i][0] = duration;

		start = std::chrono::high_resolution_clock::now();
		for_summator::compute_sum(vec, for_result);
		stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		std::cout << "\nTime taken by FOR: " << duration.count() << " microseconds" << std::endl;

		test_results[i][1] = duration;

		std::cout << "FOR RESULT: " << for_result << std::endl;
		std::cout << "THREADING RESULT: " << result << std::endl;

		if (result != for_result) return 1;

		system("pause");
		system("cls");
	}

	// ВЫВОД РЕЗУЛЬТАТОВ ТЕСТА В ТАБЛИЦУ
	
	std::cout << "|| SIZE OF N || THREAD RESULT ||  FOR RESULT  ||\n";
	for (int i = 0; i < TESTS; i++) {
		std::cout << "||--------------------------------------------||\n";
		std::cout << "||" << std::setw(11) << n_array[i] << "||" << std::setw(15) << test_results[i][0] << "||" << std::setw(14) << test_results[i][1] << "||\n";
	}
	std::cout << "||--------------------------------------------||\n";
	system("pause");

	return 0;
}

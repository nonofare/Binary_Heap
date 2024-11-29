#include <iostream>
#include <random>
#include <chrono>
#include "BH.h"

struct some_object {
	int field_1;
	char field_2;
};

std::string so_cmp_string(some_object* so) {
	return "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")";
}

bool so_cmp_lgreater(some_object* so1, some_object* so2) {
	if (so1->field_1 == so2->field_1) {
		return so1->field_2 > so2->field_2;
	}
	return so1->field_1 > so2->field_1;
}

int main() {
	const int MAX_ORDER = 6;
	const int LETTES_SIZE = 26;
	const char LETTERS[LETTES_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	static std::random_device rd;
	static std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> rnd_num(0, MAX_ORDER * 1000);
	std::uniform_int_distribution<int> rnd_let(0, LETTES_SIZE - 1);

	BH::BinHeap<some_object*>* bh = new BH::BinHeap<some_object*>();

	for (int i = 1; i <= MAX_ORDER; i++) {
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Test: " << i << std::endl << std::endl;

		int n = pow(10, i);

		std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
		for (int j = 1; j <= n; j++) {
			some_object* so = new some_object();
			so->field_1 = rnd_num(dre);
			so->field_2 = LETTERS[rnd_let(dre)];
			try {
				bh->Push(so, so_cmp_lgreater);
			}
			catch (const std::exception& ex) {
				std::cerr << "Eror in push " << j << " -> " << ex.what() << std::endl;
			}
			so = nullptr;
		}
		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> pushing_time = end_time - start_time;
		std::cout << "Pushing time: " << pushing_time.count() << "s" << std::endl;
		std::cout << bh->ToString(16, so_cmp_string);

		start_time = std::chrono::high_resolution_clock::now();
		for (int j = 1; j <= n; j++) {
			try {
				some_object* so = bh->Poll(so_cmp_lgreater);
				delete so;
			}
			catch (const std::exception& ex) {
				std::cerr << "Eror in poll " << j << " -> " << ex.what() << std::endl;
			}
		}
		end_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> extracting_time = end_time - start_time;
		std::cout << std::endl << "Extracting time: " << extracting_time.count() << "s" << std::endl;
		std::cout << bh->ToString(16, so_cmp_string);

		double total_time = pushing_time.count() + extracting_time.count();
		std::cout << std::endl << "Total time: " << total_time << "s" << std::endl;

		bh->Erase();
	}

	delete bh;
	return 0;
}
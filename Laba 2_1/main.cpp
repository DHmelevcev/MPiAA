#include "count_sort.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

vector<int> random_sequence(int size, int max) {
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, max);
	vector<int> result;
	for (int i = 0; i < size; i++) {
		result.push_back(distribution(generator));
	}
	return result;
}

vector<int> read_file(ifstream& file) {
	vector<int> result;
	while (file) {
		int n;
		file >> n;
		if (file)
			result.push_back(n);
	}
	return result;
}

int main(int argc, char** argv) {

	//ofstream ofs("random_sequence_10000000.txt");
	//vector<int> v = random_sequence(10000000, 20000000);
	//copy(v.begin(), v.end(), std::ostream_iterator<int>(ofs, " "));

	vector<string> inputs = {
		"random_sequence_10.txt",
		"random_sequence_100.txt",
		"random_sequence_1000.txt",
		"random_sequence_10000.txt",
		"random_sequence_100000.txt",
		"random_sequence_1000000.txt",
		"random_sequence_10000000.txt",
	};

	for (auto i : inputs) {
		ifstream input(i);
		vector<int> test_sequence = read_file(input);
		input.close();

		int min = *min_element(test_sequence.begin(), test_sequence.end());
		int max = *max_element(test_sequence.begin(), test_sequence.end());
		auto t1 = std::chrono::high_resolution_clock::now();
		vector<int> sortet_sequence = count_sort(test_sequence, min, max);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time1 = std::chrono::duration<double>(t2 - t1).count();
		
		t1 = std::chrono::high_resolution_clock::now();
		sort(test_sequence.begin(), test_sequence.end());
		t2 = std::chrono::high_resolution_clock::now();
		double time2 = std::chrono::duration<double>(t2 - t1).count();

		cout << i << "\ncount sort: " << time1 << "\nquick sort: " << time2 << endl;
	}

    int result = Catch::Session().run(argc, argv);
    return result;
}
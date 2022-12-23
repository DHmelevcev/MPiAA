#include "duplicates.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <numeric>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

vector<int> one_number_sequence(int size, int number) {
	vector<int> result;
	for (int i = 0; i < size; i++) {
		result.push_back(number);
	}
	return result;
}

vector<int> random_sequence(int size, int max) {
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, max);
	vector<int> result;
	for (int i = 0; i < size; i++) {
		result.push_back(distribution(generator));
	}
	return result;
}

vector<int> unique_sequence(int size, int start = 0) {
	vector<int> result(size);
	iota(result.begin(), result.end(), start);
	random_shuffle(result.begin(), result.end());
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
	
	//ofstream ofs("unique_sequence_1000000.txt");
	//vector<int> v = unique_sequence(1000000);
	//copy(v.begin(), v.end(), std::ostream_iterator<int>(ofs, " "));

	vector<string> inputs = {
		"one_number_sequence_10.txt",
		"one_number_sequence_100.txt",
		"one_number_sequence_1000.txt",
		"one_number_sequence_10000.txt",
		"one_number_sequence_100000.txt",
		//"one_number_sequence_1000000.txt",
		"random_sequence_10.txt",
		"random_sequence_100.txt",
		"random_sequence_1000.txt",
		"random_sequence_10000.txt",
		"random_sequence_100000.txt",
		//"random_sequence_1000000.txt",
		"unique_sequence_10.txt",
		"unique_sequence_100.txt",
		"unique_sequence_1000.txt",
		"unique_sequence_10000.txt",
		"unique_sequence_100000.txt",
		//"unique_sequence_1000000.txt",
	};

	for (auto i : inputs) {
		ifstream input (i);
		vector<int> test_sequence = read_file(input);
		input.close();

		auto t1 = std::chrono::high_resolution_clock::now();
		bool result1 = has_duplicates(test_sequence);
		//bool result1 = has_duplicates_set(test_sequence);
		//bool result1 = has_duplicates_sort(test_sequence);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time1 = std::chrono::duration<double>(t2 - t1).count();
		cout << i;
		if (result1)
			cout << ": duplicates found\n";
		else
			cout << ": duplicates not found\n";

		t1 = std::chrono::high_resolution_clock::now();
		vector<int> result2 = get_duplicates(test_sequence);
		//vector<int> result2 = get_duplicates_set(test_sequence);
		//vector<int> result2 = get_duplicates_sort(test_sequence);
		t2 = std::chrono::high_resolution_clock::now();
		double time2 = std::chrono::duration<double>(t2 - t1).count();
		cout << "Amount of duplicates: " << result2.size() << endl;
		cout << '(' << time1 << ") (" << time2 << ")\n\n\n";
	}

	int result = Catch::Session().run(argc, argv);
	return result;
}
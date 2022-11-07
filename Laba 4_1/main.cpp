#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "lcs.h"
#include "random_string.h"
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>

using namespace std;

pair<string, string> read_file(ifstream& file) {
	pair<string, string> result;
		string str1;
		string str2;
		file >> str1;
		if (!file)
			return {};
		file >> str2;
		if (file)
			result = make_pair(str1, str2);
	return result;
}

int main(int argc, char* argv[]) {

	//ofstream ofs("random_pair_string_100000.txt");
	//ofs << random_string(100000) << '\n' << random_string(100000);


	vector<string> strings = {
		"random_pair_string_5.txt",
		"random_pair_string_10.txt",
		"random_pair_string_15.txt",
		"random_pair_string_20.txt",
		"random_pair_string_100.txt",
		"random_pair_string_1000.txt",
		"random_pair_string_10000.txt",
		//"random_pair_string_100000.txt",
	};

	for (auto i : strings) {
		ifstream input(i);
		pair<string, string> pair = read_file(input);
		input.close();

		cout << i << ":\n";

		auto t1 = std::chrono::high_resolution_clock::now();
		lcs(pair.first, pair.second);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time = std::chrono::duration<double>(t2 - t1).count();

		cout << "time: " << setw(8) << time << "\n===============================================================================\n";
	}

    int result = Catch::Session().run(argc, argv);
    return result;
}
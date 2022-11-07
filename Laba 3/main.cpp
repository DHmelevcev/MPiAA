#include "closest_pair.h"

#include <iomanip>
#include <fstream>
#include <chrono>
#include <numeric>

using namespace std;

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

vector<double> random_sequence(int size, int max) {
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, max);
	vector<double> result;
	for (int i = 0; i < size; i++) {
		result.push_back(double(distribution(generator) - max / 2) / 10);
	}
	return result;
}

vector<Point> read_file(ifstream& file) {
	vector<Point> result;
	while (file) {
		double X;
		double Y;
		file >> X;
		if (!file)
			break;
		file >> Y;
		if (file)
			result.push_back(Point(X, Y));
	}
	return result;
}

int main(int argc, char** argv) {

	//int size = 1000000;
	//ofstream ofs("random_points_1000000.txt");
	//vector<double> v = random_sequence(size * 2, 1000);
	//copy(v.begin(), v.end(), std::ostream_iterator<double>(ofs, " "));

	vector<string> inputs = {
		"random_points_10.txt",
		"random_points_100.txt",
		"random_points_1000.txt",
		"random_points_10000.txt",
		"random_points_100000.txt",
		"random_points_1000000.txt",
	};

	for (auto i : inputs) {
		ifstream input(i);
		vector<Point> test_points = read_file(input);
		input.close();

		cout << i << ":\n";

		auto t1 = std::chrono::high_resolution_clock::now();
		pair<Point, Point> closest_points = closest_pair(test_points);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time = std::chrono::duration<double>(t2 - t1).count();

		cout << "\nClosest points found in: " << setw(12) << time << endl;

		cout << "===============================================================================\n";
	}

    int result = Catch::Session().run(argc, argv);
    return result;
}
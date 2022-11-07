#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "activities.h"
#include <chrono>
#include <iomanip>
#include <fstream>

using namespace std;

vector<Activity> read_file(ifstream& file) {
	vector<Activity> result;
	while (file) {
		int x;
		int y;
		file >> x;
		if (!file)
			break;
		file >> y;
		if (file)
			result.push_back(Activity(x, y));
	}
	return result;
}

int main(int argc, char* argv[]) {

	//int size = 10;
	//ofstream ofs("random_activities_10.txt");
	//default_random_engine generator;
	//uniform_int_distribution<int> distribution(0, size);
	//for (int i = 0; i < size; i++) {
	//	int x = distribution(generator);
	//	ofs << x << ' ' << x + 1 + (distribution(generator) % (size / 2)) << '\n';
	//}


	vector<string> strings = {
		"random_activities_10.txt",
		"random_activities_15.txt",
		"random_activities_20.txt",
		"random_activities_30.txt",
		"random_activities_40.txt",
		"random_activities_50.txt",
		"random_activities_100.txt",
		"random_activities_1000.txt",
		"random_activities_10000.txt",
		//"random_activities_100000.txt",
		//"random_activities_1000000.txt",
	};

	for (auto i : strings) {
		ifstream input(i);
		vector<Activity> activities = read_file(input);
		input.close();

		cout << i << ":\n";

		auto t1 = std::chrono::high_resolution_clock::now();
		get_max_activities(activities);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time = std::chrono::duration<double>(t2 - t1).count();

		cout << "time: " << setw(8) << time << "\n===============================================================================\n";
	}

    int result = Catch::Session().run(argc, argv);
    return result;
}
#include "dictionary.h"
#include "hash_functions.h"
#include "random_string.h"
#include <iomanip>
#include <fstream>
#include <map>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

vector<string> read_file(ifstream& file) {
	vector<string> result;
	while (file) {
		string str;
		file >> str;
		if (file)
			result.push_back(str);
	}
	return result;
}

int main(int argc, char** argv) {

	//ofstream ofs("random_keys_1000000.txt");
	//for (int i = 0; i < 1000000; i++) {
	//	string key = random_string(1 + i % 10);
	//	ofs << key << ' ';
	//}


	vector<string> keys = {
		"random_keys_10.txt",
		"random_keys_100.txt",
		"random_keys_1000.txt",
		"random_keys_10000.txt",
		"random_keys_100000.txt",
		"random_keys_1000000.txt",
	};

	string value = "";
	int number_of_keys_to_found = 1000;

	for (auto i : keys) {
		ifstream input(i);
		vector<string> test_keys = read_file(input);
		input.close();

		vector<string> keys_to_found(number_of_keys_to_found);
		for (int i = 0; i < keys_to_found.size(); i++)
			keys_to_found[i] = random_string(1 + i % 10);

		Dictionary MyDictionary(pow(10, i.size() - keys[0].size() + 1));
		Dictionary MyDictionary1(pow(10, i.size() - keys[0].size() + 1), hash1);
		Dictionary MyDictionary2(pow(10, i.size() - keys[0].size() + 1), hash2);
		Dictionary MyDictionary3(pow(10, i.size() - keys[0].size() + 1), hash3);
		map<string, string> MyMap;

		cout << i << ":\n";

		auto t1 = std::chrono::high_resolution_clock::now();
		for (auto key : test_keys)
			MyDictionary.set(key, value);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time11 = std::chrono::duration<double>(t2 - t1).count();

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : keys_to_found)
			MyDictionary.get(key);
		t2 = std::chrono::high_resolution_clock::now();
		double time12 = std::chrono::duration<double>(t2 - t1).count();

		cout << "\nstd::hash:\nInsert: " << setw(8) << time11 << "\tSearch: " << time12 << endl;

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : test_keys)
			MyDictionary1.set(key, value);
		t2 = std::chrono::high_resolution_clock::now();
		double time21 = std::chrono::duration<double>(t2 - t1).count();

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : keys_to_found)
			MyDictionary1.get(key);
		t2 = std::chrono::high_resolution_clock::now();
		double time22 = std::chrono::duration<double>(t2 - t1).count();

		cout << "\nhash1:\nInsert: " << setw(8) << time21 << "\tSearch: " << time22 << endl;

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : test_keys)
			MyDictionary2.set(key, value);
		t2 = std::chrono::high_resolution_clock::now();
		double time31 = std::chrono::duration<double>(t2 - t1).count();

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : keys_to_found)
			MyDictionary2.get(key);
		t2 = std::chrono::high_resolution_clock::now();
		double time32 = std::chrono::duration<double>(t2 - t1).count();

		cout << "\nhash2:\nInsert: " << setw(8) << time31 << "\tSearch: " << time32 << endl;

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : test_keys)
			MyDictionary3.set(key, value);
		t2 = std::chrono::high_resolution_clock::now();
		double time41 = std::chrono::duration<double>(t2 - t1).count();

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : keys_to_found)
			MyDictionary3.get(key);
		t2 = std::chrono::high_resolution_clock::now();
		double time42 = std::chrono::duration<double>(t2 - t1).count();

		cout << "\nhash3:\nInsert: " << setw(8) << time41 << "\tSearch: " << time42 << endl;

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : test_keys)
			MyMap.insert(pair<string, string>(key, value));
		t2 = std::chrono::high_resolution_clock::now();
		double time51 = std::chrono::duration<double>(t2 - t1).count();

		t1 = std::chrono::high_resolution_clock::now();
		for (auto key : keys_to_found)
			MyMap.find(key);
		t2 = std::chrono::high_resolution_clock::now();
		double time52 = std::chrono::duration<double>(t2 - t1).count();

		cout << "\nmap:\nInsert: " << setw(8) << time51 << "\tSearch: " << time52 << endl;

		cout << "===============================================================================\n";
	}

    int result = Catch::Session().run(argc, argv);
    return result;
}
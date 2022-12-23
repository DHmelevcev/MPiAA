#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>
#include <vector>
#include <set>
#include <list>

using namespace std;

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
vector<int> shuffled_sequence(int size, int start = 0) {
    vector<int> result(size);
    iota(result.begin(), result.end(), start);
    random_shuffle(result.begin(), result.end());
    return result;
}

// Returns sequence of random numbers of specified size, with values from 0 to max.
vector<int> random_sequence(int size, int max) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, max);
    vector<int> result;
    for (int i = 0; i < size; i++) {
        result.push_back(distribution(generator));
    }
    return result;
}

int main() {
    const int size = 1000000;

    // Container to use.
    //vector<int> container;
    //list <int> container;
    set <int> container;



    // Insert elements into container.
    const auto elems_to_add = shuffled_sequence(size);

    auto t1 = std::chrono::high_resolution_clock::now();
    for (const auto& elem : elems_to_add) {
        //container.push_back(elem);
        container.insert(elem);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    double time1 = std::chrono::duration<double>(t2 - t1).count();

    //container.clear();

    //t1 = std::chrono::high_resolution_clock::now();
    //for (const auto& elem : elems_to_add) {
    //    //container.insert(container.begin(), elem);
    //    container.push_front(elem);
    //}
    //t2 = std::chrono::high_resolution_clock::now();
    //double time2 = std::chrono::duration<double>(t2 - t1).count();



    // Perform search into container.
    int hits = 0;
    const auto elems_to_search = random_sequence(1000, 2 * size);

    t1 = std::chrono::high_resolution_clock::now();
    for (const auto& elem : elems_to_search) {
        //auto it = find(container.begin(), container.end(), elem);
        auto it = container.find(elem);
        if (it != container.end()) {
            hits++;
        }
    }
    t2 = std::chrono::high_resolution_clock::now();
    double time3 = std::chrono::duration<double>(t2 - t1).count();



    cout << "Found " << hits << " elements" << endl;
    cout << "Insert end " << time1 << " seconds" << endl;
    //cout << "Insert begin " << time2 << " seconds" << endl;
    cout << "Search " << time3 << " seconds" << endl;
}
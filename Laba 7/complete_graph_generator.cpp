#include <algorithm>
#include <ctime>

#include "complete_graph_generator.h"

using namespace std;

vector<tuple<int, int, double>> generate_complete_graph_edges(int vertices_size, double max_weight) {

	vector<tuple<int, int, double>> result;
	srand(time(NULL) % rand());

	if (vertices_size > 1)
		for (int i = 0; i < vertices_size - 1; i++)
			for (int j = i + 1; j < vertices_size; j++)
				result.push_back(tuple<int, int, double>(i, j, double(rand() % int(max_weight * 100)) / 100));

	return result;
}
#include "complete_graph_generator.h"

using namespace std;

vector<pair<pair<int, int>, double>> generate_complete_graph_edges(int vertices_size, double max_weight) {

	vector<pair<pair<int, int>, double>> result;

	for (int i = 0; i < vertices_size - 1; i++)
		for (int j = i + 1; j < vertices_size; j++)
			result.push_back(make_pair(make_pair(i, j), double(rand() % int(max_weight * 100)) / 100));

	return result;
}
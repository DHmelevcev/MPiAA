#include "random_graph_generator.h"

using namespace std;

vector<int> shuffled_sequence(int size, int start = 0) {
	vector<int> result(size);
	iota(result.begin(), result.end(), start);
	random_shuffle(result.begin(), result.end());
	return result;
}

int find_set_v(vector <int>& parent, int v) {
	return (v == parent[v]) ? v : find_set_v(parent, parent[v]);
}

void union_sets_v(vector <int>& parent, int a, int b) {
	a = find_set_v(parent, a);
	b = find_set_v(parent, b);
	parent[b] = a;
}

vector<pair<pair<int, int>, double>> generate_random_graph_edges(int vertices_size, int edges_size, double max_weight) {

	vector<pair<pair<int, int>, double>> result;

	vector<int> vertices_to_union = shuffled_sequence(vertices_size);

	vector<int> parent(vertices_size);
	iota(parent.begin(), parent.end(), 0);

	for (int i = 0; i < vertices_size; i++) {
		if (find_set_v(parent, i) != find_set_v(parent, vertices_to_union[i])) {
			result.push_back(make_pair(make_pair(i, vertices_to_union[i]), double(rand() % int(max_weight * 1000)) / 100));
			union_sets_v(parent, i, vertices_to_union[i]);
		}
		if (i == vertices_to_union[i])
			result.push_back(make_pair(make_pair(i, (i - 1 < 0) ? i - 1 : i + 1), double(rand() % int(max_weight * 1000)) / 100));
	}

	while (result.size() < edges_size) {
		int u = rand() % vertices_size;
		int v = rand() % vertices_size;
		if (u != v)
			result.push_back(make_pair(make_pair(u, v), double(rand() % int(max_weight * 1000)) / 100));
	}

	return result;
}
#include "min_spanning_tree.h"

using namespace std;

int find_set(vector <int>& parent, int v) {
	return (v == parent[v]) ? v : parent[v] = find_set(parent, parent[v]);
}

void union_sets(vector <int>& parent, vector <int>& rank, int a, int b) {
	a = find_set(parent, a);
	b = find_set(parent, b);
	if (rank[a] < rank [b])
		swap(a, b);
	rank[a] = max(rank[a], rank[b] + 1);
	parent[b] = a;
}

vector<pair<int, int>> min_spanning_tree(const Graph& graph) {
	// Return minimal spanning tree (MST) for the graph as array of edges.
	// Each edge is represented by its two vertices.
	// Order of edges in result and vertices in edges doesn't matter.
	// Return empty array if MST doesn't exist.

	vector<pair<int, int>> result;

	vector <pair<pair<int, int>, double>> edges = graph.get_edges();
	sort(edges.begin(), edges.end(), [](pair<pair<int, int>, double>& a, pair<pair<int, int>, double>& b) { return a.second < b.second; });

	size_t vertices_size = graph.get_vertices().size();
	vector <int> rank(vertices_size);
	vector <int> parent(vertices_size);
	iota(parent.begin(), parent.end(), 0);

	for (auto e : edges) {
		if (find_set(parent, e.first.first) != find_set(parent, e.first.second)) {
			result.push_back(make_pair(e.first.first, e.first.second));
			union_sets(parent, rank, e.first.first, e.first.second);
		}
	}

	return result;
}
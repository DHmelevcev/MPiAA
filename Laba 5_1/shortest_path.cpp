#include "shortest_path.h"

using namespace std;

vector<int> build_path(vector<int> parent, int start_vertex, int end_vertex) {
	vector<int> result;
	
	if (start_vertex != end_vertex) {
		result.push_back(end_vertex);

		for (int cur_v = end_vertex; cur_v != start_vertex;) {
			result.push_back(parent[cur_v]);
			cur_v = parent[cur_v];
		}
		reverse(result.begin(), result.end());
	}
	
	return result;
}

vector<int> shortest_path(const Graph& graph, int start_vertex, int end_vertex) {
	// Return shortest path in the graph from start vertex to end vertex as array of vertices.
	// First item in the result should be start vertex, last - end vertex.
	// Return empty array if there is no path.

	constexpr int INF = numeric_limits<int>::max();

	vector<int> vertices = graph.get_vertices();

	if (vertices.size()) {
		vector<int> distance(vertices.size(), INF), parent(vertices.size());
		distance[start_vertex] = 0;

		priority_queue <pair<double, int>> queue;
		queue.push(make_pair(0, start_vertex));

		while (!queue.empty()) {
			int u = queue.top().second;
			double cur_distance = -queue.top().first;
			queue.pop();

			if (u == end_vertex)
				return build_path(parent, start_vertex, end_vertex);

			if (cur_distance > distance[u])  continue;

			vector<pair<int, double>> v = graph.get_adjacent_edges(u);
			for (size_t i = 0; i < v.size(); i++) {
				if (distance[v[i].first] > v[i].second + distance[u]) {
					distance[v[i].first] = v[i].second + distance[u];
					parent[v[i].first] = u;
					queue.push(make_pair(-distance[v[i].first], v[i].first));
				}
			}
		}
	}

	return vector<int> {};
}
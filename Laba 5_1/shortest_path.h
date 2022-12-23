#include "graph.h"

#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> build_path(std::vector<int> parent, int start_vertex, int end_vertex);

/// Return shortest path from start to end as array of vertices.
std::vector<int> shortest_path(const Graph& graph, int start_vertex, int end_vertex);
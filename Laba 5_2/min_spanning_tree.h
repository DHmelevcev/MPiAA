#pragma once

#include "graph.h"

#include <vector>
#include <algorithm>
#include <numeric>

int find_set(std::vector <int>& parents, int v);

void union_sets(std::vector <int>& parents, std::vector <int>& rank, int a, int b);

// Return minimal spanning tree for the (connected) graph as array of edges.
std::vector<std::pair<int, int>> min_spanning_tree(const Graph& graph);
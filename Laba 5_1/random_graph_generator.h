#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> shuffled_sequence(int size, int start);

int find_set_v(std::vector <int>& parent, int v);

void union_sets_v(std::vector <int>& parent, int a, int b);

std::vector<std::pair<std::pair<int, int>, double>> generate_random_graph_edges(int vertices_size, int edges_size, double max_weight);
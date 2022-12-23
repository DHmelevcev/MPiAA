#include "graph.h"

#include <vector>

/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an array of vertices and its lenght.

std::pair<std::vector<int>, double> tsp(const Graph& graph, int start_vertex);

std::pair<std::vector<int>, double> tsp_bnb(const Graph& graph, int start_vertex);

std::pair<std::vector<int>, double> tsp_greedy(const Graph& graph, int start_vertex);
#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <chrono>
#include <iomanip>

#include "tsp.h"
#include "complete_graph_generator.h"

using namespace std;

int main(int argc, char* argv[])
{

	vector<int> sizes =
	{
		10,
		11,
		12,
		13,
		14,
		15,
		16,
		17,
		18,
		19,
		20,
		100,
		1000,
		10000,
	};

	for (auto i : sizes)
	{
		Graph graph;
		vector<pair<pair<int, int>, double>> edges = generate_complete_graph_edges(i, log(i));
		for (const auto& e : edges)
			graph.add_edge(e.first.first, e.first.second, e.second);

		cout << "graph_" << i << ":";

		int start_vertex = rand() % i;

		auto t1 = std::chrono::high_resolution_clock::now();
		pair<vector<int>, double> path1 = tsp_greedy(graph, start_vertex);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time1 = std::chrono::duration<double>(t2 - t1).count();
		cout << "\ntsp_greedy: lenght: " << setw(6) << path1.second << "\ttime: " << setw(8) << time1;

		if (graph.get_vertices().size() < 18)
		{
			t1 = std::chrono::high_resolution_clock::now();
			pair<vector<int>, double> path2 = tsp_bnb(graph, start_vertex);
			t2 = std::chrono::high_resolution_clock::now();
			double time2 = std::chrono::duration<double>(t2 - t1).count();
			cout << "\ntsp_bnb:    lenght: " << setw(6) << path2.second << "\ttime: " << setw(8) << time2;
		}

		if (graph.get_vertices().size() < 12)
		{
			t1 = std::chrono::high_resolution_clock::now();
			pair<vector<int>, double> path3 = tsp(graph, start_vertex);
			t2 = std::chrono::high_resolution_clock::now();
			double time3 = std::chrono::duration<double>(t2 - t1).count();
			cout << "\ntsp:        lenght: " << setw(6) << path3.second << "\ttime: " << setw(8) << time3;
		}

		cout << "\n===============================================================================\n";
	}

	int result = Catch::Session().run(argc, argv);
	return result;
}
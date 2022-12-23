#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <chrono>
#include <iomanip>
#include <string>
#include <fstream>

#include "shortest_path.h"
#include "random_graph_generator.h"

using namespace std;

Graph read_file(ifstream& file) {
	Graph result;
	while (file) {
		int u;
		int v;
		double w;
		file >> u;
		if (!file)
			break;
		file >> v;
		if (!file)
			break;
		file >> w;
		if (file)
			result.add_edge(u, v, w);
	}
	return result;
}

int main(int argc, char* argv[]) {

	//int v = 1000000;
	//int e = 1000000;
	//ofstream ofs("graph_1000000_1000000.txt");
	//vector<pair<pair<int, int>, double>> edges = generate_random_graph_edges(v, e, log(max(v, e)));
	//for (int i = 0; i < e; i++)
	//	ofs << edges[i].first.first << ' ' << edges[i].first.second << ' ' << edges[i].second << '\n';

	vector<string> strings = {
		"graph_10_10.txt",
		"graph_10_100.txt",
		"graph_10_1000.txt",
		"graph_10_10000.txt",
		"graph_10_100000.txt",
		"graph_10_1000000.txt",
		"graph_100_100.txt",
		"graph_100_1000.txt",
		"graph_100_10000.txt",
		"graph_100_100000.txt",
		"graph_100_1000000.txt",
		"graph_1000_1000.txt",
		"graph_1000_10000.txt",
		"graph_1000_100000.txt",
		"graph_1000_1000000.txt",
		"graph_10000_10000.txt",
		"graph_10000_100000.txt",
		"graph_10000_1000000.txt",
		"graph_100000_100000.txt",
		"graph_100000_1000000.txt",
		"graph_1000000_1000000.txt",
	};

	for (auto i : strings) {
		ifstream input(i);
		Graph graph = read_file(input);
		input.close();

		cout << i << ":\n";

		vector<double> times(100);

		size_t vertices_size = graph.get_vertices().size();
		for (int i = 0; i < times.size(); i++) {
			int start_vertex = rand() % vertices_size, end_vertex = rand() % vertices_size;

			auto t1 = std::chrono::high_resolution_clock::now();
			shortest_path(graph, start_vertex, end_vertex);
			auto t2 = std::chrono::high_resolution_clock::now();
			times[i] = std::chrono::duration<double>(t2 - t1).count();
		}

		cout << "time: " << setw(8) << std::accumulate(times.begin(), times.end(), 0.000000) / times.size() << "\n===============================================================================\n";
	}

    int result = Catch::Session().run(argc, argv);
    return result;
}
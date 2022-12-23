#include "tsp.h"

using namespace std;

const int INF = numeric_limits<int>::max();

////////////////////////////////////////////////////////////////////////////////
/////��������������� �������////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<typename T>
vector<T> push(const vector<T>& first, const vector<T>& second)
{
	vector<T> result = first;
	result.insert(result.end(), second.begin(), second.end());

	return result;
}

double get_tour_lenght(const Graph& graph, const vector<int>& vertices)
{
	// Return the lenght of tour.

	double result = 0;

	for (auto it = vertices.begin(); it < vertices.end() - 1; it++)
	{
		if (graph.has_edge(*it, *(it + 1)))
			result += graph.edge_weight(*it, *(it + 1));
		else
			return INF;
	}
	if (graph.has_edge(vertices.back(), vertices.front()))
		result += graph.edge_weight(vertices.back(), vertices.front());
	else
		return INF;

	return result;
}

double get_path_lenght(const Graph& graph, const vector<int>& vertices)
{
	// Return the lenght of path.

	double result = 0;

	for (auto it = vertices.begin(); it < vertices.end() - 1; it++)
	{
		if (graph.has_edge(*it, *(it + 1)))
			result += graph.edge_weight(*it, *(it + 1));
		else
			return INF;
	}

	return result;
}

vector<int>& min_path(const Graph& graph, vector<int>& first, vector<int>& second)
{
	double result1 = get_path_lenght(graph, first);
	double result2 = get_path_lenght(graph, second);

	return result2 > result1 ? first : second;
}

vector<int>& min_tour(const Graph& graph, vector<int>& first, vector<int>& second)
{
	double result1 = get_tour_lenght(graph, first);
	double result2 = get_tour_lenght(graph, second);

	return result2 > result1 ? first : second;
}

////////////////////////////////////////////////////////////////////////////////
/////������� ������ ���������///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool nextSet(vector<int>& vertices)
{
	size_t j = vertices.size() - 2;	// find last not invertion
	while (j != -1 && vertices[j] >= vertices[j + 1]) j--;
	if (j == -1)
		return false;	// array inverted

	size_t k = vertices.size() - 1;
	while (vertices[j] >= vertices[k]) k--;
	swap(vertices[j], vertices[k]);	// make invertion with last bigger number
	
	size_t l = j + 1, r = vertices.size() - 1;
	while (l < r)
		swap(vertices[l++], vertices[r--]);	// sort right peace
	return true;
}

pair<vector<int>, double> tsp(const Graph& graph, int start_vertex)
{
	// Return the shortest (with a minimal total weight) tour as an array of vertices and its lenght.
	// Tour is assumed to start and end in the given start vertex.
	// Start vertex should be included in the result only once, as the first item.    
	// Return empty array if there is no tour.

	vector<int> vertices = graph.get_vertices();

	if (vertices.size() > 1)
	{
		vector<int> path;
		double min_lenght = INF;

		do
		{
			if (vertices.front() == start_vertex)
			{
				double len = get_tour_lenght(graph, vertices);

				if (len < min_lenght)
				{
					path = vertices;
					min_lenght = len;
				}
			}
		} while (nextSet(vertices));

		return make_pair(path, min_lenght);
	}

	return make_pair(vector<int> {}, INF);
}

////////////////////////////////////////////////////////////////////////////////
/////������� ������� ������ � ������////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool edge_in_path(vector<int>& visited, int a, int b)
{
	for (auto it = visited.begin(); it < visited.end() - 1; it++)
		if (*it == a && *(it + 1) == b || *it == b && *(it + 1) == a)
			return true;

	return false;
}

double lower_bound(const Graph& graph, vector<int>& visited)
{
	vector<int> vertices = graph.get_vertices();

	double result = 0;

	for (auto& v : vertices)
	{
		vector<pair<int, double>> edges = graph.get_adjacent_edges(v);

		int u_min;
		double min1 = INF, min2 = INF;

		for (auto& e : edges)
		{
			if (edge_in_path(visited, v, e.first))
			{
				if (e.second < min2)
					if (e.second < min1)
					{
						min2 = min1;
						min1 = e.second;
						u_min = e.first;
					}
					else
						min2 = e.second;
			}
		}

		if (min2 == INF)
		{
			if (min1 == INF)
			{
				for (auto& e : edges)
				{
					if (e.second < min2)
						if (e.second < min1)
						{
							min2 = min1;
							min1 = e.second;
						}
						else
							min2 = e.second;
				}
			}
			else
			{
				for (auto& e : edges)
				{
					if (e.second < min2 && e.first != u_min)
						min2 = e.second;
				}
			}
		}

		result += min1 + min2;
	}

	return result / 2;
}

vector<int> bnb(const Graph& graph, vector<int>& visited, vector<int>& best_path)
{
	vector<int> vertices = graph.get_vertices();

	if (visited.size() == vertices.size())
		return min_tour(graph, visited, best_path);

	double best_path_lenght = get_path_lenght(graph, best_path);

	for (auto& v : vertices)
	{
		if (find(visited.begin(), visited.end(), v) == visited.end())
		{
			vector<int> vNext = push(visited, {v});

			if (lower_bound(graph, vNext) < best_path_lenght)
			{
				vector<int> path = bnb(graph, vNext, best_path);
				best_path = min_path(graph, path, best_path);
				best_path_lenght = get_path_lenght(graph, best_path);
			}
		}
	}
	
	return best_path;
}

pair<vector<int>, double> tsp_bnb(const Graph& graph, int start_vertex)
{
	if (graph.get_vertices().size() < 2)
		return make_pair(vector<int> {}, INF);
	
	vector<int> visited = { start_vertex };
	vector<int> best_path = tsp_greedy(graph, start_vertex).first;

	if (best_path.size() < 2)
		return make_pair(vector<int> {}, INF);

	vector<int> result = bnb(graph, visited, best_path);
	double lenght = get_tour_lenght(graph, result);

	if (lenght < INF)
		return make_pair(result, lenght);

	return make_pair(vector<int> {}, INF);
}

////////////////////////////////////////////////////////////////////////////////
/////������� ������ ����������//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

pair<vector<int>, double> tsp_greedy(const Graph& graph, int start_vertex)
{
	vector<bool> visited(graph.get_vertices().size(), false);
	if (visited.size() < 2)
		return make_pair(vector<int> {}, INF);

	int current = start_vertex;

	vector<int> path = { current };

	while (true)
	{
		visited[current] = true;
		int next = -1;
		double min_weight = INF;

		for (auto& edge : graph.get_adjacent_edges(current))
		{
			if (edge.second < min_weight && !visited[edge.first])
			{
				next = edge.first;
				min_weight = edge.second;
			}
		}

		if (next == -1)
			break;

		path.push_back(next);
		current = next;
	}

	double len = get_tour_lenght(graph, path);

	if (path.size() == visited.size() && len < INF)
		return make_pair(path, len);
	else
		return make_pair(vector<int> {}, INF);
}
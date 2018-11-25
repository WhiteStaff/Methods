#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <climits>


std::vector<int>BFC(std::vector< std::map<int, int> >& Graph, int from, int to)
{
	if (from == to)
	{
		return std::vector<int>(1, to);
	}

	std::vector<int> paths_length(Graph.size());

	for (auto i = 0; i < Graph.size(); i++)
	{
		paths_length[i] = INT32_MAX;
	}
	paths_length[from] = 0;

	int edge_count = 0;
	std::vector<bool> is_done(Graph.size());
	std::vector<int> path(Graph.size());
	std::queue<int> our_queue;
	our_queue.push(from);
	
	int vertex_in_level = 1;
	bool is_destination_found = 0;
	while (is_destination_found == 0)
	{
		for (int i = 0; i < vertex_in_level; i++)
		{
			int now = our_queue.front();
			our_queue.pop();
			for (auto next : Graph[now])
			{
				if (paths_length[now] + next.second < paths_length[next.first])
				{
					paths_length[next.first] = paths_length[now] + next.second;
					path[next.first] = now;
				}
				if (next.first == to)
				{
					is_destination_found = 1;
				}
				else if (is_done[next.first] == 0)
				{
					our_queue.push(next.first);
				}
			}
		}
		vertex_in_level = our_queue.size();
		edge_count++;
	}
	int now = to;
	std::vector<int> route(edge_count + 1);
	for (int i = edge_count; i >= 0; i--)
	{
		route[i] = now;
		now = path[now];
	}
	return route;
}


int main()
{
	std::vector< std::map<int, int> > Graph;
	int n, m;
	std::cin >> n >> m;
	Graph.resize(n);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		Graph[a - 1][b - 1] = c;
	}
	std::vector<int> answer = BFC(Graph, 0, 9 );
	std::cout << "min route:";
	for (auto i : answer)
	{
		std::cout << i + 1 << " ";
	}
	std::cin >> n;
	return 0;
}
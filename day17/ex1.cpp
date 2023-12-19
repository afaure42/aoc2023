#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <deque>
#include <queue>

enum dir
{
	RIGHT,
	UP,
	LEFT,
	DOWN
};

struct node;

typedef std::pair<dir, node *> neighbour;

struct node
{
	node() : neighbours(std::vector<neighbour>()), cost(0) {};
	node(int cost, std::stirng name) : neighbours(std::vector<neighbour>()), cost(cost) {}

	int cost = 0;
	std::string name;
	std::vector<neighbour> neighbours;
};

size_t dijkstra(const std::vector<node *> nodes, const node * start, const node * end)
{
	std::map<const node *, size_t> dist;
	std::map<const node *, std::pair<dir, int>> prev;
	std::map<const node *, const node *> path;
	std::priority_queue<std::pair<size_t, const node *>> pq;

	for (auto & n : nodes)
		dist[n] = 1000000000000000000;
	dist[start] = 0;
	pq.push(std::make_pair(0, start));
	while (!pq.empty())
	{
		auto top = pq.top();
		pq.pop();
		for( auto & n : top.second->neighbours)
		{
			if (n.first % 2 == prev[top.second].first
				&& n.first != prev[top.second].first) // if we are going back
				continue;
			if (prev[top.second].second == 3 && n.first == prev[top.second].first)
				continue; //cant go 3 times in the same direction

			size_t alt = dist[top.second] + n.second->cost;
			if (alt < dist[n.second])
			{
				dist[n.second] = alt;
				if (n.first == prev[top.second].first)
					prev[n.second] = std::make_pair(n.first, prev[top.second].second + 1);
				else
					prev[n.second] = std::make_pair(n.first, 1);
				path[n.second] = top.second;
				pq.push(std::make_pair(alt, n.second));
			}
		}
	}

	return dist[end];
}	

int main(int argc, char *argv[])
{
	std::ifstream in_file;
	if (argc != 2)
	{
		std::cout << "Dude you coded that shit 5 min ago\n";
		exit(EXIT_FAILURE);
	}

	std::string file_name(argv[1]);
	in_file.open(file_name, std::ios_base::in);

	if (in_file.fail())
	{
		std::cout << "Wrong file, try remembering what you did 5 min ago\n";
		exit(EXIT_FAILURE);
	}

	std::string line;
	std::vector<std::string> lines;
	std::vector<node *> nodes;
	while(std::getline(in_file, line, '\n'))
		lines.push_back(line);
	
	for(auto & str : lines)
	{
		for (auto & c : str)
			nodes.push_back(new node(c - '0'));
	}
	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
		{
			node * l, * r, * u, * d;
			l = r = u = d = nullptr;
			node * current = nodes[i * lines[i].length() + j];

			if (i > 0)
				current->neighbours.push_back(std::make_pair(UP, nodes[lines[i].length() * (i - 1) + j]));	
			if (i < lines.size() - 1)
				current->neighbours.push_back(std::make_pair(DOWN, nodes[lines[i].length() * (i + 1) + j]));
			if (j > 0)
				current->neighbours.push_back(std::make_pair(LEFT, nodes[lines[i].length() * i + (j - 1)]));
			if (j < lines[i].length() - 1)
				current->neighbours.push_back(std::make_pair(RIGHT, nodes[lines[i].length() * i + (j + 1)]));
		}
	}

	std::cout << dijkstra(nodes, nodes[0], nodes[nodes.size() - 1]) << std::endl;
}

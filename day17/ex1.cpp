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
	UNKOWN,
	RIGHT,
	UP,
	LEFT,
	DOWN,
};

struct node;

typedef std::pair<dir, node *> neighbour;

struct node
{
	node() : neighbours(std::vector<neighbour>()), cost(0) {};
	node(int cost, std::pair<int, int> pos) : neighbours(std::vector<neighbour>()), cost(cost), pos(pos) {}

	std::ostream & operator<<(std::ostream & os)
	{
		os << "Node at " << pos.first << ", " << pos.second << " with cost " << cost << std::endl;
		return os;
	};
	int cost = 0;
	std::pair<int, int> pos;
	std::vector<neighbour> neighbours;
};

std::pair<size_t, std::vector<std::pair<dir, const node *>>> dijkstra(const std::vector<node *> nodes, const node * start, const node * end)
{
	std::map<const node *, size_t> dist;
	std::map<const node *, std::pair<dir, int>> prev;
	std::map<const node *, const node *> path;
	std::set<const node *> visited;
	std::priority_queue<std::pair<size_t, const node *>> pq;

	for (auto & n : nodes)
		dist[n] = 1000000000000000000;
	dist[start] = 0;
	pq.push(std::make_pair(0, start));
	while (!pq.empty())
	{
		auto top = pq.top();
		pq.pop();
		if (!prev.contains(top.second))
			std::cout << "prev doesnt contain " << top.second << std::endl;
		for( auto & n : top.second->neighbours)
		{
			if (n.first != UNKOWN)
			{
				if (n.first == LEFT && prev[top.second].first == RIGHT
					|| n.first == RIGHT && prev[top.second].first == LEFT
					|| n.first == UP && prev[top.second].first == DOWN
					|| n.first == DOWN && prev[top.second].first == UP)
					continue;
				if (prev[top.second].second == 3 && n.first == prev[top.second].first)
				{
					continue; //cant go 3 times in the same direction
				}
			}
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
	std::vector<std::pair<dir, const node *>> ret;

	auto current = end;
	while(current != nullptr)
	{
		std::cout << "prev: " << prev[current].first << ", " << prev[current].second << std::endl;
		ret.push_back(std::make_pair(prev[current].first, current));
		current = path[current];
	}
	return std::make_pair(dist[end], ret);
}	

std::vector<const node *> bfs_bis(const std::vector<node *> nodes, const node * start, const node * end)
{
	std::set<const node *> unvisited;
	std::map<const node *, size_t> dist;
	std::map<const node *, std::tuple<const node *, dir, size_t>> prev; //previous node, direction and number of times we had the same dir
	std::priority_queue<std::pair<size_t, const node *>> pq;

	for (auto & n : nodes)
	{
		unvisited.insert(n);
		dist[n] = 100000000000;
	}
	dist[start] = 0;
	pq.push(std::make_pair(0, start));

	while(!pq.empty())
	{
		auto current = pq.top().second;
		pq.pop();
		if (!unvisited.contains(end))
			break;
		if (!unvisited.contains(current))
			continue;
		unvisited.erase(current);
		for (auto & n : current->neighbours)
		{
			if (n.first % 2 == std::get<1>(prev[current]) % 2
				&& n.first != std::get<1>(prev[current])) // if we are going back
				continue;
			if (std::get<2>(prev[current]) == 3 && n.first == std::get<1>(prev[current]))
				continue; //cant go 3 times in the same direction
			if (!unvisited.contains(n.second))
				continue;
			
			size_t distance = dist[current] + n.second->cost;
			if (distance < dist[n.second])
			{
				dist[n.second] = distance;
				if (n.first == std::get<1>(prev[current]))
					prev[n.second] = std::make_tuple(current, n.first, std::get<2>(prev[current]) + 1);
				else
					prev[n.second] = std::make_tuple(current, n.first, 1);
				pq.push(std::make_pair(dist[n.second], n.second));
			}
		}
	}

	std::vector<const node *> path;

	auto current = end;
	while(current != nullptr)
	{
		path.push_back(current);
		current = std::get<0>(prev[current]);
	}

	return path;
}


std::pair<size_t, std::vector<std::pair<dir, const node *>>> dijkstra_tris(const std::vector<node *> & nodes, const node * start, const node * end)
{
	std::set<std::tuple<const node *, dir, size_t>> visited;
	std::map<const node *, size_t> dist;
	std::map<const node *, std::pair<dir, const node *>> path;
	std::priority_queue<std::tuple<size_t, const node *, dir, size_t>> to_visit; //distance, node, direction, repetition

	for(auto & n : nodes)
		dist[n] = 100000000000;
	dist[start] = 0;
	to_visit.push(std::make_tuple(0, start, UNKOWN, 0));

	while(!to_visit.empty())
	{
		auto top = to_visit.top();
		auto current = std::get<1>(top);
		auto prev_dir = std::get<2>(top);
		auto repetition = std::get<3>(top);
		to_visit.pop();
		// if (visited.contains(std::make_tuple(current, prev_dir, repetition)))
		// 	continue;
		// visited.insert(std::make_tuple(current, prev_dir, repetition));
		// if (repetition == 4)
			// continue;
		for (auto & current_neighbour : current->neighbours)
		{
			if (repetition == 3 && current_neighbour.first == prev_dir)
				continue;
			size_t alt = dist[current] + current_neighbour.second->cost;
			if (alt < dist[current_neighbour.second])
			{
				dist[current_neighbour.second] = alt;
				if (current_neighbour.first == prev_dir)
					to_visit.push(std::make_tuple(alt, current_neighbour.second, current_neighbour.first, repetition + 1));
				else
					to_visit.push(std::make_tuple(alt, current_neighbour.second, current_neighbour.first, 1));
				path[current_neighbour.second] = std::make_pair(current_neighbour.first, current);
			}
		}
	}

	std::cout << dist[end] << std::endl;
	std::vector<std::pair<dir, const node *>> ret;

	auto current = end;
	while(current != nullptr)
	{
		ret.push_back(std::make_pair(path[current].first, current));
		current = path[current].second;
	}
	return std::make_pair(dist[end], ret);	
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
	
	for(size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].length(); j++)
			nodes.push_back(new node(lines[i][j] - '0', std::make_pair(i, j)));
	}
	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
		{
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

	auto path = dijkstra_tris(nodes, nodes[0], nodes[nodes.size() - 1]);
	size_t total = 0;
	for(auto & n : path.second)
	{
		char c;
		switch(n.first)
		{
			case UP:
				c = '^';
				break;
			case DOWN:
				c = 'v';
				break;
			case LEFT:
				c = '<';
				break;
			case RIGHT:
				c = '>';
				break;
		}
		lines[n.second->pos.first][n.second->pos.second] = c;
		total += n.second->cost;
	}
	for(auto & l : lines)
		std::cout << l << std::endl;
	std::cout << path.first << " " << total << std::endl;
}

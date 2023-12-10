#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

struct node
{
	char name;
	std::vector<node *> neighbours;
};

bool dir_v(std::pair<int, int> dir, std::pair<int, int> current, std::vector<std::string> & lines)
{
	current.first += dir.first * 2;
	current.second += dir.second * 2;
	return (lines[current.first][current.second] == 'V');
}

void fill_v(std::pair<int, int> dir, std::pair<int, int> current, std::vector<std::string> & lines)
{
	current.first += dir.first;
	current.second += dir.second;
	while(lines[current.first][current.second] == 'a')
	{
		std::cout << "FILLING " << current.first << " " << current.second << std::endl;
		lines[current.first][current.second] = 'V';
		current.first += dir.first;
		current.second += dir.second;
	}
}

void create_graph(std::vector<std::string> &lines, int y, int x, node * start, std::map<std::pair<int, int>, node *> nodes)
{
	std::set<std::pair<int, int>> visited;
	std::vector<std::pair<int, int>> to_visit;

	to_visit.push_back(std::make_pair(y, x));
	while(!to_visit.empty())
	{
		std::pair<int, int> current = to_visit.front();
		to_visit.erase(to_visit.begin());
		std::pair<int, int> next = current;
		if (lines[current.first][current.second] == 'V')
			continue;
		// std::cout << "VISITING " << current.first << " " << current.second << " " << lines[current.first][current.second] << std::endl;
		switch(lines[current.first][current.second])
		{
			case 'S':
			{
				lines[current.first][current.second] = 'V';

				to_visit.push_back(std::make_pair(current.first + 2, current.second));
				to_visit.push_back(std::make_pair(current.first, current.second + 2));
				to_visit.push_back(std::make_pair(current.first, current.second - 2));
				to_visit.push_back(std::make_pair(current.first - 2, current.second));
				break;
			}
			case '|':
			{
				if (dir_v({1, 0}, current, lines))
				{
					lines[current.first][current.second] = 'V';
					fill_v({1, 0}, current, lines);
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					nodes[{current.first + 2, current.second}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first + 2, current.second}]);
					to_visit.push_back(std::make_pair(current.first - 2, current.second));
				}

				if (dir_v({-1 , 0}, current, lines))
				{
					fill_v({-1, 0}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					nodes[{current.first - 2, current.second}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first - 2, current.second}]);
					to_visit.push_back(std::make_pair(current.first + 2, current.second));
				}
				break;
			}
			case '-':
			{

				if (dir_v({0, 1}, current, lines))
				{
					fill_v({0, 1}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					nodes[{current.first, current.second + 2}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first, current.second + 2}]);
					to_visit.push_back(std::make_pair(current.first, current.second - 2));
				}
				
				if (dir_v({0, -1}, current, lines))
				{
					fill_v({0, -1}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					nodes[{current.first, current.second - 2}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first, current.second - 2}]);
					to_visit.push_back(std::make_pair(current.first, current.second + 2));
				}

				break;
			}
			case 'L':
			{
				if (dir_v({-1, 0}, current, lines))
				{
					fill_v({-1, 0}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					nodes[{current.first - 2, current.second}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first - 2, current.second}]);
					to_visit.push_back(std::make_pair(current.first, current.second + 2));
				}

				if (dir_v({0, 1}, current, lines))
				{
					fill_v({0, 1}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					to_visit.push_back(std::make_pair(current.first - 2, current.second));
					nodes[{current.first, current.second + 2}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first, current.second + 2}]);
				}
				break;
			}
			case 'J':
			{
				if (dir_v({-1, 0}, current, lines))
				{
					fill_v({-1, 0}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));


					nodes[{current.first - 2, current.second}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first - 2, current.second}]);
					to_visit.push_back(std::make_pair(current.first, current.second - 2));

				}
				if(dir_v({0, -1}, current, lines))
				{
					fill_v({0, -1}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					nodes[{current.first, current.second - 2}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first, current.second - 2}]);
					to_visit.push_back(std::make_pair(current.first - 2, current.second));
				}
				break;
			}
			case '7':
			{
				if (dir_v({1, 0}, current, lines))
				{
					fill_v({1, 0}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					to_visit.push_back(std::make_pair(current.first, current.second - 2));
					nodes[{current.first + 2, current.second}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first + 2, current.second}]);
				}

				if(dir_v({0, -1}, current, lines))
				{
					fill_v({0, -1}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					to_visit.push_back(std::make_pair(current.first + 2, current.second));
					nodes[{current.first, current.second - 2}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first, current.second - 2}]);
				}
				break;
			}
			case 'F':
			{
				if(dir_v({1, 0}, current, lines))
				{
					fill_v({1, 0}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					to_visit.push_back(std::make_pair(current.first, current.second + 2));
					nodes[{current.first + 2, current.second}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first + 2, current.second}]);
				}

				if(dir_v({0, 1}, current, lines))
				{
					fill_v({0, 1}, current, lines);
					lines[current.first][current.second] = 'V';
					nodes.insert(std::make_pair(std::make_pair(current.first, current.second), new node()));

					to_visit.push_back(std::make_pair(current.first + 2, current.second));
					nodes[{current.first, current.second + 2}]->neighbours.push_back(nodes[current]);
					nodes[current]->neighbours.push_back(nodes[{current.first, current.second + 2}]);
				}

				break;
			}
			default:
				break;
		}
	}
}

int visit_graph(node * start)
{
	std::map<node *, std::pair<node *, int>> visited;
	visited.insert(std::make_pair(start, std::make_pair(nullptr, 0)));

	std::vector<node *> to_visit;
	to_visit.push_back(start);

	while (!to_visit.empty())
	{
		node * current = to_visit.front();
		to_visit.erase(to_visit.begin());

		for (size_t i = 0; i < current->neighbours.size(); i++)
		{
			if (visited.find(current->neighbours[i]) != visited.end())
				continue;
			to_visit.push_back(current->neighbours[i]);
			visited.insert(std::make_pair(current->neighbours[i], std::make_pair(current, visited[current].second + 1)));
		}
	}

	int biggest = 0;
	for (auto & iter : visited)
	{
		if (iter.second.second > biggest)
			biggest = iter.second.second;
	}

	return biggest;
}

bool found_0(std::map<std::pair<int, int>, node *> & nodes, node * start)
{
	std::set<node *> visited;

	std::vector<node *> to_visit;
	to_visit.push_back(start);
	visited.insert(start);

	while(!to_visit.empty())
	{
		node * current = to_visit.front();
		to_visit.erase(to_visit.begin());

		if (current->name == '0')
			return true;
		
		for(size_t i = 0; i < current->neighbours.size(); i++)
		{
			if (visited.find(current->neighbours[i]) != visited.end() || current->neighbours[i]->name == 'V')
				continue;
			to_visit.push_back(current->neighbours[i]);
			visited.insert(current->neighbours[i]);
		}
	}
	return false;
}

int inside_loop(std::vector<std::string> &lines)
{
	std::map<std::pair<int, int>, node *> nodes;

	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
			nodes.insert(std::make_pair(std::make_pair(i, j), new node()));
	}

	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
			nodes[{i, j}]->name = lines[i][j];
	}

	for(size_t i = 1; i + 1 < lines.size(); i++)
	{
		for(size_t j = 1; j + 1 < lines[i].length(); j++)
		{
			nodes[{i, j}]->neighbours.push_back(nodes[{i + 1, j}]);
			nodes[{i, j}]->neighbours.push_back(nodes[{i - 1, j}]);
			nodes[{i, j}]->neighbours.push_back(nodes[{i, j - 1}]);
			nodes[{i, j}]->neighbours.push_back(nodes[{i, j + 1}]);
		}
	}

	int total = 0;
	for(auto & iter : nodes)
	{
		std::cout << "iterating on node :" << iter.second->name << std::endl;
		if (iter.second == nullptr)
		{
			std::cout << iter.first.first << " " << iter.first.second << std::endl;
			std::cout << "ERROR\n";
		}
		if (iter.second->name != 'V' && iter.second->name != 'a' && iter.second->name != '0' && !found_0(nodes, iter.second))
		{
			lines[iter.first.first][iter.first.second] = 'O';
			total++;
		}
	}
	return total;
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
	while(std::getline(in_file, line, '\n'))
		lines.push_back(line);
	
	node * start = new node();
	std::map<std::pair<int, int>, node *> nodes;

	for( auto & iter : lines)
	{
		for (size_t i = 0; i < iter.size(); i++)
		{
			if (iter[i] != 'a')
				iter.insert(iter.begin() + i + 1, 'a');
		}
	}

	for(size_t i = 0; i < lines.size(); i+= 2)
	{
		lines.insert(lines.begin() + i, std::string(lines[0].length(), 'a'));
	}


	for(auto & iter : lines)
		std::cout << iter << std::endl;

	lines.push_back(std::string(lines[0].length(), '0'));
	lines.insert(lines.begin(), std::string(lines[0].length(), '0'));
	for(size_t i = 0; i < lines.size(); i++)
	{
		lines[i].push_back('0');
		lines[i].insert(lines[i].begin(), '0');
	}
	
	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
		{
			if (lines[i][j] == 'S')
			{
				nodes.insert(std::make_pair(std::make_pair(i, j), start));
				create_graph(lines, i, j, start, nodes);
			}
		}
	}
	int test = visit_graph(start);
	std::cout << "OUTSIDE" << std::endl;
	std::cout << "ENCLOSED :" << inside_loop(lines) << std::endl;

	// for(size_t i = 0; i < lines.size(); i++)
	// {
	// 	for(size_t j = 0; j < lines[i].length(); j++)
	// 	{
	// 		if (lines[i][j] != 'O' && lines[i][j] != '0' && lines[i][j] != 'V')
	// 			lines[i][j] = ' ';
	// 		else if (lines[i][j] != 'O')
	// 			lines[i][j] = '_';
	// 	}
	// }
	for(auto & iter : lines)
		std::cout << iter << std::endl;
	std::cout << test << std::endl;
}

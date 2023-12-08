#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <numeric>

struct node 
{
	std::string name;

	std::string left_name;
	node * left_node;
	std::string right_name;
	node * right_node;
};

bool valid_vect(const std::vector<node *> & vect)
{
	for (auto & it : vect)
	{
		if (it->name.back() != 'Z')
			return false;
	}
	return true;
}

void choose_left(std::vector<node *> & vect)
{
	for (auto & it : vect)
	{
		it = it->left_node;
	}
}

void choose_right(std::vector<node *> & vect)
{
	for (auto & it : vect)
	{
		it = it->right_node;
	}
}

void map_tree(std::unordered_map<std::string, node> & nodes)
{
	for (auto & it : nodes)
	{
		it.second.left_node = &nodes[it.second.left_name];
		it.second.right_node = &nodes[it.second.right_name];
	}
}

unsigned long new_lcm(std::vector<unsigned long long> numbers)
{
	unsigned long long ret = numbers[0];
	for(size_t i = 1; i < numbers.size(); i++)
	{
		ret = std::lcm(ret, numbers[i]);
	}
	return ret;
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
	std::string instructions;
	bool first_line = true;
	std::unordered_map<std::string, node> nodes;
	std::vector<node *> starting_nodes;
	while(std::getline(in_file, line, '\n'))
	{
		if (line.length() == 0) continue;
		if (first_line)
		{
			instructions = line;
			first_line = false;
			continue;
		}
		nodes[line.substr(0, 3)].name = line.substr(0, 3);
		nodes[line.substr(0, 3)].left_name = line.substr(7, 3);
		nodes[line.substr(0, 3)].right_name = line.substr(12, 3);
		if (line[2] == 'A')
			starting_nodes.push_back(&nodes[line.substr(0, 3)]);
	}

	map_tree(nodes);
	std::vector<unsigned long long> z_indexes;
	for(auto & it : starting_nodes)
	{
		bool finished = false;
		unsigned long long count = 0;
		node * current = it;
		while (!finished)
		{
			for (size_t i = 0; i < instructions.length(); i++)
			{
				if (current->name.back() == 'Z')
				{
					z_indexes.push_back(count);
					std::cout << count << std::endl;
					finished = true;
					break;
				}

				if (instructions[i] == 'L')
					current = current->left_node;
				else if (instructions[i] == 'R')
					current = current->right_node;
				count++;
			}
		}
	}	


	std::cout << "Total: " << new_lcm(z_indexes) << std::endl;
}

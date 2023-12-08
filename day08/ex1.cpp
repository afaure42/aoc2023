#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

struct node 
{
	std::string name;

	std::string left_name;
	std::string right_name;
};

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
	std::map<std::string, node> nodes;
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
	}

	unsigned long total = 0;
	bool finished = false;
	auto iter = nodes.find("AAA");
	while (!finished)
	{
		for(size_t i = 0; i < instructions.length(); i++)
		{
			if (iter->first == "ZZZ")
			{
				std::cout << "FINISHEEEED" << std::endl;
				finished = true;
				break;
			}

			if (instructions[i] == 'L')
				iter = nodes.find(iter->second.left_name);
			else if (instructions[i] == 'R')
				iter = nodes.find(iter->second.right_name);
			total++;
		}
	}
	std::cout << "Total: " << total << std::endl;
}

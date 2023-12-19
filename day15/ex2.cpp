#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <deque>


    // Determine the ASCII code for the current character of the string.
    // Increase the current value by the ASCII code you just determined.
    // Set the current value to itself multiplied by 17.
    // Set the current value to the remainder of dividing itself by 256.
unsigned long long hash(const std::string &str)
{
	unsigned long long value = 0;
	for (auto & c : str)
	{
		value += c;
		value *= 17;
		value %= 256;
	}
	return value;
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
	std::list<std::pair<std::string, size_t>> my_map[256];
	while(std::getline(in_file, line, '\n'))
	{
		while(!line.empty())
		{
			size_t end = line.find(',');
			std::string current = line.substr(0, end);
			size_t label_end = current.find('-');
			if (label_end == std::string::npos)
				label_end = current.find('=');
			std::string label = current.substr(0, label_end);

			size_t hashed = hash(label);

			if (current[label_end] == '-')
			{
				for(auto it = my_map[hashed].begin(); it != my_map[hashed].end(); it++)
				{
					if (it->first == label)
					{
						my_map[hashed].erase(it);
						break;
					}
				}
			}
			else if (current[label_end] == '=')
			{
				auto it = my_map[hashed].begin();
				while(it != my_map[hashed].end())
				{
					if (it->first == label)
					{
						it->second = current[label_end + 1] - '0';
						break;
					}
					it++;
				}
				if (it == my_map[hashed].end())
					my_map[hashed].push_back(std::make_pair(label, current[label_end + 1] - '0'));
			}

			if (end != std::string::npos)
				line.erase(0, end + 1);
			else
				line.clear();
			std::cout << current << std::endl;
			for(int i = 0; i < 256; i++)
			{
				if (my_map[i].size() == 0)
					continue;
				std::cout << "Box " << i << ": ";
				for (auto & it : my_map[i])
					std::cout << '[' << it.first << " " << it.second << "] ";
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	unsigned long long total = 0;
	for(int i = 0; i < 256; i++)
	{
		if (my_map[i].size() == 0)
			continue;
		std::cout << "Box " << i << ": ";
		for (auto & it : my_map[i])
			std::cout << '[' << it.first << " " << it.second << "] ";
		std::cout << std::endl;
	}
	for(size_t i = 0; i < 256; i++)
	{
		size_t j = 1;
		for(auto & it : my_map[i])
		{
			total += it.second * j * (i + 1);
			j++;
		}
	}
	std::cout << total << std::endl;
}

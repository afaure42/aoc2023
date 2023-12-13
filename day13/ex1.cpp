#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include "cache.hpp"

cache winning_cache;

bool vertical_comp(std::vector<std::string> & lines, int a, int b)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i][a] != lines[i][b])
			return false;
	}
	return true;
}

bool cached_compare(std::vector<std::string> & lines, int a, int b, bool horizontal)
{
	if (horizontal)
	{
		// auto ret = winning_cache.get(std::make_tuple(lines[a], lines[b]));
		// if (ret.first)
		// 	return ret.second;
		// else
		// {
		// 	bool result = lines[a] == lines[b];
		// 	winning_cache.add_to_cache(std::make_tuple(lines[a], lines[b]), result);
		// 	return result;
		// }
		return lines[a] == lines[b];
	}
	else
	{
		std::string str_a;
		std::string str_b;
		for(size_t i = 0; i < lines.size(); i++)
		{
			str_a.push_back(lines[i][a]);
			str_b.push_back(lines[i][b]);
		}
		// auto ret = winning_cache.get(std::make_tuple(str_a, str_b));
		// if (ret.first)
		// 	return ret.second;
		// else
		// {
		// 	bool result = str_a == str_b;
		// 	winning_cache.add_to_cache(std::make_tuple(str_a, str_b), result);
		// 	return result;
		// }
		return str_a == str_b;
	}
}

bool valid_reflection(std::vector<std::string> & lines, bool vertical, int index)
{
	if (!vertical)
	{
		int i = index + 1;
		while (i < lines.size() && index >= 0)
		{
			if (cached_compare(lines, i, index, true) == false)
				return false;
			i++;
			index--;
		}
	}
	else
	{
		int i = index + 1;
		while(i < lines[0].length() && index >= 0)
		{
			if (cached_compare(lines, i, index, false) == false)
				return false;
			i++;
			index--;
		}
	}
	return true;
}

unsigned long long solve_reflections(std::vector<std::string> & lines, unsigned long long base = 0)
{
	//horizontal checks
	unsigned long long ret = 0;
	for(size_t i = 0; i + 1 < lines.size(); i++)
	{
		if (cached_compare(lines, i, i + 1, true) && valid_reflection(lines, false, i))
		{
			// std::cout << "horizontal reflection at " << i << std::endl;

			ret = (i + 1) * 100;
			if (ret == base)
				continue;
			return ret;
		}
	}

	//vertical checks
	for(size_t i = 0; i + 1 < lines[0].length(); i++)
	{
		if (cached_compare(lines, i, i + 1, false) && valid_reflection(lines, true, i))
		{
			// std::cout << "vertical reflection at " << i << std::endl;
			ret = i + 1;
			if (ret == base)
				continue;
			return ret;
		}
	}
	return 0;
}

unsigned long long wrapper_solve_reflections(std::vector<std::string> & lines)
{
	unsigned long long base = solve_reflections(lines);
	std::cout << "base: " << base << std::endl;
	unsigned long long nbr = 0;
	for(size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].length(); j++)
		{
			lines[i][j] = lines[i][j] == '.' ? '#' : '.';
			nbr = solve_reflections(lines, base);
			if (nbr != 0 && nbr != base)
			{
				for(auto & str : lines)
					std::cout << str << std::endl;
				break;
			}
			lines[i][j] = lines[i][j] == '.' ? '#' : '.';
		}
		if (nbr != 0)
			break;
	}
	if (nbr == 0 || nbr == base)
		std::cout << "ERROR NO SMUDGE FOUND" << std::endl;
	return nbr;
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
	unsigned long long total = 0;
	while(std::getline(in_file, line, '\n'))
	{
		// std::cout << "input :" << line << std::endl;
		winning_cache.clear();
		if (line.empty())
		{
			//do some logic
			total += wrapper_solve_reflections(lines);
			lines.clear();
		}
		else
			lines.push_back(line);
	}
	total += wrapper_solve_reflections(lines);

	std::cout << total << std::endl;
}

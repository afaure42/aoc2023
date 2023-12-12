#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <mutex>
#include <thread>
#include <future>
#include <deque>
#include <list>

#include "cache.hpp"

std::mutex cache_mutex;

struct cache winning_cache;


unsigned long long cached_try_solve_4(std::string str, std::vector<int> & groups, int current, int index)
{
	cache_mutex.lock();
	auto cached = winning_cache.get(std::make_tuple(str, groups, current, index));
	cache_mutex.unlock();
	if (cached.first)
		return cached.second;
	else
	{
		unsigned long long total = try_solve_4(str, groups, current, index);
		cache_mutex.lock();
		winning_cache.add_to_cache(std::make_tuple(str, groups, current, index), total);
		cache_mutex.unlock();
		return total;
	}
}

//proxy only here because you cant have a ref in a call to std::async
unsigned long long proxy_try_solve_4(std::string str, std::vector<int> groups, int current, int index)
{
	return cached_try_solve_4(str, groups, current, index);
}
unsigned long long try_solve_4(std::string str, std::vector<int> & groups, int current, int index)
{
	if (str.empty())
	{
		if (index == groups.size())
			return 1;
		return 0;
	}
	unsigned long long total = 0;
	if (str[0] == '#')
	{
		size_t temp_index = str.find_first_not_of('#');
		if (temp_index == std::string::npos)
			temp_index = str.length();
		
		total = cached_try_solve_4(str.substr(temp_index), groups, current + temp_index, index);
	}
	else if (str[0] == '.')
	{
		size_t temp_index = str.find_first_not_of('.');

		if (temp_index == std::string::npos)
			temp_index = str.length();
		if (current != 0)
		{
			if (groups[index] != current)
			{
				return 0;
			}
			index++;
		}
		total = cached_try_solve_4(str.substr(temp_index), groups, 0, index);
	}
	else if (str[0] == '?')
	{
		str[0] = '#';
		total += cached_try_solve_4(str, groups, current, index);
		str[0] = '.';
		total += cached_try_solve_4(str, groups, current, index);
	}
	return total;
}

void fill_vect(std::vector<int> & vect, std::string str)
{
	size_t index = 0;
	while (!str.empty())
	{
		int num = std::stoi(str, &index);
		vect.push_back(num);
		str.erase(0, index + 1);
	}
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
	unsigned long long total = 0;
	int line_nbr = 0;
	std::vector<std::future<unsigned long long>> promises;
	while(std::getline(in_file, line, '\n'))
	{
		//Input parsing
		std::vector<int> groups;
		fill_vect(groups, line.substr(line.find(' ')));
		line = line.substr(0, line.find(' '));

		if (line[0] == '.') //discard every dot in the front
			line = line.substr(line.find_first_not_of('.'));
		line.push_back('.'); //easier to detect eol to add a dot at the end

		total += cached_try_solve_4(line, groups, 0, 0);
		std::cout << "Line " << line_nbr++ << std::endl;
	}
	std::cout << total << std::endl;
	std::cout << "Cache hits: " << winning_cache.hits << std::endl;
	std::cout << "Cache misses: " << winning_cache.misses << std::endl;
}

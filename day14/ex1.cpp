#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#include "cache.hpp"
#include "grid.hpp"

enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

int grid::width;
int grid::height;

cache winning_cache;

void slide_all(grid & lines, char c, e_direction dir);
void push_north(grid & lines, char c)
{
	for(long j = 0; j <= grid::width; j++)
	{
		long count = 0;
		for(long i = grid::height - 1; i >= -1; i--)
		{
			if (i >= 0 && lines.array[i][j] == c)
			{
				lines.array[i][j] = '.';
				count++;
			}
			if (i == -1 || lines.array[i][j] == '#')
			{
				while(count)
				{
					lines.array[i + count][j] = c;
					count--;
				}
			}
		}
	}
}

void push_south(grid & lines, char c)
{
	for(long j = 0; j <= grid::width; j++)
	{
		long count = 0;
		for(long i = 0; i <= grid::height; i++)
		{
			if (i < grid::height && lines.array[i][j] == c)
			{
				lines.array[i][j] = '.';
				count++;
			}
			if (i >= grid::height || lines.array[i][j] == '#')
			{
				while(count)
				{
					lines.array[i - count ][j] = c;
					count--;
				}
			}
		}
	}
}

void push_east(grid & lines, char c)
{
	for(long i = 0; i < grid::height; i++)
	{
		long count = 0;
		for(long j = 0; j <= grid::width; j++)
		{
			if (lines.array[i][j] == c)
			{
				lines.array[i][j] = '.';
				count++;
			}
			if (lines.array[i][j] == '#' || lines.array[i][j] == '\0')
			{
				while(count)
				{
					lines.array[i][j - count] = c;
					count--;
				}
			}
		}
	}
}

void push_west(grid & lines, char c)
{

	for(long i = 0; i < grid::height; i++)
	{
		long count = 0;
		for(long j = grid::width - 1; j >= -1; j--)
		{
			if (j >= 0 && lines.array[i][j] == c)
			{
				lines.array[i][j] = '.';
				count++;
			}
			if (j == -1 || lines.array[i][j] == '#')
			{
				while(count)
				{
					lines.array[i][j + count] = c;
					count--;
				}
			}
		}
	}
}

// void cached_slide_all(std::vector<std::string> & lines, char c, e_direction dir)
// {
// 	auto ret = winning_cache.get(std::make_pair(lines, dir));
// 	if (ret.first)
// 		lines = std::move(ret.second);
// 	else
// 	{
// 		std::vector<std::string> temp = lines;
// 		slide_all(lines, c, dir);
// 		winning_cache.add_to_cache(std::make_pair(temp, dir), lines);
// 	}
// }

void cached_cycle(grid & lines)
{
	auto ret = winning_cache.get(lines);
	if (ret.first)
		lines = ret.second;
	else
	{
		grid temp(lines);
		slide_all(lines, 'O', NORTH);
		slide_all(lines, 'O', WEST);
		slide_all(lines, 'O', SOUTH);
		slide_all(lines, 'O', EAST);
		winning_cache.add_to_cache(temp, lines);
	}
}

void slide_all(grid & lines, char c, e_direction dir)
{
	switch (dir)
	{
		case NORTH:
		{
			push_north(lines, c);
			break;
		}
		case SOUTH:
		{
			push_south(lines, c);
			break;
		}
		case EAST:
		{
			push_east(lines, c);
			break;
		}
		case WEST:
		{
			push_west(lines, c);
			break;
		}
	}
}

unsigned long north_load(grid & lines, char c)
{
	unsigned long long count = 0;
	for(size_t i = 0; i < grid::height; i++)
	{
		for(size_t j = 0; j < grid::width; j++)
		{
			if (lines.array[i][j] == c)
				count += grid::height - i;
		}
	}
	return count;
}

unsigned long long count_load(grid & lines, char c, e_direction dir)
{
	switch (dir)
	{
		case NORTH:
		{
			return north_load(lines, c);
		}
		default:
		{
			return 0;
		}
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
	std::vector<std::string> lines;
	std::unordered_map<grid, size_t> grids_map;
	std::unordered_map<size_t, grid> index_to_grid_map;
	while(std::getline(in_file, line, '\n'))
		lines.push_back(line);

	grid my_grid(lines);
	size_t cycle_start = 0;
	size_t cycle_length = 0;
	for(size_t i =0; i < 1000000000; i++)
	{
		if(grids_map.contains(my_grid))
		{
			cycle_start = grids_map[my_grid];
			cycle_length = i - cycle_start;
			break;
		}
		grids_map[my_grid] = i;
		index_to_grid_map[i] = my_grid;
		cached_cycle(my_grid);
		std::cout << "load : " << count_load(my_grid, 'O', NORTH) << std::endl;
		for(size_t j = 0; j < grid::height; j++)
		{
			for(size_t k = 0; k < grid::width; k++)
				std::cout << my_grid.array[j][k];
			std::cout << std::endl;
		}
		std::cout << "\n\n";
	}

	size_t final_index = (1000000000 - cycle_start) % cycle_length;
	grid final_grid = index_to_grid_map[cycle_start + final_index];

	// slide_all(lines, 'O', SOUTH);
	for(size_t j = 0; j < grid::height; j++)
	{
		for(size_t k = 0; k < grid::width; k++)
			std::cout << my_grid.array[j][k];
		std::cout << std::endl;
	}

	std::cout << count_load(final_grid, 'O', NORTH) << std::endl;
}

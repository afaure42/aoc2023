#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

int nbr_of_voids(std::vector<int> & voids, int start, int end)
{
	int nbr = 0;

	if (end < start)
		std::swap(start, end);
	for (auto & iter : voids)
	{
		if (iter >= start && iter <= end)
			nbr++;
	}
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
	while(std::getline(in_file, line, '\n'))
		lines.push_back(line);
	
	//expanding
	std::vector<int> vertical_voids;
	std::vector<int> horizontal_voids;
	for(size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].find('#') == lines[i].npos)
			horizontal_voids.push_back(i);
	}
	for(auto & iter : lines)
		std::cout << iter << std::endl;

	for(size_t i = 0; i < lines[0].length(); i++)
	{
		bool galaxy = false;
		for(size_t j = 0; j < lines.size(); j++)
		{
			if (lines[j][i] == '#')
				galaxy = true;
		}

		if (!galaxy)
			vertical_voids.push_back(i);
	}	

	for(auto & iter : lines)
		std::cout << iter << std::endl;
	std::vector<std::pair<int, int>> galaxies;
	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
		{
			if (lines[i][j] == '#')
				galaxies.push_back(std::make_pair(i, j));
		}
	}

	long long total = 0;
	for(size_t i = 0; i < galaxies.size(); i++)
	{
		for(size_t j = i + 1; j < galaxies.size(); j++)
		{
			// std::cout << "calculating distance between " << galaxies[i].first << " " << galaxies[i].second << " and " << galaxies[j].first << " " << galaxies[j].second << std::endl;

			int dist = std::abs(galaxies[i].first - galaxies[j].first) + std::abs(galaxies[i].second - galaxies[j].second)	
					+ nbr_of_voids(vertical_voids, galaxies[i].second, galaxies[j].second) * 999999
					+ nbr_of_voids(horizontal_voids, galaxies[i].first, galaxies[j].first) * 999999;
			total += dist;
			// std::cout << "distance is " << dist << std::endl;
		}
	}
	std::cout << total << std::endl;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>


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
	for(size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].find('#') == lines[i].npos)
		{
			lines.insert(lines.begin() + i, std::string(lines[0].length(), '.'));
			i++;
		}
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
		{
			for(size_t k = 0; k < lines.size(); k++)
				lines[k].insert(lines[k].begin() + i, '.');
			i++;
		}
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
			int dist = std::abs(galaxies[i].first - galaxies[j].first) + std::abs(galaxies[i].second - galaxies[j].second);
			total += dist;
			// std::cout << "distance is " << dist << std::endl;
		}
	}
	std::cout << total << std::endl;
}

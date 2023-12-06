#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void fill_vect(std::vector<long long> & vect, std::string & str)
{
	std::cout << "str : [" << str << ']' << std::endl;
	size_t index = 0;
	while (!str.empty())
	{
		std::cout << "str : [" << str << ']' << std::endl;
		long long num = std::stoll(str, &index);
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
	bool first_line = true;
	std::vector<long long>	times;
	std::vector<long long>	distances;
	int		total = 1;
	while(std::getline(in_file, line, '\n'))
	{
		if (first_line)
		{
			fill_vect(times, line);
			first_line = false;
		}
		else
			fill_vect(distances, line);
	}

	for(size_t i = 0; i < times.size(); i++)
	{
		// std::vector<int> race_distances(times[i]);
		int records_beat = 0;
		for(size_t j = 0; j < times[i]; j++)
		{
			if( j * (times[i] - j) > distances[i])
				records_beat++;
		}

		total *= records_beat;
	}

	std::cout << total << std::endl;
}

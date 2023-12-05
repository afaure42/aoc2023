#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void fill_vect(std::vector<unsigned long long> & vect, std::string & str)
{
	std::cout << "str : [" << str << ']' << std::endl;
	size_t index = 0;
	while (!str.empty())
	{
		std::cout << "str : [" << str << ']' << std::endl;
		unsigned long long num = std::stoull(str, &index);
		vect.push_back(num);
		str.erase(0, index + 1);
	}
}

unsigned long long find_next(std::vector<std::vector<unsigned long long>> & vect, unsigned long long value)
{
	for(size_t i = 0; i < vect.size(); i++)
	{
		// std::cout << "value : " << value << std::endl;	
		// std::cout << "testing for range : " << vect[i][1] << " - " << vect[i][1] + vect[i][2] << std::endl;
		if (vect[i][1] <= value && vect[i][1] + vect[i][2] > value) {
			return (vect[i][0] + (value - vect[i][1]));
		}
	}
	return 0;
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
	std::vector<std::vector<std::vector<unsigned long long>>> conversion_table(7);
	std::vector<unsigned long long> seeds;
	int index = 0;
	int sub_index = 0;
	int line_nbr = 0;
	while(std::getline(in_file, line, '\n'))
	{
		if (line.length() == 0)
			continue;
		if (line_nbr == 0)
		{
			fill_vect(seeds, line);
			line_nbr++;
			continue;
		}

		if(line == "seed-to-soil map:") {
			index = 0;
			sub_index = 0;
		} else if ( line == "soil-to-fertilizer map:") {
			index = 1;
			sub_index = 0;
		} else if ( line == "fertilizer-to-water map:") {
			index = 2;
			sub_index = 0;
		} else if (line == "water-to-light map:") {
			index = 3;
			sub_index = 0;
		} else if (line == "light-to-temperature map:") {
			index = 4;
			sub_index = 0;
		} else if (line == "temperature-to-humidity map:") {
			index = 5;
			sub_index = 0;
		} else if (line == "humidity-to-location map:") {
			index = 6;
			sub_index = 0;
		}
		else {
			conversion_table[index].push_back(std::vector<unsigned long long>());
			fill_vect(conversion_table[index][sub_index], line);
			sub_index++;
		}
	}

	unsigned long long lowest = 0;

	for (size_t i = 0; i < seeds.size(); i+= 2)
	{
		unsigned long long seed = seeds[i];
		unsigned long long current_value = seed;
		std::cout << "SEED : " << seed << std::endl;
		// int current_index = 0;
		for(size_t j = 0; j < conversion_table.size(); j++)
		{
			unsigned long next = find_next(conversion_table[j], current_value);
			if (next != 0)
				current_value = next;
			// std::cout << "SEED " << seed << "; NEXT_VALUE: " << current_value << std::endl;
		}
		if (current_value != 0 && (lowest == 0 || current_value < lowest))
			lowest = current_value;
	}
	std::cout << "lowest : " << lowest << std::endl;
}

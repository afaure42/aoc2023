#include <iostream>
#include <fstream>
#include <string>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

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
	int total = 0;
	while(std::getline(in_file, line, '\n'))
	{
		int max_red = 0;
		int max_blue = 0;
		int max_green = 0;
		bool impossible = false;
		size_t index = 0;
		int game_id = std::stoi(line, &index);
		index+= 2; //going through the : and space
		std::cout << "index : " << index << std::endl;
		std::cout << "game id :" << game_id << std::endl;
		std::cout << "first char : " << line[index] << std::endl;
		line.erase(0, index);
		while(!line.empty())
		{
			// std::cout << "index : " << index << std::endl;
			// std::cout << "first char : " << line[index] << std::endl;
			index = 0;
			int number_of_cubes = std::stoi(line, &index);
			index++; //skipping space

			if (line.substr(index, 4) == "blue") {
				index += 5;
				if (number_of_cubes > max_blue) {
					max_blue = number_of_cubes;
				}
			} else if (line.substr(index, 5) == "green") {
				index += 6;
				if (number_of_cubes > max_green) {
					max_green = number_of_cubes;
				}

			} else if (line.substr(index, 3) == "red") {
				index += 4;
				if (number_of_cubes > max_red) {
					max_red = number_of_cubes;
				}
			}
			line.erase(0, index);
		}
		total += (max_red * max_blue * max_green);
	}
	std::cout << "total : " << total << std::endl;
}

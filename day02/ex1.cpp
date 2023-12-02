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
				if (number_of_cubes > BLUE_MAX) {
					std::cout << "impossible blue game id :" << game_id << std::endl;
					std::cout << "number of cubes : " << number_of_cubes << std::endl;
					impossible = true;
					break;
				}
			} else if (line.substr(index, 5) == "green") {
				index += 6;
				if (number_of_cubes > GREEN_MAX) {
					std::cout << "impossible green game id :" << game_id << std::endl;
					std::cout << "number of cubes : " << number_of_cubes << std::endl;
					impossible = true;
					break;
				}

			} else if (line.substr(index, 3) == "red") {
				index += 4;
				if(number_of_cubes > RED_MAX) {
					std::cout << "impossible red game id :" << game_id << std::endl;
					std::cout << "number of cubes : " << number_of_cubes << std::endl;
					impossible = true;
					break;
				}
			}
			line.erase(0, index);
		}
		if (!impossible) {
			total += game_id;
		}
	}
	std::cout << "total : " << total << std::endl;
}

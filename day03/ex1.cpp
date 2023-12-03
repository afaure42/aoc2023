#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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
	std::vector<std::string> arr;

	while(std::getline(in_file, line, '\n'))
	{
		arr.push_back(line);
	}

	std::cout << isdigit('*') << std::endl;
	int total = 0;
	for(size_t i = 0; i < arr.size(); i++)
	{
		int current_number_index = -1;
		bool adjacent = false;
		for (size_t j = 0; j < arr[i].length(); j++)
		{
			if (!isdigit(arr[i][j]))
			{
				current_number_index = -1;
				continue;
			}
			else if (current_number_index  == -1)
				current_number_index = j;
			//UP CHECKS
			if (i > 0)
			{
				//DIRECTLY UP
				if (!isdigit(arr[i - 1][j]) && arr[i - 1][j] != '.')
				{
					adjacent = true;
					std::cout << "DIRECTLY UP " << arr[i - 1][j] << std::endl;
				}

				// UP LEFT
				if (j > 0 && !isdigit(arr[i - 1][j - 1]) && arr[i - 1][j - 1] != '.')
				{
					adjacent = true;
					std::cout << "UL" << std::endl;
				}

				// UP RIGHT
				if (j + 1 < arr[i].length() && !isdigit(arr[i - 1][j + 1]) && arr[i - 1][j + 1] != '.')
				{
					adjacent = true;
					std::cout << "UR" << std::endl;
				}
			}
			
			//DOWN CHECKS
			if (i + 1 < arr.size())
			{
				//DIRECTLY DOWN
				if (!isdigit(arr[i + 1][j]) && arr[i + 1][j] != '.')
				{
					adjacent = true;
					std::cout << "D" << std::endl;
				}

				// DOWN LEFT
				if (j > 0 && !isdigit(arr[i + 1][j - 1]) && arr[i + 1][j - 1] != '.')
				{
					adjacent = true;
					std::cout << "DL" << std::endl;
				}

				// DOWN RIGHT
				if (j + 1 < arr[i].length() && !isdigit(arr[i + 1][j + 1]) && arr[i + 1][j + 1] != '.')
				{
					adjacent = true;
					std::cout << "DR" << std::endl;
				}
			}

			//directly left
			if (j > 0 && !isdigit(arr[i][j - 1]) && arr[i][j - 1] != '.')
			{
				adjacent = true;
				std::cout << "L" << std::endl;
			}

			//directly right
			if (j + 1 < arr[i].length() && !isdigit(arr[i][j + 1]) && arr[i][j + 1] != '.')
			{
				adjacent = true;
				std::cout << "R" << std::endl;
			}
			

			size_t index;
			int number = std::stoi(arr[i].substr(current_number_index), &index);
			if (current_number_index + index - 1 == j)
			{
				std::cout << "number: " << number << '\n';
				if (adjacent)
					total += number;
				else
					std::cout << "not adjacent: " << number << '\n';
				adjacent = false;
			}
		}
	}
	std::cout << total << '\n';
}

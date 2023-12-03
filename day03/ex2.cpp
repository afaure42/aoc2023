#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int find_number(std::vector<std::string> & arr, size_t i, size_t j)
{
	while(j >= 0 && isdigit(arr[i][j]))
		j--;
	
	return (std::stoi(arr[i].substr(j + 1)));
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
	std::vector<std::string> arr;

	while(std::getline(in_file, line, '\n'))
	{
		arr.push_back(line);
	}

	std::cout << isdigit('*') << std::endl;
	int total = 0;
	for(size_t i = 0; i < arr.size(); i++)
	{
		for (size_t j = 0; j < arr[i].length(); j++)
		{
			if (arr[i][j] != '*')
				continue;
			// std::vector<std::pair<size_t, size_t>> coords;
			std::vector<int> adjacents;

			//UP CHECKS
			if (i > 0)
			{
				//DIRECTLY UP
				if (isdigit(arr[i - 1][j]))
				{
					adjacents.push_back(find_number(arr, i - 1, j));
					std::cout << "DIRECTLY UP " << arr[i - 1][j] << std::endl;
				}

				// UP LEFT
				if (j > 0 && isdigit(arr[i - 1][j - 1]))
				{
					adjacents.push_back(find_number(arr, i - 1, j - 1));
					std::cout << "UL" << std::endl;
				}

				// UP RIGHT
				if (j + 1 < arr[i].length() && isdigit(arr[i - 1][j + 1]))
				{
					adjacents.push_back(find_number(arr, i - 1, j + 1));
					std::cout << "UR" << std::endl;
				}
			}
			
			//DOWN CHECKS
			if (i + 1 < arr.size())
			{
				//DIRECTLY DOWN
				if (isdigit(arr[i + 1][j]))
				{
					adjacents.push_back(find_number(arr, i + 1, j));
					std::cout << "D" << std::endl;
				}

				// DOWN LEFT
				if (j > 0 && isdigit(arr[i + 1][j - 1]))
				{
					adjacents.push_back(find_number(arr, i + 1, j - 1));
					std::cout << "DL" << std::endl;
				}

				// DOWN RIGHT
				if (j + 1 < arr[i].length() && isdigit(arr[i + 1][j + 1]))
				{
					adjacents.push_back(find_number(arr, i + 1, j + 1));
					std::cout << "DR" << std::endl;
				}
			}

			//directly left
			if (j > 0 && isdigit(arr[i][j - 1]))
			{
				adjacents.push_back(find_number(arr, i, j - 1));
				std::cout << "L" << std::endl;
			}

			//directly right
			if (j + 1 < arr[i].length() && isdigit(arr[i][j + 1]))
			{
				adjacents.push_back(find_number(arr, i, j + 1));
				std::cout << "R" << std::endl;
			}
			
			if (adjacents.size() > 1)
			{
				size_t k = 0;
				while(k < adjacents.size())
				{
					if (k > 0 && adjacents[k] == adjacents[k - 1])
						adjacents.erase(adjacents.begin() + k);
					else
						k++;
				}
				if (adjacents.size() == 2)
				{
					std::cout << "found : " << adjacents[0] << " " << adjacents[1] << std::endl;
					total += adjacents[0] * adjacents[1];
				}
			}
		}
	}
	std::cout << total << '\n';
}

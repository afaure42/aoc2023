#include <iostream>
#include <fstream>
#include <string>

std::string numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

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
	long total = 0;
	while(std::getline(in_file, line, '\n'))
	{
		int number = 0;
		int i = 0;
		std::cout << "new line\n";
		std::cout << line << std::endl;
		for(auto iter = line.begin(); iter != line.end(); iter++)
		{
			std::cout << "line[i] : " << line[i] << std::endl;
			if (isdigit(*iter))
			{
				number = (*iter - '0' ) * 10;
				std::cout << "found digit " << number << std::endl;
				break;
			}
			for(int j = 0; j < 9; j++)
			{
				if (i + numbers[j].length() <= line.length() && line.compare(i, numbers[j].length(), numbers[j].c_str()) == 0)
				{
					number = (j + 1) * 10;
					std::cerr << "found number in front " << j + 1 << std::endl;
					break;
				}
			}
			if (number != 0)
				break;
			i++;
		}
		i = line.length() - 1;
		for(auto iter = line.rbegin(); iter != line.rend(); iter++)
		{
			bool found = false;
			if (isdigit(*iter))
			{
				number += (*iter - '0' );
				std::cout << "found digit " << *iter << std::endl;
				break;
			}
			for (int j = 0; j < 9 && !found; j++)
			{
				if (i + numbers[j].length() <= line.length() && line.compare(i, numbers[j].length(), numbers[j].c_str()) == 0)
				{
					number += j + 1;
					std::cerr << "found number at the end" << j + 1 << std::endl;
					found = true;
					break;
				}
			}
			if (found)
				break;
			i--;
		}
		total += number;
	}
	std::cout << total << std::endl;
}

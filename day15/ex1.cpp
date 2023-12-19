#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>


    // Determine the ASCII code for the current character of the string.
    // Increase the current value by the ASCII code you just determined.
    // Set the current value to itself multiplied by 17.
    // Set the current value to the remainder of dividing itself by 256.


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
	unsigned long long total = 0;
	while(std::getline(in_file, line, '\n'))
	{
		while(!line.empty())
		{
			unsigned long long value = 0;
			size_t end = line.find(',');
			for (auto & c : line.substr(0, end))
			{
				value += c;
				value *= 17;
				value &= 0xFF;
				std::cout << "char:" << c <<  "; value :" << value << std::endl;
			}
			total += value;
			if (end != std::string::npos)
				line.erase(0, end + 1);
			else
				line.clear();
		}
	}
	
	std::cout << total << std::endl;
}

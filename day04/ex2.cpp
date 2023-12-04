#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


void fill_vect(std::vector<int> & vect, std::string & str)
{
	size_t index = 0;
	while (!str.empty())
	{
		int num = std::stoi(str, &index);
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

	int delim = 0;
	int total = 0;
	int size = 0;
	std::string line;
	std::vector<int> copies(1000, 1);
	while(std::getline(in_file, line, '\n'))
	{
		size_t index = 0;

		int id = std::stoi(line, &index);
		line.erase(0, index + 1); //removing id and trailing ':'
		if (delim == 0)	
		{
			while(line[delim] != '|')
				delim++;
		}

		std::string str1 = line.substr(0, delim);
		std::string str2 = line.substr(delim + 1);

		std::vector<int> list1;
		std::vector<int> list2;
		fill_vect(list1, str1);
		fill_vect(list2, str2);

		int match = 0;
		for(size_t i = 0; i < list2.size(); i++)
		{
			if (std::find(list1.begin(), list1.end(), list2[i]) != list1.end())
			{
				match++;
			}
		}

		while (match > 0)
		{
			copies[id - 1 + match] += copies[id - 1]; //minus 1 because ids start at 1 and we dont like that
			match--;
		}
		size++;
	}
	for(int i = 0; i < size; i++) //counting total scratchcards
		total += copies[i];
	std::cout << "total : " << total << std::endl;
}

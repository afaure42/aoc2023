#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

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

bool zero_vect(std::vector<int> & vect)
{
	for (auto & iter : vect)
		if (iter != 0)
			return false;
	return true;
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
	std::vector<std::vector<int>> lines;
	while(std::getline(in_file, line, '\n'))
	{
		lines.push_back(std::vector<int>());
		fill_vect(lines.back(), line);
	}
	int total = 0;
	for (auto & iter : lines)
	{
		std::vector<std::vector<int>> subsequences;
		subsequences.push_back(iter);
		int index = 1;
		int j = 0;
		do {
			subsequences.push_back(std::vector<int>());
			j = 0;
			for(size_t i = 1; i < subsequences[index - 1].size(); i++)
			{
				subsequences[index].push_back(subsequences[index -1][j + 1] - subsequences[index - 1][j]);
				j++;
			}
			index++;
		} while(!zero_vect(subsequences.back()));
		int next = 0;


		subsequences.back().push_back(0); 
		for(int i = subsequences.size() - 2; i > -1; i--)
			subsequences[i].insert(subsequences[i].begin(), subsequences[i].front() - subsequences[i + 1].front());
		
		// I SHOULD HAVE DONE THIS TO FOLLOW MY LOGIC IN THE FIRST PART
		// int next = 0;
		// for(int i = subsequences.size() - 1; i > -1; i--)
			// next = subsequences[i].front() - next;

		total += subsequences[0][0];
	}

	std::cout << total << std::endl;
}

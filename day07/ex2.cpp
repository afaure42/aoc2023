#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

enum e_hand 
{
	high_card,
	one_pair,
	two_pairs,
	three_of_a_kind,
	full_house,
	four_of_a_kind,
	five_of_a_kind,
};

e_hand find_single_hand(std::string str)
{
	int doubles = 0;
	int different_doubles = 0;
	char c = '\0';
	std::sort(str.begin(), str.end());
	for (int i = 0; i + 1 < str.length(); i++)
	{
		if (str[i] == str[i + 1])
		{
			if (!c)
				c = str[i];
			if (str[i] != c)
				different_doubles++;
			doubles++;
		}
	}

	if(doubles == 0)
		return (high_card);
	else if (doubles == 1)
		return (one_pair);
	else if (doubles == 4)
		return (five_of_a_kind);
	else if (different_doubles == 0 && doubles == 3)
		return (four_of_a_kind);
	else if (different_doubles == 0 && doubles == 2)
		return (three_of_a_kind);
	else if (different_doubles >= 1 && doubles == 3)
		return (full_house);
	else if (different_doubles >= 1 && doubles == 2)
		return (two_pairs);
	return high_card;
}

e_hand find_hand(const std::string & str)
{
	std::string set = "ABCE98765432";


	e_hand best = high_card;
	for(size_t i = 0; i < set.length(); i++) //since i m a brute, i ll just replace the joker with every possible card and find the best hand
	{
		std::string input = str;
		std::replace(input.begin(), input.end(), '1', set[i]); // joker is marked as 1 because of later comparisons
		e_hand hand = find_single_hand(input);
		if (best < hand)
			best = hand;
	}
	return best;
}

int comp_cards(const std::string & s1, const std::string & s2)
{
	for(int i = 0; i < 5; i++)
	{
		if (s1[i] != s2[i])
		{
			if (isdigit(s1[i]) && !isdigit(s2[i]))
				return (-1);
			else if (!isdigit(s1[i]) && isdigit(s2[i]))
				return (1);
			else
				return (s1[i] - s2[i]);
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
	std::vector<std::pair<std::string, unsigned long long>> hands;
	while(std::getline(in_file, line, '\n'))
	{
		for(auto & iter : line)
		{
			if (iter == 'A') //replacing heads for easier comparisons
				iter = 'G';
			else if (iter == 'K')
				iter = 'F';
			else if (iter == 'Q')
				iter = 'E';
			else if (iter == 'J') //now joker will be the weakest card when comparing
				iter = '1';
			else if (iter == 'T')
				iter = 'C';
		}
		hands.push_back(std::make_pair(line.substr(0, 5), std::stoull(line.substr(5))));
	}

	std::sort(hands.begin(), hands.end(), [](const std::pair<std::string, unsigned long long> & lhs, const std::pair<std::string,unsigned long long> & rhs)
	{
		e_hand lhs_hand = find_hand(lhs.first);
		e_hand rhs_hand = find_hand(rhs.first);
		return (rhs_hand > lhs_hand || (lhs_hand == rhs_hand && comp_cards(lhs.first, rhs.first) < 0));
	});

	unsigned long long total = 0;
	for(size_t i = 0; i < hands.size(); i++)
	{
		std::cout << hands[i].first << " " << hands[i].second << " " << find_hand(hands[i].first) << std::endl;
		hands[i].second *= i + 1;
		total += hands[i].second;
	}

	std::cout << "total: " << total << std::endl;
}

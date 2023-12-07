#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

enum e_hand 
{
	five_of_a_kind,
	four_of_a_kind,
	full_house,
	three_of_a_kind,
	two_pairs,
	one_pair,
	high_card
};

e_hand find_hand(std::string str)
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

	std::cout << "double : " << doubles << std::endl;
	std::cout << "different doubles : " << different_doubles << std::endl;
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

int main()
{
	std::cout << find_hand("12345") << std::endl;
	std::cout << find_hand("12344") << std::endl;
	std::cout << find_hand("12312") << std::endl;
	std::cout << find_hand("42344") << std::endl;
	std::cout << find_hand("13331") << std::endl;
	std::cout << find_hand("21222") << std::endl;
	std::cout << find_hand("11111") << std::endl;	
}

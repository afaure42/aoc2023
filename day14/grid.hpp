#pragma once
#include <string>
#include <vector>


class grid
{
public:
	grid()
	{
		array = new char*[height];
		for(int i = 0; i < height; i++)
		{
			array[i] = new char[width + 1];
			array[i][width] = '\0';
		}

	};

	grid(std::vector<std::string> & lines)
	{
		width = lines[0].length();
		height = lines.size();
		array = new char*[height];
		for(int i = 0; i < height; i++)
		{
			array[i] = new char[width + 1];
			array[i][width] = '\0';
		}
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				array[i][j] = lines[j][i];
	};

	grid(grid && other)
	{
		array = other.array;
		other.array = nullptr;
	};

	grid(grid const & other)
	{
		array = new char*[height];
		for(int i = 0; i < height; i++)
		{
			array[i] = new char[width + 1];
			array[i][width] = '\0';
		}
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				array[i][j] = other.array[i][j];
	};

	grid & operator=(grid const & other)
	{
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				array[i][j] = other.array[i][j];
		return *this;
	};

	~grid()
	{
		if (array != nullptr)
		{
			for(int i = 0; i < height; i++)
				delete[] array[i];
			delete[] array;
		}
	};

	friend bool operator==(const grid & lhs, const grid & rhs)
	{
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
				if (lhs.array[i][j] != rhs.array[i][j])
					return false;
		return true;
	};

	char **array;
	static int width;
	static int height;
private:
};

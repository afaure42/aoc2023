#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <list>

enum e_dir
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

struct node;


typedef std::pair<e_dir, node *> action;

template<>
struct std::hash<action>
{
	size_t operator()(action const & m) const
	{
		size_t x = std::hash<e_dir>()(m.first);
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x ^ std::hash<unsigned long>()((unsigned long)m.second);
	}
};

std::unordered_map<action, bool> visited;

void solve(node * start, e_dir direction);

struct node
{
public:
	static size_t energized_nodes;
	node() : left(nullptr), right(nullptr), up(nullptr), down(nullptr), energized(false), name(".") {};
	node (std::string n) : left(nullptr), right(nullptr), up(nullptr), down(nullptr), energized(false), name(n) {};
	node (node * l, node * r, node * u, node * d) : left(l), right(r), up(u), down(d) {};
	node (node const & rhs) : left(rhs.left), right(rhs.right), up(rhs.up), down(rhs.down), energized(rhs.energized), name(rhs.name) {};
	virtual action get_next_node(e_dir direction)
	{
		if (visited.count(std::make_pair(direction, this)) > 0)
			return std::make_pair(direction, nullptr);
		visited[std::make_pair(direction, this)] = true;
		// print();
		if (energized == false)
		{
			energized = true;
			energized_nodes++;
		}
		switch (direction)
		{
			case RIGHT:
				return (std::make_pair(RIGHT, right));
			case LEFT:
				return (std::make_pair(LEFT, left));
			case UP:
				return (std::make_pair(UP, up));
			case DOWN:
				return (std::make_pair(DOWN, down));
		}
	}

	void set_nodes(node * l, node * r, node * u, node * d, std::string n = "")
	{
		left = l;
		right = r;
		up = u;
		down = d;
		name = n + ":" + name;
	}

	void print() {std::cout << "node: " << name << std::endl;};
	virtual ~node() {};
	virtual node * copy() {return new node(*this);};

	bool	energized;
protected :
	node * left;
	node * right;
	node * up;
	node * down;
	std::string name;
};

size_t node::energized_nodes = 0;

// / node
struct node_slash : public node
{
public:
	node * copy() override {return new node_slash(*this);};
	node_slash(node_slash const & rhs) : node(rhs) {};
	node_slash() : node("/") {};
	action get_next_node(e_dir direction) override
	{
		if (visited.count(std::make_pair(direction, this)) > 0)
			return std::make_pair(direction, nullptr);
		visited[std::make_pair(direction, this)] = true;
		// print();
		if (energized == false)
		{
			energized = true;
			energized_nodes++;
		}
		switch (direction)
		{
			case RIGHT:
				return std::make_pair(UP, up);
			case LEFT:
				return std::make_pair(DOWN, down);
			case UP:
				return std::make_pair(RIGHT, right);
			case DOWN:
				return std::make_pair(LEFT, left);
		}
	}
};

// \ node
struct node_backslash : public node
{
	node * copy() override {return new node_backslash(*this);};
	node_backslash(node_backslash const & rhs) : node(rhs) {};
	node_backslash() : node("\\") {};
	action get_next_node(e_dir direction) override
	{
		if (visited.count(std::make_pair(direction, this)) > 0)
			return std::make_pair(direction, nullptr);
		visited[std::make_pair(direction, this)] = true;
		// print();
		if (energized == false)
		{
			energized = true;
			energized_nodes++;
		}
		switch (direction)
		{
			case RIGHT:
				return std::make_pair(DOWN, down);
			case LEFT:
				return std::make_pair(UP, up);
			case UP:
				return std::make_pair(LEFT, left);
			case DOWN:	
				return std::make_pair(RIGHT, right);
		}
	}
};

// | node
struct node_pipe : public node
{
	node * copy() override {return new node_pipe(*this);};
	node_pipe(node_pipe const & rhs) : node(rhs) {};
	node_pipe() : node("|") {};
	action get_next_node(e_dir direction) override
	{
		if (visited.count(std::make_pair(direction, this)) > 0)
			return std::make_pair(direction, nullptr);
		visited[std::make_pair(direction, this)] = true;
		// print();
		if (energized == false)
		{
			energized = true;
			energized_nodes++;
		}
		switch(direction)
		{
			case RIGHT:
			case LEFT:
			{
				solve(up, UP); //launch a ray up
				return (std::make_pair(DOWN, down)); // keep going down
			}
			case UP:
				return (std::make_pair(UP, up));
			case DOWN:
				return (std::make_pair(DOWN, down));
		}
	}
};


// - node
struct node_dash : public node
{
	node * copy() override {return new node_dash(*this);};
	node_dash(node_dash const & rhs) : node(rhs) {};
	node_dash() : node("-") {};
	action get_next_node(e_dir direction) override
	{
		if (visited.count(std::make_pair(direction, this)) > 0)
			return std::make_pair(direction, nullptr);
		visited[std::make_pair(direction, this)] = true;
		// print();
		if (energized == false)
		{
			energized = true;
			energized_nodes++;
		}
		switch(direction)
		{
			case RIGHT:
				return (std::make_pair(RIGHT, right));
			case LEFT:
				return (std::make_pair(LEFT, left));
			case UP:
			case DOWN:
			{
				solve(left, LEFT); //launch a ray left
				return (std::make_pair(RIGHT, right)); // keep going right
			}
		}
	}
};

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
	std::vector<std::string> lines;
	std::vector<node *> nodes;
	while(std::getline(in_file, line, '\n'))
		lines.push_back(line);
	
	for(auto & str : lines)
	{
		for (auto & c : str)
		{
			switch (c)
			{
				case '/': {
					nodes.push_back(new node_slash());
					break;
				} case '\\':{
					nodes.push_back(new node_backslash());
					break;
				} case '-': {
					nodes.push_back(new node_dash());
					break;
				} case '|': {
					nodes.push_back(new node_pipe());
					break;
				} case '.':{
					nodes.push_back(new node());
					break;
				}
				default:
					continue;
			}
		}
	}
	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
		{
			node * l, * r, * u, * d;
			l = r = u = d = nullptr;

			if (i > 0)
				u = nodes[lines[i].length() * (i - 1) + j];
			if (i < lines.size() - 1)
				d = nodes[lines[i].length() * (i + 1) + j];
			if (j > 0)
				l = nodes[lines[i].length() * i + (j - 1)];
			if (j < lines[i].length() - 1)
				r = nodes[lines[i].length() * i + (j + 1)];
			nodes[lines[i].length() * i + j]->set_nodes(l, r, u, d, std::to_string(i) + ":" + std::to_string(j));
		}
	}

	size_t max = 0;
	action best;
	for(auto & n : nodes)
	{
		for(auto & d : {RIGHT, LEFT, UP, DOWN})
		{
		}
	}

	for(size_t i = 0; i < lines.size(); i++)
	{
		for(size_t j = 0; j < lines[i].length(); j++)
		{
			if (i > 0 && i < lines.size() - 1 && j > 0 && j < lines[i].length() - 1)
				continue;
			e_dir d;
			node * n = nodes[lines[i].length() * i + j];

			if (i == 0)
				d = DOWN;
			else if (i == lines.size() - 1)
				d = UP;
			else if (j == 0)
				d = RIGHT;
			else if (j == lines[i].length() - 1)
				d = LEFT;
			visited.clear();
			node::energized_nodes = 0;
			solve(n, d);
			if (node::energized_nodes > max)
			{
				max = node::energized_nodes;
				best = std::make_pair(d, n);
			}
			for (auto & n : nodes)
				n->energized = false;
		}
	}
	std::cout << "max:" << max << std::endl;
	std::cout << "best:" << best.first << std::endl;
	best.second->print();
}

void solve(node * start, e_dir direction)
{
	action next;
	next.second = start;
	next.first = direction;
	while (next.second != nullptr)
		next = next.second->get_next_node(next.first);
}

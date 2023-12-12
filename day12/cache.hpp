#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>

#define CACHE_SIZE 10000

struct hash_vect
{
	size_t operator()(std::vector<int> const& vec) const
	{
		std::size_t seed = vec.size();
		for(auto x : vec)
		{
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = (x >> 16) ^ x;
			seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

template<>
struct std::hash<std::tuple<std::string, std::vector<int>, int, int>>
{
	size_t operator()(const std::tuple<std::string, std::vector<int>, int, int> & k) const
	{
		std::size_t seed = std::get<1>(k).size();
		seed ^= std::hash<std::string>()(std::get<0>(k)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		for(auto x : std::get<1>(k))
		{
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = (x >> 16) ^ x;
			seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}

		seed ^= std::get<2>(k) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::get<3>(k) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};

typedef std::tuple<std::string, std::vector<int>, int, int> key_type;
typedef std::pair<key_type, unsigned long long> value_type;
typedef std::list<value_type>::iterator list_iter;
typedef std::unordered_map<key_type, list_iter>::iterator map_iter;

unsigned long long try_solve_4(std::string str, std::vector<int> & groups, int current, int index);

struct cache
{
	cache()
	{
		hashmap.reserve(CACHE_SIZE);
	}
	size_t misses = 0;
	size_t hits = 0;
	std::unordered_map<key_type, list_iter> hashmap;
	std::list<value_type> values;
	void add_to_cache(key_type key, unsigned long long value)
	{
		auto search = hashmap.find(key);
		if (search != hashmap.end()) //if we have it cached update it
		{
			search->second->second = value;
			push_to_front(search);
			return;
		}

		if (values.size() > CACHE_SIZE - 1) //if we have too many values in the cache, remove the oldest one
		{
			auto & iter = values.back();
			hashmap.erase(iter.first);
			values.pop_back();
		}

		// misses++;
		values.push_front(std::make_pair(key, value));
		hashmap.insert(std::make_pair(key, values.begin()));
	}

	std::pair<bool, unsigned long long> get(key_type key)
	{
		auto iter = hashmap.find(key);
		if (iter != hashmap.end())
		{
			hits++;
			auto ret = std::make_pair(true, iter->second->second);
			push_to_front(iter);
			return ret;
		}
		misses++;
		return std::make_pair(false, 0);
	}

	void push_to_front(map_iter & iter)
	{
		auto temp = *iter->second;
		values.erase(iter->second);
		values.push_front(temp);
		iter->second = values.begin();
	}

	void clear()
	{
		hashmap.clear();
		values.clear();
	}

};

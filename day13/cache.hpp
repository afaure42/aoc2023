#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>

#define CACHE_SIZE 10000


struct hash_vect
{
	size_t operator()(std::vector<std::string> const& vec) const
	{
		std::size_t seed = vec.size();
		for(auto str : vec)
		{
			auto x = std::hash<std::string>()(str);
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = (x >> 16) ^ x;
			seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

template<>
struct std::hash<std::tuple<std::string, std::string>>
{
	size_t operator()(std::tuple<std::string, std::string> const& tup) const
	{
		auto x = std::hash<std::string>()(std::get<0>(tup));
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		auto y = std::hash<std::string>()(std::get<1>(tup));
		y = ((y >> 16) ^ y) * 0x45d9f3b;
		y = ((y >> 16) ^ y) * 0x45d9f3b;
		y = (y >> 16) ^ y;
		return x ^ y;
	}
};

typedef std::tuple<std::string, std::string> key_type;
typedef std::pair<key_type, bool> value_type;
typedef std::list<value_type>::iterator list_iter;
typedef std::unordered_map<key_type, list_iter>::iterator map_iter;

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

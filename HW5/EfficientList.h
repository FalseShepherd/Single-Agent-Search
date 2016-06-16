#pragma once
#include <iostream>
#include <cassert>
#include <set>
//#include <tuple>
#include <map>
#include <queue>
#include <stdint.h>
#include "StateWrapper.h"
struct tupler
{
	tupler(int a, int b) : fcost(a), map(b) {}
	int fcost;
	int map;
	inline bool operator<(tupler a) const
	{
		return fcost < a.fcost;
	}
	inline void operator=(tupler a)
	{
		fcost = a.fcost;
		map = a.map;
	}
};


template<typename state_t>
class EfficientList
{
public:
	bool empty();
	bool find(state_wrapper_t<state_t> &state);
	void addOpen(state_wrapper_t<state_t> &state);
	void addClosed(state_wrapper_t<state_t> &state);
	void pop(state_wrapper_t<state_t>& st);

private:
	std::priority_queue<tupler> priorityQueue;
	std::map<int, state_wrapper_t<state_t>> hash;
};


template<typename state_t>
bool EfficientList<state_t>::empty()
{
	return hash.empty();
}
template<typename state_t>
bool EfficientList<state_t>::find(state_wrapper_t<state_t> &state)
{
	uint32_t num = state.rank;
	auto it = hash.find(num);
	if (it != hash.end())
	{
		return true;
	}
	return false;
}
template<typename state_t>
void EfficientList<state_t>::addOpen(state_wrapper_t<state_t> &state)
{
	uint32_t num = state.rank;
	auto it = hash.find(num);
	if (it != hash.end())
	{
		if(state.h + state.g < it->second.h + it->second.g)
		{
			hash[num] = state;
			tupler a(state.h + state.g, num);
			priorityQueue.push(a);
		}
		else
		{
			return;
		}
	}
	else
	{
		hash[num] = state;
		tupler a(state.h + state.g, num);
		priorityQueue.push(a);
	}
}

template<typename state_t>
void EfficientList<state_t>::addClosed(state_wrapper_t<state_t> &state)
{
	std::uint32_t num = state.rank;
	auto it = hash.find(num);
	if (it != hash.end())
	{
		if (state.h + state.g < it->second.h + it->second.g)
		{
			hash[num] = state;
		}
		else
		{
			return;
		}
	}
	else
	{
		hash[num] = state;
	}

}

template<typename state_t>
void EfficientList<state_t>::pop(state_wrapper_t<state_t>& st)
{
	tupler top = priorityQueue.top();
	st = hash[top.map];
	hash.erase(top.map);
	priorityQueue.pop();
	//return topState;
}

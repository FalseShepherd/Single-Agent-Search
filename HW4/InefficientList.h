#pragma once
#include "StateWrapper.h"
template<typename state_t>
class list {
public:
	bool empty();
	bool find(state_wrapper_t<state_t> state);
	void add(state_wrapper_t<state_t> state);
	state_wrapper_t<state_t> &min();
	state_wrapper_t<state_t> pop();
private:
	std::vector<state_wrapper_t<state_t>> array;
};
template<typename state_t>
bool list<state_t>::empty()
{
	return array.empty();
}
template<typename state_t>
bool list<state_t>::find(state_wrapper_t<state_t> state)
{
	for (int i = 0; i < array.size(); i++)
	{
		if (state.s == array[i].s && (state.g + state.h) >= (array[i].g + array[i].h))
		{
			return true;
		}
	}
	return false;
}
template<typename state_t>
void list<state_t>::add(state_wrapper_t<state_t> state)
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].s == state.s && (state.g + state.h) < (array[i].g + array[i].h))
		{
			array[i].g = state.g;
			array[i].h = state.h;
			return;
		}
		else if (array[i].s == state.s)
		{
			return;
		}
	}
	array.push_back(state);
}
template<typename state_t>
state_wrapper_t<state_t> &list<state_t>::min()
{
	int j = 0;
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].h + array[i].g < array[j].g + array[j].h)
		{
			j = i;
		}
		else if (array[i].h + array[i].g == array[j].g + array[j].h && array[i].g >= array[j].g)
		{
			j = i;
		}
	}
	return array[j];
}
template<typename state_t>
state_wrapper_t<state_t> list<state_t>::pop()
{
	state_wrapper_t<state_t> temp = this->min();
	array.erase(std::remove(array.begin(), array.end(), temp), array.end());
	return temp;
}
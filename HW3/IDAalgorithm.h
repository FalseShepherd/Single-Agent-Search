#pragma once
#include <list>
#include <vector>
#include <algorithm>

template<typename state, typename action, typename environment, typename heuristic>
class IDAalgorithm
{
public:
	int nodesExpanded;
	IDAalgorithm() : nodesExpanded(0) {}
	std::vector<action> GetPath(environment &e, state &start, state &goal, heuristic &heur)
	{
		h = heur;
		nodesExpanded = 0;
		path.clear();
		int limit = h.H(start, goal);
		while (true)
		{
			int minfCost = CostLimitedDFS(e, start, goal, 0, limit);
			if (minfCost == FOUND)
				return path;
			if (minfCost == NOT_FOUND)
				return path;
			limit = minfCost;
		}
	}

	int CostLimitedDFS(environment &e, state &start, state &goal, int gcost, int limit)
	{
		int fcost = gcost + h.H(start, goal);
		if (fcost > limit)
		{
			return fcost;
		}
		if (start == goal)
		{
			return FOUND;
		}
		int minCost = std::numeric_limits<int>::max();
		std::vector<action> actions;
		e.GetActions(start, actions);
		nodesExpanded++;
		for (action a : actions)
		{
			e.ApplyAction(start, a);
			path.emplace_back(a);
			int cost = CostLimitedDFS(e, start, goal, gcost + 1, limit);
			if (cost == FOUND)
				return FOUND;
			minCost = std::min(minCost, cost);
			e.UndoAction(start, a);
			path.pop_back();
		}
		return minCost;
	}
private:
	heuristic h;
	std::vector<action> path;
	const int FOUND = -1;
	const int NOT_FOUND = -2;
};


#pragma once
#include <cstdint>
#include <queue>
#include <vector>

template<typename state, typename action, typename environment>
class BFS
{
public:
	BFS() : nodesExpanded(0) {}
	// GetPath returns if the goal was found
	bool GetPath(environment &e, state &start, state &goal)
	{
		nodesExpanded = 0;
		std::queue<state> q;
		q.push(start);
		std::vector<action> actions;
		while (!q.empty())
		{
			state next = q.front();
			q.pop();
			e.GetActions(next, actions);
			nodesExpanded++;
			for (action a : actions)
			{
				e.ApplyAction(next, a);
				if (next == goal)
				{
					return true;
				}
				q.push(next);
				e.UndoAction(next, a);
			}
		}
		return false;
	}
	// Returns the total nodes expanded by the last GetPath call.
	uint64_t GetNodesExpanded()
	{
		return nodesExpanded;
	}
private:
	uint64_t nodesExpanded;
};

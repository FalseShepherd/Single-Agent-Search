#pragma once
#include <cstdint>
#include <vector>

template<typename state, typename action, typename environment>
class DFID
{
public:
	DFID() : nodesExpanded(0) {}
	// GetPath returns if the goal was found
	bool GetPath(environment &e, state &start, state &goal)
	{
		nodesExpanded = 0;
		bool done = false;
		for (uint32_t i = 0; !done; i++)
		{
			done = GetPath(e, start, goal, 0, i);
			if (done)
				return true;
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
	bool GetPath(environment &e, state &start, state &goal, uint32_t depth, uint32_t limit)
	{
		std::vector<action> actions;
		e.GetActions(start, actions);
		nodesExpanded++;
		for (action a : actions)
		{
			e.ApplyAction(start, a);
			if (start == goal)
			{
				return true;
			}
			if (depth < limit)
			{
				if (GetPath(e, start, goal, depth + 1, limit))
				{
					return true;
				}
			}
			e.UndoAction(start, a);
		}
		return false;
	}
};

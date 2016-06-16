#pragma once
#pragma once
#include <vector>
#include <algorithm>
//#include "EfficientList.h"
#include "InefficientList.h"

template<typename state, typename action, typename environment>
class Dijkstra
{
	typedef state_wrapper_t<state> state_wrapper;
public:
	state_wrapper ExpandtoFurthest(environment &e, std::vector<state> &start)
	{
		NodesExpanded = 0;
		open.getVec().clear();
		closed.getVec().clear();
		state_wrapper st;
		for (int i = 0; i < start.size(); i++)
		{
			st = { start.at(i), 0, 0, e.hash(start.at(i)) };
			open.add(st);
		}
		while (!open.empty())
		{
			//state_wrapper st;
			st = open.pop();
			//std::cout << "x: " << st.s.x << " y: " << st.s.y << " heuristic: " << st.h << "  Gcost: " << st.g << " Fcost: " << st.g+st.h << "\n";
			if (!closed.find(st))
			{
				std::vector<action> moves;
				e.GetActions(st.s, moves);
				NodesExpanded++;
				//std::cout << NodesExpanded << "\n";
				//std::cout << st.g + st.h << "\n";
				for (auto& m : moves)
				{
					e.ApplyAction(st.s, m);
					if (open.find(st) || closed.find(st))
					{
						//do nothing, skip this node.
					}
					else {
						state_wrapper s{ st.s, st.g + 1, 0, e.hash(st.s) };
						open.add(s);
					}
					e.UndoAction(st.s, m);
				}
				closed.add(st);
			}
		}
		return st;
	}
	std::vector<state_wrapper> DifferentialSearch(environment &e, state &start)
	{
		NodesExpanded = 0;
		open.getVec().clear();
		closed.getVec().clear();
		state_wrapper st{ start, 0, 0, e.hash(start) };
		open.add(st);
		while (!open.empty())
		{
			//state_wrapper st;
			st = open.pop();
			//std::cout << "x: " << st.s.x << " y: " << st.s.y << " heuristic: " << st.h << "  Gcost: " << st.g << " Fcost: " << st.g+st.h << "\n";
			if (!closed.find(st))
			{
				std::vector<action> moves;
				e.GetActions(st.s, moves);
				NodesExpanded++;
				//std::cout << NodesExpanded << "\n";
				//std::cout << st.g + st.h << "\n";
				for (auto& m : moves)
				{
					e.ApplyAction(st.s, m);
					if (open.find(st) || closed.find(st))
					{
						//do nothing, skip this node.
					}
					else {
						state_wrapper s{ st.s, st.g + 1, 0, e.hash(st.s) };
						open.add(s);
					}
					e.UndoAction(st.s, m);
				}
				closed.add(st);
			}
		}
		return closed.getVec();
	}

private:
	list<state> open;
	list<state> closed;
	int NodesExpanded = 0;
	std::vector<action> path;
	const int FOUND = -1;
	const int NOT_FOUND = -2;
};

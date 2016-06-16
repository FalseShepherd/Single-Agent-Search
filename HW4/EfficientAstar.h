#pragma once
#pragma once
#include <vector>
#include <algorithm>
#include "EfficientList.h"

template<typename state, typename action, typename environment, typename heuristic>
class EfficientAStar
{
    typedef state_wrapper_t<state> state_wrapper;
public:
    int GetPath(environment &e, state &start, state &goal)
    {
		NodesExpanded = 0;
		state_wrapper st{ start,0,heur.H(start, goal), e.hash(start) };
        open.addOpen(st);
        while(!open.empty())
        {
			//state_wrapper st;
			open.pop(st);
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
					if (st.s == goal) {
						st.g++;
						std::cout << NodesExpanded << "\n";
						std::cout << st.g << "\n";
						return st.g;
					}
					else if (open.find(st) || closed.find(st))
					{
						//do nothing, skip this node.
					}
					else {
						state_wrapper s{ st.s, st.g + 1, heur.H(st.s, goal),e.hash(st.s) };
						open.addOpen(s);
					}
					e.UndoAction(st.s, m);
				}
				closed.addClosed(st);
			}
        }
    }

private:
    EfficientList<state> open;
    EfficientList<state> closed;
	int NodesExpanded = 0;
    heuristic heur;
    std::vector<action> path;
    const int FOUND = -1;
    const int NOT_FOUND = -2;
};

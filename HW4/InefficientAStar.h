//
// Created by nathan on 4/30/16.
//

#pragma once
#include <vector>
#include <algorithm>
#include "InefficientList.h"

template<typename state, typename action, typename environment, typename heuristic>
class InefficientAStar
{
    typedef state_wrapper_t<state> state_wrapper;
public:
    int GetPath(environment &e, state &start, state &goal)
    {
		NodesExpanded = 0;
        open.add(state_wrapper {start,0,heur.H(start, goal), 0 });
        while(!open.empty())
        {
			state_wrapper st = open.pop();
			//std::cout << "x: " << st.s.x << " y: " << st.s.y << " heuristic: " << st.h << "  Gcost: " << st.g << " Fcost: " << st.g+st.h << "\n";
            std::vector<action> moves;
            e.GetActions(st.s, moves);
			NodesExpanded++;
			if(NodesExpanded % 1000 == 0)
			std::cout << NodesExpanded << "\n";
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
                    open.add(state_wrapper {st.s, st.g + 1, heur.H(st.s, goal), 0});
                }
                e.UndoAction(st.s, m);
            }
			closed.add(st);
        }
    }

private:
    list<state> open;
    list<state> closed;
	int NodesExpanded = 0;
    heuristic heur;
    std::vector<action> path;
    const int FOUND = -1;
    const int NOT_FOUND = -2;
};

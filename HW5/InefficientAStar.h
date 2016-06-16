//
// Created by nathan on 4/30/16.
//

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "InefficientList.h"

template<typename state, typename action, typename environment, typename heuristic>
class InefficientAStar
{
    typedef state_wrapper_t<state> state_wrapper;
public:
    int GetPath(environment &e, state &start, state &goal, heuristic &heur)
    {
		NodesExpanded = 0;
        open.getVec().clear();
        closed.getVec().clear();
        open.add(state_wrapper {start,0, heur.H(e, start, goal), 0 });
        while(!open.empty())
        {
			state_wrapper st = open.pop();
			//std::cout << "x: " << st.s.x << " y: " << st.s.y << " heuristic: " << st.h << "  Gcost: " << st.g << " Fcost: " << st.g+st.h << "\n";
            std::vector<action> moves;
            e.GetActions(st.s, moves);
			NodesExpanded++;
			for (auto& m : moves)
			{
                e.ApplyAction(st.s, m);
                if (st.s == goal) {
					st.g++;
					std::cout << "Nodes expanded: " << NodesExpanded << "\n";
					std::cout << "Solution cost: " << st.g << "\n";
                    return st.g;
                }
				else if (open.find(st) || closed.find(st))
				{
					//do nothing, skip this node.
				}
                else {
                    open.add(state_wrapper {st.s, st.g + 1, heur.H(e, st.s, goal), 0});
                }
                e.UndoAction(st.s, m);
            }
			closed.add(st);
        }
        std::cout << "no path found :(\n";
        return -1;
    }

private:
    list<state> open;
    list<state> closed;
	int NodesExpanded = 0;
    std::vector<action> path;
    const int FOUND = -1;
    const int NOT_FOUND = -2;
};

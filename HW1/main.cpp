#include <iostream>
#include "GridEnvironment.h"
#include "NAryTree.h"
#include "BFS.h"
#include "DFID.h"

int main(int argc, char* argv[]) {
	NAryTree tree(2);
	BFS<NAryTreeState, NAryTreeAction, NAryTree> bfs;
	NAryTreeState start = 0;
	NAryTreeState goal = 20;
	bfs.GetPath(tree, start, goal);
	std::cout << "BFS of tree " << bfs.GetNodesExpanded() << " nodes expanded\n";
	
	DFID<NAryTreeState, NAryTreeAction, NAryTree> dfid;
	dfid.GetPath(tree, start, goal);
	std::cout << "DFID of tree " << dfid.GetNodesExpanded() << " nodes expanded\n";

	GridEnvironment grid(3, 3);
	GridState gStart(0, 0);
	GridState gFinish(1, 2);
	BFS<GridState, GridAction, GridEnvironment> bfsGrid;
	std::cout << "starting grid bfs\n";
	bfsGrid.GetPath(grid, gStart, gFinish);
	std::cout << "BFS of grid " << bfsGrid.GetNodesExpanded() << " nodes expanded in grid\n";

	DFID<GridState, GridAction, GridEnvironment> dfidGrid;
	std::cout << "starting grid bfs\n";
	dfidGrid.GetPath(grid, gStart, gFinish);
	std::cout << "DFID of grid " << dfidGrid.GetNodesExpanded() << " nodes expanded in grid\n";
	return 0;
}
#include "GridEnvironment.h"
//#include "SlidingTileEnvironment.h"
#include "InefficientAStar.h"
//#include "EfficientAStar.h"
#include "DifferentialHeuristic.h"
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <chrono>

int main() {
//	std::ofstream out("out.txt");
//	std::cout.rdbuf(out.rdbuf());
	srand(0);
	std::vector<GridAction > act;
	std::string filename = "lak303d.map";
	GridEnvironment g(filename);

	std::ifstream scen_file(filename + ".scen");
	std::string line = "";
	std::string skip = "";
	getline(scen_file, line);

	InefficientAStar<GridState, GridAction , GridEnvironment, DifferentialHeuristic> SlowAS;
	DifferentialHeuristic dh;
	dh.FurthestPivots(g, 10);

	DifferentialHeuristic dh2;
	dh2.RandomPivots(g, 10);


	while (getline(scen_file, line)) {
		std::stringstream ss(line);
		ss >> skip;
		ss >> skip;
		ss >> skip;
		ss >> skip;
		int startX, startY, goalX, goalY;
		ss >> startX;
		ss >> startY;
		ss >> goalX;
		ss >> goalY;
		ss >> skip;

		std::cout << "\nstart: " << startX << " " << startY << " goal: " << goalX << " " << goalY << std::endl;
		GridState start{ startX, startY };
		GridState goal{ goalX, goalY };;
		assert(g.valid(start.x,start.y));
		assert(g.valid(goal.x,goal.y));
		std::cout << "Farthest spaced:\n";
		auto time1 = std::chrono::system_clock::now();
		SlowAS.GetPath(g, start, goal, dh);
		std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - time1).count() << " ms\n";
		std::cout << "Random pivots:\n";
		time1 = std::chrono::system_clock::now();
		SlowAS.GetPath(g, start, goal, dh2);
		std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - time1).count() << " ms\n";
	}
}

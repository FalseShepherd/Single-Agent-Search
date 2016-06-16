#include <unordered_map>
#include <vector>
#include <random>
#include "EfficientAstar.h"
#include "Dijkstra.h"
#include "GridEnvironment.h"
struct OctileDist {
	static int H(GridState a, GridState b) {
		int x = std::abs(a.x - b.x);
		int y = std::abs(a.y - b.y);
		return 	std::max(x, y) + std::min(x, y) / 2;
//		return round(std::max(x, y) + std::min(x, y)*(sqrt(2)-1.0));
	}
};
struct Pivot
{
public:
	std::unordered_map<int, int> distances;
	GridState place;
};

class DifferentialHeuristic
{
public:
	void RandomPivots(GridEnvironment &e, int numPivots)
	{
		int32_t xpivot;
		int32_t ypivot;
		int count = 0;
		while (count < numPivots)
		{
			xpivot = rand() % e.getWidth();
			ypivot = rand() % e.getHeight();
			if (e.valid(xpivot, ypivot))
			{
				GridState currentPivot(xpivot, ypivot);
				Pivots.push_back(currentPivot);
				count++;
			}
		}
		for (int i = 0; i < numPivots; i++)
		{
			Pivot p;
			p.place = Pivots.at(i);
//			Differentials.at(i).place = Pivots.at(i);
			std::vector<state_wrapper_t<GridState>> temp = D.DifferentialSearch(e, Pivots.at(i));
			for (int j = 0; j < temp.size(); j++)
			{
				auto &st = temp.at(j);
				int key = e.hash(st.s);
				auto a = p.distances.find(key);
				if (a == p.distances.end()) {
					p.distances.insert(std::make_pair(e.hash(temp.at(j).s), temp.at(j).g));
				} else if (st.g < a->second) {
					std::cout << "updated g-cost\n";
					p.distances.at(key) = st.g;
				}
			}
			Differentials.emplace_back(p);
		}
	}
	void FurthestPivots(GridEnvironment &e, int numPivots)
	{
		int32_t xpivot;
		int32_t ypivot;
		while (true)
		{
			xpivot = rand() % e.getWidth();
			ypivot = rand() % e.getHeight();
			if (e.valid(xpivot, ypivot))
			{
				break;
			}
		}
		GridState currentPivot(xpivot, ypivot);
		for (int i = 0; i < numPivots; i++)
		{
			//do a Dijkstra for every pivot on the open list 
			Pivots.push_back(currentPivot);
			currentPivot = D.ExpandtoFurthest(e, Pivots).s;
		}
		for (int i = 0; i < numPivots; i++)
		{
			Pivot p;
			p.place = Pivots.at(i);
//			Differentials.at(i).place = Pivots.at(i);
			std::vector<state_wrapper_t<GridState>> temp = D.DifferentialSearch(e, Pivots.at(i));
			for (int j = 0; j < temp.size(); j++)
			{
				auto &st = temp.at(j);
				int key = e.hash(st.s);
				auto a = p.distances.find(key);
				if (a == p.distances.end()) {
					p.distances.insert(std::make_pair(e.hash(temp.at(j).s), temp.at(j).g));
				} else if (st.g < a->second) {
					std::cout << "updated g-cost\n";
					p.distances.at(key) = st.g;
				}
			}
			Differentials.emplace_back(p);
		}
	}
	int H(GridEnvironment &e, GridState &start, GridState &goal)
	{
//		return OctileDist::H(start, goal);
		int max = 0;

		for (int i = 0; i < Differentials.size(); i++)
		{
			auto &d = Differentials.at(i);
			auto g = d.distances.find(e.hash(goal));
			auto s = d.distances.find(e.hash(start));
			if (s != d.distances.end() && g != d.distances.end()) {
				int Temp = std::abs(Differentials.at(i).distances.at(e.hash(goal)) -
									Differentials.at(i).distances.at(e.hash(start)));
				if (Temp > max) {
					max = Temp;
				}
			} else {
//				std::cout << "eeek pivot: " << i << " state: " << start.x << " " << start.y << " hash: " << e.hash(start) << " pivot x: " << d.place.x << " y: " << d.place.y << "\n";
			}
		}
		if (OctileDist::H(start, goal) > max)
		{
//			std::cout << "used octile " << OctileDist::H(start, goal) << " " << max << "\n";
			max = OctileDist::H(start, goal);
		} // else std::cout << "didn't use octile!! " << OctileDist::H(start, goal) << " " << max << "\n";
		return max;
	}
private:
	std::vector<GridState> Pivots;
	std::vector<Pivot> Differentials;
	Dijkstra<GridState, GridAction, GridEnvironment> D;
};
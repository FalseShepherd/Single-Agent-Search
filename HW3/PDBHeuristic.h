#include <deque>
#include "PDB.h"

class PDBHeuristic {
public:
	PDBHeuristic();
	PDBHeuristic(std::vector<std::vector<int>> pats);
	~PDBHeuristic();
	int H(SlidingTileState &current, SlidingTileState &goal);
private:
	int L1(SlidingTileState &s);
	std::vector<PDB*> heurs;
};

PDBHeuristic::~PDBHeuristic()
{
	for (auto& p : heurs)
		delete p;
}

PDBHeuristic::PDBHeuristic() {}

PDBHeuristic::PDBHeuristic(std::vector<std::vector<int>> pats)
{
	for (auto& i : pats) {
		PDB* p = new PDB(i);
		p->CreatePDB();
		heurs.emplace_back(p);
	}
}

int PDBHeuristic::L1(SlidingTileState &s)
{
	int heuristic=0;
	for (int i = 0; i < 16; i++)
	{
		if (s.board[i] != 0)
		{
			int val = s.board[i];
			int goalx = val % 4;
			int goaly = val / 4;
			int curx = i % 4;
			int cury = i / 4;
			heuristic += std::abs(goalx - curx) + std::abs(goaly - cury);
		}
	}
	return heuristic;
}


// ignores goal ;-)
int PDBHeuristic::H(SlidingTileState &current, SlidingTileState &goal)
{
	int h = -1;
	for (auto& i : heurs) {
		h = std::max(i->getDepth(current), h);
	}
	return std::max(h, L1(current));
}

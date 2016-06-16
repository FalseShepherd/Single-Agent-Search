#pragma once
#include <algorithm>
#include <cstdint>
#include <vector>
#include <array>

enum Action { STPup, STPright, STPdown, STPleft, fakeIgnoreMe };

struct SlidingTileState{
	SlidingTileState(std::array<int, 16> a);
	std::array<int, 16> board;
	int hcost = 0;
	int blank = 0;
	int x, y;
	Action prevAction;
};


inline bool operator==(const SlidingTileState &lhs, const SlidingTileState &rhs)
{
	//for (int i = 0; i < 16; i++)
	//{
	//	if (lhs.board[i] != rhs.board[i])
	//		return false;
	//}
	return lhs.board == rhs.board;
}

class SlidingTileEnvironment {
public:
	void GetActions(SlidingTileState &a, std::vector<Action> &actions);
	void ApplyAction(SlidingTileState &s, Action a);
	void UndoAction(SlidingTileState &s, Action a);
	uint64_t rank(SlidingTileState &a, std::vector<int> pattern);
	void unrank( uint64_t hashVal, SlidingTileState& s, std::vector<int> pattern);
	uint64_t hash(SlidingTileState &a);
};

class ManhattanDistance
{
public:
	int H(SlidingTileState &current, SlidingTileState &goal);
};


#pragma once
#include <cstdint>
#include <vector>
#include <array>

enum Action { up, right, down, left, fakeIgnoreMe };

struct SlidingTileState{
	SlidingTileState(std::array<int, 16> a);
	std::array<int, 16> Environment;
	int x, y;
	Action prevAction;
};

inline bool operator==(const SlidingTileState &lhs, const SlidingTileState &rhs)
{
	//for (int i = 0; i < 16; i++)
	//{
	//	if (lhs.Environment[i] != rhs.Environment[i])
	//		return false;
	//}
	return lhs.Environment == rhs.Environment;
}

class SlidingTileEnvironment {
public:
	void GetActions(SlidingTileState &a, std::vector<Action> &actions);
	void ApplyAction(SlidingTileState &s, Action a);
	void UndoAction(SlidingTileState &s, Action a);
};

class SlidingTileHeuristic
{
public:
	int H(SlidingTileState &current, SlidingTileState &goal);
};
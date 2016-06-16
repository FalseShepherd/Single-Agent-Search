#pragma once
#include <vector>
#include <cstdint>

enum GridAction { grid_up, /*down, left,*/ grid_right };

class GridState
{
public:
	GridState(int32_t x, int32_t y) : x(x), y(y) {}
	int32_t x = 0, y = 0;
};

inline bool operator==(const GridState& lhs, const GridState& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

class GridEnvironment
{
public:
	GridEnvironment(int32_t width=128, int32_t height=128);
	~GridEnvironment();
	void GetActions(GridState &nodeID, std::vector<GridAction> &actions);
	void ApplyAction(GridState &s, GridAction a);
	void UndoAction(GridState &s, GridAction a);
private:
	int32_t width, height;
};

class ManhattanDistance
{
public:
	int H(GridState start, GridState goal)
	{
		return std::abs(start.x - goal.x) + std::abs(start.y - goal.y);
	}
};

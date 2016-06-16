#pragma once
#include <vector>
#include <cstdint>

enum GridAction { up, /*down, left,*/ right };

class GridState
{
public:
	GridState(uint32_t x, uint32_t y) : x(x), y(y) {}
	uint32_t x = 0, y = 0;
};

inline bool operator==(const GridState& lhs, const GridState& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

class GridEnvironment
{
public:
	GridEnvironment(uint32_t width=128, uint32_t height=128);
	~GridEnvironment();
	void GetActions(GridState &nodeID, std::vector<GridAction> &actions);
	void ApplyAction(GridState &s, GridAction a);
	void UndoAction(GridState &s, GridAction a);
private:
	uint32_t width, height;
};

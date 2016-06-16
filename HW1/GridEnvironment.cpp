#include "GridEnvironment.h"

GridEnvironment::GridEnvironment(uint32_t width, uint32_t height) : width(width), height(height)
{
}


GridEnvironment::~GridEnvironment()
{
}

void GridEnvironment::GetActions(GridState &nodeID, std::vector<GridAction> &actions)
{
	actions.clear();
	//if (nodeID.y > 0)
	//	actions.emplace_back(down);
	if (nodeID.y < height)
		actions.emplace_back(up);
	//if (nodeID.x > 0)
	//	actions.emplace_back(left);
	if (nodeID.x < width)
		actions.emplace_back(right);
}

void GridEnvironment::ApplyAction(GridState &s, GridAction a)
{
	switch(a)
	{
	case up:
			s.y++;
		break;
	//case down:
	//		s.y--;
	//	break;
	//case left:
	//		s.x--;
	//	break;
	case right:
			s.x++;
		break;
	}
}

void GridEnvironment::UndoAction(GridState &s, GridAction a)
{
	switch (a)
	{
	case up:
			s.y--;
		break;
	//case down:
	//		s.y++;
	//	break;
	//case left:
	//		s.x++;
	//	break;
	case right:
			s.x--;
		break;
	}
}
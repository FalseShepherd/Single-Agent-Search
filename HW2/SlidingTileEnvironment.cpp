#include "SlidingTileEnvironment.h"
SlidingTileState::SlidingTileState(std::array<int, 16> a) : Environment(a), prevAction(fakeIgnoreMe)
{
for (int i = 0; i < 16; i++)
	{
		if (a[i] == 0)
		{
			this->x = (i % 4);
			this->y = (i / 4);
			break;
		}
	}
}

void SlidingTileEnvironment::GetActions(SlidingTileState &a, std::vector<Action> &actions)
{
	actions.clear();
	if (a.x > 0 && a.prevAction != right)
		actions.emplace_back(left);
	if (a.x < 3 && a.prevAction != left)
		actions.emplace_back(right);
	if (a.y > 0 && a.prevAction != down)
		actions.emplace_back(up);
	if (a.y < 3 && a.prevAction != up)
		actions.emplace_back(down);
}
void SlidingTileEnvironment::ApplyAction(SlidingTileState &s, Action a)
{
	s.prevAction = a;
	int arraynum = s.y * 4 + s.x;
	switch (a)
	{
	case up:
		std::swap(s.Environment[arraynum], s.Environment[arraynum-4]);
		s.y--;
		break;
	case down:
		std::swap(s.Environment[arraynum], s.Environment[arraynum + 4]);
		s.y++;
		break;
	case left:
		std::swap(s.Environment[arraynum], s.Environment[arraynum-1]);
		s.x--;
		break;
	case right:
		std::swap(s.Environment[arraynum], s.Environment[arraynum + 1]);
		s.x++;
		break;
	}
}
void SlidingTileEnvironment::UndoAction(SlidingTileState &s, Action a)
{
	s.prevAction = fakeIgnoreMe;
	int arraynum = s.y * 4 + s.x;
	switch (a)
	{
	case up:
		std::swap(s.Environment[arraynum], s.Environment[arraynum + 4]);
		s.y++;
		break;
	case down:
		std::swap(s.Environment[arraynum], s.Environment[arraynum - 4]);
		s.y--;
		break;
	case left:
		std::swap(s.Environment[arraynum], s.Environment[arraynum + 1]);
		s.x++;
		break;
	case right:
		std::swap(s.Environment[arraynum], s.Environment[arraynum - 1]);
		s.x--;
		break;
	}
}
int SlidingTileHeuristic::H(SlidingTileState &s, SlidingTileState &goal)
{
	//goal gets ignored
	int heuristic=0;
	for (int i = 0; i < 16; i++)
	{
		if (s.Environment[i] != 0)
		{
			int val = s.Environment[i];
			int goalx = val % 4;
			int goaly = val / 4;
			int curx = i % 4;
			int cury = i / 4;
			heuristic += std::abs(goalx - curx) + std::abs(goaly - cury);
		}
	}
	return heuristic;
}

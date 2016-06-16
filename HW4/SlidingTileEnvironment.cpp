#include "SlidingTileEnvironment.h"
static uint64_t factorial(uint64_t n)
{
	static std::array<int64_t, 17> precomp{ 1L, 1L, 2L, 6L, 24L, 120L, 720L, 5040L, 40320L, 362880L, 3628800L, 39916800L, 479001600L, 6227020800L, 87178291200L, 1307674368000L, 20922789888000L };
	return precomp[n];
}
SlidingTileState::SlidingTileState(std::array<int, 16> a) : board(a), prevAction(fakeIgnoreMe)
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

uint64_t SlidingTileEnvironment::rank(SlidingTileState &a, std::vector<int> pattern)
{
	uint64_t hashval = 0;
	// int size = 0;
	int numEntriesLeft = 16;
	std::vector<int> dual(pattern.size());
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < pattern.size(); y++) 
		{
			if (a.board[x] == pattern[y])
			{
				dual[a.board[x]] = x;
				break;
			}
		}
	}

	for (int x = 0; x < pattern.size(); x++)
	{
		hashval += dual[x] * factorial(numEntriesLeft - 1) / factorial(16 - pattern.size());
		for (unsigned y = x; y < pattern.size(); y++)
		{
			if (dual[y] > dual[x])
				dual[y]--;
		}
		numEntriesLeft--;
	}
	return hashval;
}

void SlidingTileEnvironment::unrank(uint64_t hashVal, SlidingTileState& s, std::vector<int> pattern)
{
	// int numEntriesLeft = 16 - pattern.size() + 1;
	std::vector<int> dual(pattern.size());
	for (int x = 0; x < pattern.size(); x++)
	{
		auto t = (factorial(15 - x) / factorial(16 - pattern.size()));
		dual[x] = hashVal / t;
		hashVal %= t;
		// hashVal /= numEntriesLeft;
	}
	for (int x = pattern.size() - 1; x >= 0; x--)
	{
		for (int y = x - 1; y >= 0; y--)
		{
			if (dual[y] <= dual[x])
			{
				dual[x]++;
			}
		}
	}

	for (auto &i : s.board)
		i = -1;
	for (int x = 0; x < pattern.size(); x++)
	{ 
		s.board[dual[x]] = pattern[x];
		// if (dual[x] != -1)
		if (pattern[x] == 0) {
			s.x = dual[x] % 4;
			s.y = dual[x] / 4;
		}
	}
}

uint64_t SlidingTileEnvironment::hash(SlidingTileState &a)
{
	std::vector<int> pattern{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	uint64_t hashval = 0;
	// int size = 0;
	int numEntriesLeft = 16;
	std::vector<int> dual(pattern.size());
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < pattern.size(); y++)
		{
			if (a.board[x] == pattern[y])
			{
				dual[a.board[x]] = x;
				break;
			}
		}
	}

	for (int x = 0; x < pattern.size(); x++)
	{
		hashval += dual[x] * factorial(numEntriesLeft - 1) / factorial(16 - pattern.size());
		for (unsigned y = x; y < pattern.size(); y++)
		{
			if (dual[y] > dual[x])
				dual[y]--;
		}
		numEntriesLeft--;
	}
	return hashval;
}


void SlidingTileEnvironment::GetActions(SlidingTileState &a, std::vector<Action> &actions)
{
	actions.clear();
	if (a.x > 0 && a.prevAction != STPright)
		actions.emplace_back(STPleft);
	if (a.x < 3 && a.prevAction != STPleft)
		actions.emplace_back(STPright);
	if (a.y > 0 && a.prevAction != STPdown)
		actions.emplace_back(STPup);
	if (a.y < 3 && a.prevAction != STPup)
		actions.emplace_back(STPdown);
}
void SlidingTileEnvironment::ApplyAction(SlidingTileState &s, Action a)
{
	s.prevAction = a;
	int arraynum = s.y * 4 + s.x;
	switch (a)
	{
	case STPup:
		std::swap(s.board[arraynum], s.board[arraynum-4]);
		s.y--;
		break;
	case STPdown:
		std::swap(s.board[arraynum], s.board[arraynum + 4]);
		s.y++;
		break;
	case STPleft:
		std::swap(s.board[arraynum], s.board[arraynum-1]);
		s.x--;
		break;
	case STPright:
		std::swap(s.board[arraynum], s.board[arraynum + 1]);
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
	case STPup:
		std::swap(s.board[arraynum], s.board[arraynum + 4]);
		s.y++;
		break;
	case STPdown:
		std::swap(s.board[arraynum], s.board[arraynum - 4]);
		s.y--;
		break;
	case STPleft:
		std::swap(s.board[arraynum], s.board[arraynum + 1]);
		s.x++;
		break;
	case STPright:
		std::swap(s.board[arraynum], s.board[arraynum - 1]);
		s.x--;
		break;
	}
}

int ManhattanDistance::H(SlidingTileState &s, SlidingTileState &goal)
{
	//goal gets ignored
	int heuristic = 0;
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
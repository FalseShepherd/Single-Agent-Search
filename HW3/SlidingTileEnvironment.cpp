#include "SlidingTileEnvironment.h"
#include "PDB.h"
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

uint64_t SlidingTileEnvironment::rank(SlidingTileState &a)
{
 	uint64_t hashval = 0;
 	int size = 0;
 	int numEntriesLeft = 16;
 	std::array<int, 16> loc;
 	for (int &i : loc)
 		i = -1;
 	for (unsigned int x = 0; x < 16; x++)
 	{
 		if (a.board[x] != -1)
 		{
 			size++;
 			loc[a.board[x]] = x;
 		}
 	}
 	for (int x = 0; x < 16; x++)
 	{
 		if (loc[x] != -1)
 		{
 			hashval += loc[x] * factorial(numEntriesLeft - 1) / factorial(16 - size);
 			for (unsigned y = x; y < 16; y++)
 			{
 				if (loc[y] > loc[x] && loc[y] != -1)
 					loc[y]--;
 			}
 			numEntriesLeft--;
 		}
 	}
 	return hashval;
}

void SlidingTileEnvironment::unrank(uint64_t hashVal, SlidingTileState &s, std::vector<int> pattern)
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
		std::swap(s.board[arraynum], s.board[arraynum-4]);
		s.y--;
		break;
	case down:
		std::swap(s.board[arraynum], s.board[arraynum + 4]);
		s.y++;
		break;
	case left:
		std::swap(s.board[arraynum], s.board[arraynum-1]);
		s.x--;
		break;
	case right:
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
	case up:
		std::swap(s.board[arraynum], s.board[arraynum + 4]);
		s.y++;
		break;
	case down:
		std::swap(s.board[arraynum], s.board[arraynum - 4]);
		s.y--;
		break;
	case left:
		std::swap(s.board[arraynum], s.board[arraynum + 1]);
		s.x++;
		break;
	case right:
		std::swap(s.board[arraynum], s.board[arraynum - 1]);
		s.x--;
		break;
	}
}

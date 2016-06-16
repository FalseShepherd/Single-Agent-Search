#include "NAryTree.h"

NAryTree::NAryTree(uint32_t n) : n(n)
{
}


NAryTree::~NAryTree()
{
}

void NAryTree::GetActions(NAryTreeState &nodeID, std::vector<NAryTreeAction> &actions)
{
	actions.clear();
	for (uint32_t i = 0; i < n; ++i)
	{
		actions.emplace_back(i);
	}
}

void NAryTree::ApplyAction(NAryTreeState &s, NAryTreeAction a)
{
	s = s * n + 1 + a;
}

void NAryTree::UndoAction(NAryTreeState &s, NAryTreeAction a)
{
	s = (s - 1 - a) / n;
}
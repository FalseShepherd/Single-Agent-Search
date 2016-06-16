#pragma once
#include <cstdint>
#include <vector>

typedef int32_t NAryTreeState;

typedef int32_t NAryTreeAction;

class ZeroHeuristic
{
public:
	int H(NAryTreeState, NAryTreeState)
	{
		return 0;
	}
};

class NAryTree
{
public:
	NAryTree(int32_t n);
	~NAryTree();
	void GetActions(NAryTreeState &nodeID, std::vector<NAryTreeAction> &actions);
	void ApplyAction(NAryTreeState &s, NAryTreeAction a);
	void UndoAction(NAryTreeState &s, NAryTreeAction a);
private:
	int32_t n;
};

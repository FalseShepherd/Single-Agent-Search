#pragma once
#include <cstdint>
#include <vector>

typedef uint32_t NAryTreeState;

typedef uint32_t NAryTreeAction;

class NAryTree
{
public:
	NAryTree(uint32_t n);
	~NAryTree();
	void GetActions(NAryTreeState &nodeID, std::vector<NAryTreeAction> &actions);
	void ApplyAction(NAryTreeState &s, NAryTreeAction a);
	void UndoAction(NAryTreeState &s, NAryTreeAction a);
private:
	uint32_t n;
};

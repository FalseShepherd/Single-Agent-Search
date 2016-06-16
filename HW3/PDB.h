#pragma once
#include <atomic>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "SlidingTileEnvironment.h"

static uint64_t factorial(uint64_t n)
{
	static std::array<int64_t, 17> precomp{ 1L, 1L, 2L, 6L, 24L, 120L, 720L, 5040L, 40320L, 362880L, 3628800L, 39916800L, 479001600L, 6227020800L, 87178291200L, 1307674368000L, 20922789888000L };
	return precomp[n];
}

class PDB
{
public:
	PDB(std::vector<int> a);
	//PDB(std::string filename);
	// TODO read from file
	void CreatePDB();
	int getDepth(SlidingTileState& s);
private:
	size_t pdb_size;
	std::unique_ptr<std::atomic<uint8_t>[]> pdb;
	std::vector<int> pattern;
	SlidingTileEnvironment env;

};


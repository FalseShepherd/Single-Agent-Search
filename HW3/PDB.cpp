#include <fstream>
#include <iterator>

#include "PDB.h"
// #include <omp.h>

PDB::PDB(std::vector<int> a) : pattern(a), pdb_size(factorial(16) / factorial(16 - a.size()))
{
	pdb = std::unique_ptr<std::atomic<uint8_t>[]>(new std::atomic<uint8_t>[pdb_size]);
	for (uint64_t i = 0; i < pdb_size; i++)
		pdb[i] = 255;
}

void PDB::CreatePDB()
{
	// std::unique_ptr<std::atomic<uint8_t>[]> pdb(new std::atomic<uint8_t>[pdb_size]);
	SlidingTileState s{ { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 } };
	std::vector<Action> moves;
	for (auto i : pattern) {
		s.board[i] = i;
	}
	
	pdb[env.rank(s)] = 0;
	std::atomic<uint64_t> count {1};

	for (int d = 0; d < 255; d++) {
		#pragma omp parallel for firstprivate(s, moves)
		for (uint64_t i = 0; i < pdb_size; i++) {
			if (pdb[i] == d) {
				env.unrank(i, s, pattern);
				env.GetActions(s, moves);
				for (auto &a : moves) {
					env.ApplyAction(s, a);

					uint64_t r = env.rank(s);
					uint8_t test_val = 255;
					if (pdb[r].compare_exchange_strong(test_val, d + 1)) {
						++count;
					}
					env.UndoAction(s, a);
				}
			}
		}

		std::cout << "Depth " << d << " complete; " << count << " of " << pdb_size << "total \n";
		if (count == pdb_size)
			break;
	}
}

int PDB::getDepth(SlidingTileState& s)
{
	SlidingTileState s_copy(s.board);
	for (int i = 0; i < 16; i++)
	{
		bool a = true;
		for (int p : pattern)
		{
			if(s_copy.board[i] == p)
				a = false;
		}
		if (a)
			s_copy.board[i] = -1;
	}
	return pdb[env.rank(s_copy)];
}

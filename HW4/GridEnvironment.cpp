#include <iostream>
#include <cassert>
#include "GridEnvironment.h"

GridEnvironment::GridEnvironment(std::string filename)
{
	std::ifstream map_file(filename);
	if (map_file.is_open()) {
		std::string line;
		std::getline(map_file, line);
		map_file >> line;
		map_file >> height;
		map_file >> line;
		map_file >> width;
		grid.reserve(width*height);
		std::getline(map_file, line); std::getline(map_file, line); // skips the line that says map
		std::cout << line << std::endl;
		while (std::getline(map_file, line)) {
			for (char& c : line) {
				assert(c != '\n');
				if (c != '.'){
					grid.push_back(false);
				}
				else
				{
					grid.push_back(true);
				}
			}
		}
	} else {
		std::cout << "wtf is going on exploding\n";
	}
}


GridEnvironment::~GridEnvironment()
{
}

void GridEnvironment::GetActions(GridState &s, std::vector<GridAction> &actions)
{
	actions.clear();
	if (s.y > 0 && grid.at(s.x+width*(s.y-1)))
		actions.emplace_back(up);
	if (s.y < height && grid.at(s.x+width*(s.y+1)))
		actions.emplace_back(down);
	if (s.x > 0 && grid.at(s.x-1+width*s.y))
		actions.emplace_back(left);
	if (s.x < width && grid.at(s.x+1+width*(s.y)))
		actions.emplace_back(right);
	if (s.x != width && s.y != height && grid.at(s.x+1+width*(s.y+1)) && grid.at(s.x+width*(s.y+1)) && grid.at(s.x+1+width*(s.y)))
		actions.emplace_back(down_right);
	if (s.x != width && s.y != 0 && grid.at(s.x+1+width*(s.y-1)) && grid.at(s.x+width*(s.y-1)) && grid.at(s.x+1+width*(s.y)))
		actions.emplace_back(up_right);
	if (s.x != 0 && s.y != 0 && grid.at(s.x-1+width*(s.y-1)) && grid.at(s.x+width*(s.y-1)) && grid.at(s.x-1+width*s.y))
		actions.emplace_back(up_left);
	if (s.x != 0 && s.y != height && grid.at(s.x-1+width*(s.y+1)) && grid.at(s.x+width*(s.y+1)) && grid.at(s.x-1+width*s.y))
		actions.emplace_back(down_left);
}

void GridEnvironment::ApplyAction(GridState &s, GridAction a)
{
	switch(a)
	{
	case up:
		s.y--;
		break;
	case down:
		s.y++;
		break;
	case left:
		s.x--;
		break;
	case right:
		s.x++;
		break;
	case up_left:
		s.y--;
		s.x--;
		break;
	case up_right:
		s.y--;
		s.x++;
		break;
	case down_left:
		s.y++;
		s.x--;
		break;
	case down_right:
		s.y++;
		s.x++;
		break;
	}
}

void GridEnvironment::UndoAction(GridState &s, GridAction a)
{
	switch (a)
	{
	case up:
		s.y++;
		break;
	case down:
		s.y--;
		break;
	case left:
		s.x++;
		break;
	case right:
		s.x--;
		break;
	case up_left:
		s.y++;
		s.x++;
		break;
	case up_right:
		s.y++;
		s.x--;
		break;
	case down_left:
		s.y--;
		s.x++;
		break;
	case down_right:
		s.y--;
		s.x--;
		break;
	}
}

int GridEnvironment::hash(GridState &s)
{
	if (width > height)
	{
		return s.x + s.y * width;
	}
	else
	{
		return s.y + s.x * height;
	}
}

GridState GridEnvironment::unhash(int hash)
{
	if (width > height)
	{
		return GridState(hash % width, hash / width);
	}
	else
	{
		return GridState(hash % height, hash / height);
	}
}
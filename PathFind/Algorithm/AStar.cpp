#include "AStar.h"
#include <cassert>

AStar::AStar()
{

}

AStar::~AStar()
{

}

void AStar::Find(
	const GridInfo& grid,
	const Coordinate& from,
	const Coordinate& to,
	PathWay& way)
{
	assert(grid.w >= 0);
	assert(grid.h >= 0);
	assert(grid.data.size() == grid.h * grid.w());
	if (grid.size() <= 2) return;
}
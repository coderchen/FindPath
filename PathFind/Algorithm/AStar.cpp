#include "AStar.h"
#include <cassert>

AStar::AStar()
{

}

AStar::~AStar()
{

}

void AStar::Find(
	const MapGrid& m,
	const Coordinate& from,
	const Coordinate& to,
	PathWay& way)
{
	assert(m.points.size() == m.h * m.w);
}
#pragma once

#include "IPathFind.h"

class AStar : public IPathFind
{
public:
	AStar();
	~AStar();

	virtual void Find(
		const MapGrid& m,
		const Coordinate& from,
		const Coordinate& to,
		PathWay& way);
};
#pragma once

#include <vector>

struct Coordinate
{
	int x;
	int y;

	Coordinate(int xPos = 0, int yPos = 0) 
		: x(xPos), y(yPos)
	{ }
};

typedef std::vector<Coordinate> PathWay;

struct MapGrid
{
	int width;
	int height;
	std::vector<int> points;
};

class IPathFind
{
public:
	IPathFind() { }
	virtual ~IPathFind() { }

	virtual void Find(
		const MapGrid& m, 
		const Coordinate& from, 
		const Coordinate& to, 
		PathWay& way) = 0;
};
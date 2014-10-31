#pragma once

#include <vector>

struct Coordinate
{
	unsigned int X;
	unsigned int Y;

	Coordinate() : X(0), Y(0) { }
};

typedef std::vector<Coordinate> PathWay;

struct MapGrid
{
	unsigned int W;
	unsigned int H;
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
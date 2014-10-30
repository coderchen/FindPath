#pragma once

#include <tuple>
#include <vector>

typedef std::tuple<int, int> Coordinate;
typedef std::vector<Coordinate> PathWay;

struct MapGrid
{
	std::size_t w;
	std::size_t h;
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
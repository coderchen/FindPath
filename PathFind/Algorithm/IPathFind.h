#pragma once

#include <tuple>
#include <vector>

typedef std::tuple<int, int> Coordinate;
typedef std::vector<Coordinate> PathWay;

struct GridInfo
{
	int w;
	int h;
	std::vector<int> data;
};

class IPathFind
{
public:
	IPathFind() { }
	virtual ~IPathFind() { }

	virtual void Find(
		const GridInfo& grid, 
		const Coordinate& from, 
		const Coordinate& to, 
		PathWay& way) = 0;
};
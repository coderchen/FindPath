#include <iostream>
#include "Algorithm/AStar.h"

int main()
{
	{
		MapGrid m;
		m.width = 3;
		m.height = 3;
		m.points.push_back(0);
		m.points.push_back(0);
		m.points.push_back(1);
		m.points.push_back(0);
		m.points.push_back(1);
		m.points.push_back(0);
		m.points.push_back(0);
		m.points.push_back(0);
		m.points.push_back(0);

		Coordinate from(0, 0);
		Coordinate to(2, 2);

		PathWay way;
		AStar a;
		a.Find(m, from, to, way);

		for (const Coordinate& c : way)
			std::cout << c.x << " " << c.y << std::endl;
		std::cout << std::endl;
	}

	{
	MapGrid m;
	m.width = 7;
	m.height = 4;
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(1);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);

	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(1);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);

	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(1);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);

	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);
	m.points.push_back(0);

	Coordinate from(1, 1);
	Coordinate to(5, 1);

	PathWay way;
	AStar a;
	a.Find(m, from, to, way);

	for (const Coordinate& c : way)
		std::cout << c.x << " " << c.y << std::endl;
	std::cout << std::endl;
	}

	return 0;
}
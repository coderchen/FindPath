#include "AStar.h"
#include <cassert>
#include <algorithm>

AStar::AStar()
{

}

AStar::~AStar()
{

}

void AStar::_checkValid(const MapGrid& m, const Coordinate& from, const Coordinate& to)
{
	assert(m.points.size() == m.height * m.width);
	assert(!(from.x == to.x && from.y == to.y));
	assert(from.x >= 0 && from.x < m.width);
	assert(from.y >= 0 && from.y < m.height);
	assert(to.x >= 0 && to.x < m.width);
	assert(to.y >= 0 && to.y < m.height);
}

void AStar::Find(
	const MapGrid& m,
	const Coordinate& from,
	const Coordinate& to,
	PathWay& way)
{
	_checkValid(m, from, to);

	m_dynMap.resize(m.width * m.height);
	for (_Node& n : m_dynMap)
		n.reset();

	std::vector<int> minHeap;

	int idx = from.y * m.width + from.x;
	_Node& n = m_dynMap[idx];
	n.opened = true;
	n.g = 0;
	n.h = abs(from.x - to.x) + abs(from.y - to.y);
	minHeap.push_back(idx);
	std::push_heap(minHeap.begin(), minHeap.end(), _NodeMinHeapCmp(m_dynMap));

	const int DIR_CNT = 4;
	const int X_DIR[DIR_CNT] = {0, 1, 0, -1};
	const int Y_DIR[DIR_CNT] = {-1, 0, 1, 0};

	bool bFind = false;
	while (!minHeap.empty() && !bFind)
	{
		int pos = minHeap.front();
		std::pop_heap(minHeap.begin(), minHeap.end(), _NodeMinHeapCmp(m_dynMap));
		minHeap.pop_back();
		m_dynMap[pos].closed = true;

		int x = pos % m.width;
		int y = pos / m.width;

		for (int i = 0; i < 4; ++i)
		{
			int nextX = x + X_DIR[i];
			int nextY = y + Y_DIR[i];

			if (nextX < 0 || nextX >= m.width 
				|| nextY < 0 || nextY >= m.height)
				continue;
			if (m.points[nextY * m.width + nextX] == 1) continue;

			_Node& nextNode = m_dynMap[nextY * m.width + nextX];
			if (nextNode.closed) continue;

			if (nextNode.opened)
			{
				if (m_dynMap[pos].g + 1 < nextNode.g)
				{
					nextNode.g = m_dynMap[pos].g + 1;
					nextNode.parent = pos;
				}
			}
			else
			{
				nextNode.opened = true;
				nextNode.parent = pos;
				nextNode.g = m_dynMap[pos].g + 1;
				nextNode.h = abs(nextX - to.x) + abs(nextY - to.y);
				if (nextX == to.y && nextY == to.y)
				{
					bFind = true;
					break;
				}

				minHeap.push_back(nextY * m.width + nextX);
				std::push_heap(minHeap.begin(), minHeap.end(), _NodeMinHeapCmp(m_dynMap));
			}
		}
	}

	if (!bFind) return;

	int curX = to.x;
	int curY = to.y;
	while (1)
	{
		way.push_back(Coordinate(curX, curY));
		int p_pos = m_dynMap[curY * m.width + curX].parent;
		if (p_pos == -1) break;
		curX = p_pos % m.width;
		curY = p_pos / m.width;
	}

	std::reverse(way.begin(), way.end());
}
#include "AStar.h"
#include <cassert>
#include <functional>
#include <algorithm>

AStar::AStar() : m_dynMap(), m_minHeap()
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

bool AStar::_nodeCmp(_Node* n1, _Node* n2)
{
	assert(n1 && n2);
	assert(n1->x != -1 && n1->y != -1);
	assert(n2->x != -1 && n2->y != -1);

	return n1->g + n1->h > n2->g + n2->h;
}

void AStar::Find(
	const MapGrid& m,
	const Coordinate& from,
	const Coordinate& to,
	PathWay& way)
{
	_checkValid(m, from, to);

	m_minHeap.clear();
	m_dynMap.clear();
	m_dynMap.resize(m.width * m.height);

	_Node& start = m_dynMap[from.y * m.width + from.x];
	start.opened = true;
	start.g = 0;
	start.h = abs(from.x - to.x) + abs(from.y - to.y);
	start.x = from.x;
	start.y = from.y;
	m_minHeap.push_back(&start);
	std::push_heap(m_minHeap.begin(), m_minHeap.end(),
		std::bind(&AStar::_nodeCmp, this, std::placeholders::_1, std::placeholders::_2));

	//上右下左
	const int DIR_CNT = 4;
	const int X_DIR[DIR_CNT] = {0, 1, 0, -1};
	const int Y_DIR[DIR_CNT] = {-1, 0, 1, 0};

	bool bFind = false;
	while (!m_minHeap.empty() && !bFind)
	{
		_Node* pMin = m_minHeap.front();
		std::pop_heap(m_minHeap.begin(), m_minHeap.end(), 
			std::bind(&AStar::_nodeCmp, this, std::placeholders::_1, std::placeholders::_2));
		m_minHeap.pop_back();
		pMin->closed = true;

		for (int i = 0; i < DIR_CNT; ++i)
		{
			int nextX = pMin->x + X_DIR[i];
			int nextY = pMin->y + Y_DIR[i];

			//检测有效坐标
			if (nextX < 0 || nextX >= m.width 
				|| nextY < 0 || nextY >= m.height)
				continue;

			//检测是否可以通过 1:障碍
			if (m.points[nextY * m.width + nextX] == 1) continue;

			//检测是否已经加入关闭列表
			_Node& nextNode = m_dynMap[nextY * m.width + nextX];
			if (nextNode.closed) continue;

			if (nextNode.opened)
			{
				//新路径更短
				if (pMin->g + 1 < nextNode.g)
				{
					nextNode.g = pMin->g + 1;
					nextNode.parent = pMin;
					std::make_heap(m_minHeap.begin(), m_minHeap.end(),
						std::bind(&AStar::_nodeCmp, this, std::placeholders::_1, std::placeholders::_2));
				}
			}
			else
			{
				nextNode.opened = true;
				nextNode.parent = pMin;
				nextNode.g = pMin->g + 1;
				nextNode.h = abs(nextX - to.x) + abs(nextY - to.y);
				nextNode.x = nextX;
				nextNode.y = nextY;
				if (nextX == to.x && nextY == to.y)
				{
					bFind = true;
					break;
				}

				m_minHeap.push_back(&nextNode);
				std::push_heap(m_minHeap.begin(), m_minHeap.end(),
					std::bind(&AStar::_nodeCmp, this, std::placeholders::_1, std::placeholders::_2));
			}
		}
	}
	
	if (!bFind) return;
	_Node* p = &m_dynMap[to.y * m.width + to.x];
	while (p)
	{
		way.push_back(Coordinate(p->x, p->y));
		p = p->parent;
	}
	std::reverse(way.begin(), way.end());
}
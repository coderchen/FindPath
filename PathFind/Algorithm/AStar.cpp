#include "AStar.h"
#include <cassert>
#include <algorithm>

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
	assert(m.points.size() == m.H * m.W);
	assert(!(from.X == to.X && from.Y == to.Y));
	assert(from.X >= 0 && from.X < m.W);
	assert(from.Y >= 0 && from.Y < m.H);
	assert(to.X >= 0 && to.X < m.W);
	assert(to.Y >= 0 && to.Y < m.H);

	m_runtime.resize(m.H * m.W);
	for (int i = 0; i < m.H * m.W; ++i)
	{
		m_runtime[i].reset();
	}

	m_minHeap.clear();

	int pos = from.X * m.W + from.Y;
	_Node& node = m_runtime[pos];
	node.opened = true;
	node.X = from.X;
	node.Y = from.Y;
	node.G = 0;
	node.H = 0;
	m_minHeap.push_back(&node);
	std::push_heap(m_minHeap.begin(), m_minHeap.end(), _minHeapCmp);

	static int xDiff[] = { 0, 1, 0, -1 };
	static int yDiff[] = { -1, 0, 1, 0 };

	bool bFind = false;
	while (!m_minHeap.empty() && !bFind)
	{
		_Node* pMin = m_minHeap.front();
		std::pop_heap(m_minHeap.begin(), m_minHeap.end(), _minHeapCmp);
		m_minHeap.pop_back();
		pMin->closed = true;

		for (int i = 0; i < 4; ++i)
		{
			int nextX = pMin->X + xDiff[i];
			int nextY = pMin->Y + yDiff[i];

			if (nextX < 0 || nextX >= m.W || nextY < 0 || nextY >= m.H)
				continue;
			_Node& nextNode = m_runtime[nextX * m.W + nextY];
			if (nextNode.closed) continue;
			if (nextNode.opened)
			{
				if (pMin->G + 1 < nextNode.G)
				{
					nextNode.G = pMin->G + 1;
					nextNode.parent = pMin;
				}
			}
			else
			{
				nextNode.opened = true;
				nextNode.parent = pMin;
				nextNode.G = pMin->G + 1;
				nextNode.H = 1;//FIXME 
				nextNode.X = nextX;
				nextNode.Y = nextY;
				if (nextNode.X == to.X && nextNode.Y == to.Y)
				{
					bFind = true;
					break;
				}

				m_minHeap.push_back(&nextNode);
				std::push_heap(m_minHeap.begin(), m_minHeap.end(), _minHeapCmp);
			}
		}
	}

	if (!bFind) return;

	_Node* p = &m_runtime[to.X * m.W + to.Y];
	while (p)
	{
		Coordinate c;
		c.X = p->X;
		c.Y = p->Y;
		way.push_back(c);
		p = p->parent;
	}

	std::reverse(way.begin(), way.end());
}

bool AStar::_minHeapCmp(const _Node* n1, const _Node* n2)
{
	return (n1->G + n1->H > n2->G + n2->H);
}
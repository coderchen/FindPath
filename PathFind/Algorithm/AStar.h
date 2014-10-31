#pragma once

#include "IPathFind.h"

class AStar : public IPathFind
{
	struct _Node
	{
		bool opened;
		bool closed;
		int g;
		int h;
		int parent;

		_Node() { this->reset(); }
		void reset()
		{
			opened = false;
			closed = false;
			g = 0;
			h = 0;
			parent = -1;
		}
	};

	struct _NodeMinHeapCmp
	{
		_NodeMinHeapCmp(std::vector<_Node>& m)
		: m_dynMapRef(m) { }

		bool operator()(int pos1, int pos2)
		{
			_Node& n1 = m_dynMapRef[pos1];
			_Node& n2 = m_dynMapRef[pos2];
			return n1.g + n1.h > n2.g + n2.h;
		}

		std::vector<_Node>& m_dynMapRef;
	};

public:
	AStar();
	~AStar();

	virtual void Find(
		const MapGrid& m,
		const Coordinate& from,
		const Coordinate& to,
		PathWay& way);

private:
	void _checkValid(const MapGrid& m, const Coordinate& from, const Coordinate& to);

private:
	std::vector<_Node> m_dynMap;
};
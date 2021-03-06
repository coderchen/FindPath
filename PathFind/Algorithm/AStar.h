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
		int x;
		int y;
		_Node* parent;

		_Node() { this->reset(); }
		void reset()
		{
			opened = false;
			closed = false;
			g = 0;
			h = 0;
			x = -1;
			y = -1;
			parent = nullptr;
		}
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
	bool _nodeCmp(_Node* n1, _Node* n2);

private:
	std::vector<_Node> m_dynMap;
	std::vector<_Node*> m_minHeap;
};
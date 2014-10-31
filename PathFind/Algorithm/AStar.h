#pragma once

#include "IPathFind.h"

class AStar : public IPathFind
{
	struct _Node
	{
		bool opened;
		bool closed;
		unsigned int G;
		unsigned int H;
		unsigned int X;
		unsigned int Y;
		_Node* parent;

		_Node() { this->reset(); }
		void reset()
		{
			opened = false;
			closed = false;
			G = 0;
			H = 0;
			X = 0;
			Y = 0;
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
	static bool _minHeapCmp(const _Node* n1, const _Node* n2);

private:
	std::vector<_Node> m_runtime;
	std::vector<_Node*> m_minHeap;
};
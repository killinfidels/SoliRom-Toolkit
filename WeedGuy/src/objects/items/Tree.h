#pragma once
#include "../../core.h"
#include "../Object.h"

class Tree : public Object
{
public:
	Tree(int _tree, int _size, int _x, int _y);

	void Animate();

	std::vector<std::string> treeList;
	SoliRom::Asset::Animation* a_tree;

	bool load = false;
};


#pragma once
#include "Tree.h"


void treeTest() {
	diy::Tree<int> intTree(5);

	intTree.insert(3);
	intTree.insert(7);
}
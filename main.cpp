#include "RBtree.hpp"


#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

int main()
{
	std::vector<int>a{1,2,3,7,9,32,10,12,25,67,0,-12};
	RBTree<int> tree(a);
	tree.add(6);
	tree.add(5);
	tree.add(321);
	tree.print();







}
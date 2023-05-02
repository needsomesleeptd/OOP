#include "RBtree.hpp"

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

int main()
{
	std::vector<int> a{ 2, 1, 3};
	RBTree<int> tree(a);
	tree.add(6);
	tree.add(5);

	tree.add(5);
	tree.add(321);
	tree.remove(6);
	tree.remove(56);
	RBIterator<int> it = tree.begin();
	for (it = tree.begin(); it != tree.end(); it++)
		std::cout << *it << " ";
	std::cout<< '\n';
	for (it = tree.begin(); it != tree.end(); ++it)
		std::cout << *it << " ";

	tree.setDifference(a);
	tree.print();


	tree.print();

}
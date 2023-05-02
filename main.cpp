#include "RBtree.hpp"

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <iterator>

int main()
{
	std::vector<int> a{ 2, 1, 3};
	std::vector<int> b{ 3, 5, 4};

	RBTree<int> tree(a);
	RBTree<long> tree2(b);
	tree.add(6);
	tree.add(5);

	/*RBIterator<int> it = tree.begin();
	for (it = tree.begin(); it != tree.end(); it++)
		std::cout << *it << " ";
	std::cout<< '\n';
	for (it = tree.begin(); it != tree.end(); ++it)
		std::cout << *it << " ";
*/
	tree.setDifference(a);
	//tree.print();
    tree.add(3);
	//tree.print();
	auto tree_3 = tree.setIntersection(tree2);


	//tree.print();
	tree_3.print();

}
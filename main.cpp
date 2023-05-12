#include "RBtree.hpp"

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <iterator>

int main()
{
	std::vector<int> a{ 2, 1, 3 };
	std::vector<int> b{ 3, 5, 4 };

	RBTree<int> tree(a);
	RBTree<long> tree2(b);

	std::cout << "constructed by vector 2 1 3\n";
	tree.print();
	std::cout << "\naddded to tree 5\n";
	tree.add(5);
	tree.print();

	std::cout << "\ndifference by vector 2 1 3\n";
	tree.setDifference(a).print();
	//tree.print();
	tree.add(3);
	//tree.print();
	std::cout << "\nintersection by tree2 : 3 5 4\n";
	auto tree_3 = tree.setIntersection(tree2);
	//tree.print();
	tree_3.print();

	std::cout << "\nremoving values 5 1 2\n";
	tree.remove(5);
	tree.remove(1);
	tree.remove(2);
	tree.print();
	std::cout << "\nremoving nonexistenst value 11\n";
	std::cout << "\nValues was successfully removed:" << tree.remove(11);

	std::cout << "\nadding existing values";
	std::cout << "\nValues was successfully added:" << tree.add(3);

	std::cout << "\n\nTesting iterators\n\n";
	std::cout << "iterators with std::advance\n";
	tree.add(1);
	tree = tree2;
	tree2.add(3);
	tree2.add(-23);
	tree2.add(123);
	tree2.print();

	std::cout << *tree2.begin();
	auto it = tree2.begin();
	std::advance(it, 2);
	std::cout << "\nadvance 2\n";
	std::cout << *it;
	std::cout << "\nsize of tree\n" << tree2.size();
	std::cout << "\n_____________________________________\n";
	std::cout << "\nCleared tree\n";
	tree.clear();
	tree.add(1);
	auto it_2 = tree.begin();
	it_2--;
	RBTree<int> t{ 1, 2, 3 };

	std::cout << "\nCreating tree by iterators\n";
	RBTree<int> temp(a.begin(), a.end());
	temp.add(10.123);
	temp.print();
	std::cout << "\b";
	std::cout << "\n creating tree with rvalue containers\n";
	RBTree<int> tr(std::vector<int>{ 5, 3, 3532 });

	std::cout << "\n";
	std::cout << "\n creating tree comparasent\n";
	t = RBTree<int>{ 3, 5 };
	std::cout << "f:";
	tr.print();
	std::cout << "\n";
	std::cout << "s:";
	t.print();
	std::cout << "\n";

	auto bl = (t < tr);
	std::cout << "f < s " << bl << "\n";
	std::cout << "f == f " << (t == t) << "\n";
	std::cout << "f == s " << (t == tr) << "\n";
	std::cout << "f != s " << (t != tr) << "\n";
	std::cout << "s >= f " << (tr >= t) << "\n";
	std::cout << "f > f " << (t > t) << "\n";
	std::cout << "f != empty tree " << (t != tree) << "\n";

	std::cout << "\n";
	std::cout << "\n creating tree intersections exc\n";
	t.add(54);

	std::cout << "f:";
	tr.print();
	std::cout << "\n";
	std::cout << "s:";
	t.print();
	std::cout << "\n";

	std::cout<< "\nf | s ";
	(t | tr).print();

	std::cout<< "\nf & s ";
	(t & tr).print();

	std::cout<< "\nf - s ";
	(t - tr).print();


	std::cout<< "\n(1 2 10) |= s ";
	temp |= tr;
	temp.print();

	std::cout<< "\n(1 2 10 {s}) &= s ";
	temp &= tr;
	temp.print();



}
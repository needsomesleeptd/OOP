#include "RBtree.hpp"
#include <iostream>
#include <algorithm>
#include <set>

int main()
{
	RBTree<int> tree;
	/*tree.add(2);
	tree.add(1);
	tree.add(3);
	auto  it = tree.begin();
	std:: cout<< *it;
	it++; //Find out why It is nullptr
	it++; //Find out why It is nullptr
	std:: cout<< *it;
	it--;
	std:: cout<< *it;
	++it;
	std:: cout<< *it;
	--it;
	std:: cout<< *it;
	std::cout<< "IsIn Check";
	std::cout<< tree.isIn(3);
	tree.remove(3);
	std::cout<< tree.isIn(3);
	std:: cout<<"REMOVED";
	it = tree.begin();
	std:: cout<< *it;
	it++; //Find out why It is nullptr
	std:: cout<< *it;
	it--;
	std:: cout<< *it;
	++it;
	std:: cout<< *it;
	--it;
	std:: cout<< *it;
	std::set s(tree.begin(),tree.end());*/
	tree.add(2);
	tree.add(1);
	tree.remove(3);
	auto  it = tree.begin();
	//std:: cout<< *it;
	//it--;
	std:: cout<< *it;
	++it;
	std:: cout<< *it;
	++it;





}
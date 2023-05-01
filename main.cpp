#include "RBtree.hpp"
#include <iostream>



int main()
{
	RBTree<int> tree;
	tree.add(2);
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
	tree.remove(3);
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




}
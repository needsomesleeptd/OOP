#ifndef _RB_TREE_
#define _RB_TREE_

#include "treeNode.h"
#include "Iset.h"

template <typename T>
class RBTree : ISet<T>
{
 private:
	NodePtr<T> root;
 public:
	void add(const T &data) override;
	void remove(const T &data) override;
	void clear() override;
	void find(const T &key) override;

	RBTree* set_Union(RBTree* other);
	RBTree* set_SymmDifference(RBTree* other);
	RBTree* set_Intersection(RBTree* other);


};




#endif _RB_TREE
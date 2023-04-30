#ifndef _RB_TREE_
#define _RB_TREE_

#include "treeNode.h"
#include "Iset.h"
#include "Iterator.hpp"

template <typename T>
class RBTree : ISet<T>
{
 private:
	NodePtr<T> root;
	friend class RBIterator<T>;
 protected:
	void rotateRight(NodePtr<T> node);
	void rotateLeft(NodePtr<T> node);
	NodePtr<T> search(const T& key);
	NodePtr<T> insertBin(NodePtr<T> root, NodePtr<T> nodeToInsert);
	void setColor(NodePtr<T> node, int color);
	void RBTreeFixInsert(NodePtr<T> insertedNode);



 public:

	RBTree();
	~RBTree() override;

	void add(const T &data) override;
	void remove(const T &data) override;
	void clear() override;
	void find(const T &key) override;

	void set_union(ISet<T>* other);
	void set_symmDifference(ISet<T>* other);
	void set_intersection(ISet<T>* other);

};





#endif _RB_TREE_
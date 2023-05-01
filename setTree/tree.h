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
	NodePtr<T> findMin(const NodePtr<T> &root) const;
	void RBTreeFixInsert(NodePtr<T> insertedNode);
	void RBTreeFixRemove(NodePtr<T> node);
	NodePtr<T> insertBin(NodePtr<T> root, NodePtr<T> nodeToInsert);
	NodePtr<T> removeBin(NodePtr<T> root, const T& key);

	void setColor(NodePtr<T> node, NodeColor color);
	NodeColor getColor(NodePtr<T> node);






 public:

	RBTree();
	~RBTree() override;

	void add(const T &data) override;
	void remove(const T &data) override;
	void clear() override;
	void find(const T &key) override;

	RBIterator<T> begin();
	RBIterator<T> end();



	void set_union(ISet<T>* other);
	void set_symmDifference(ISet<T>* other);
	void set_intersection(ISet<T>* other);


};





#endif //_RB_TREE_
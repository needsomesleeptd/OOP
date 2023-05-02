#ifndef _RB_TREE_
#define _RB_TREE_

#include "treeNode.h"
#include "Iset.h"
#include "Iterator.hpp"
#include "concepts.h"

template<ValidNodeData T>

class RBTree : ISet<T>
{
 private:
	NodePtr<T> root_;
	friend class RBIterator<T>;
 protected:
	void rotateRight(NodePtr<T> node);
	void rotateLeft(NodePtr<T> node);
	NodePtr<T> findMin(const NodePtr<T>& root) const;
	void RBTreeFixInsert(NodePtr<T> insertedNode);
	void RBTreeFixRemove(NodePtr<T> node);
	NodePtr<T> find(NodePtr<T> root, const T& key) const;
	NodePtr<T> insertBin(NodePtr<T> root, NodePtr<T> nodeToInsert);
	NodePtr<T> removeBin(NodePtr<T> root, const T& key);

	void setColor(NodePtr<T> node, NodeColor color);
	NodeColor getColor(NodePtr<T> node);

 public:

	using value_type = T;
	using size_type = size_t;
	using iterator = RBIterator<T>;
	using const_iterator = const RBIterator<T>;

	explicit RBTree();

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	explicit RBTree(const ContainerType& container);



	~RBTree() override;

	bool add(const T& data) override;
	bool remove(const T& data) override;
	void clear() override;
	bool contains(const T& key) override;

	RBIterator<T> begin() noexcept;
	RBIterator<T> end() noexcept;


	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	void setUnion(const ContainerType& container);

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	void setDifference(const ContainerType& container);

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	void setSymmDifference(const ContainerType& container);

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	void setIntersection(const ContainerType& container);

	void  print();

};

#endif //_RB_TREE_
#ifndef _RB_TREE_
#define _RB_TREE_

#include "treeNode.h"
#include "Iset.h"
#include "Iterator.hpp"
#include "concepts.h"

template<ValidNodeData T>

class RBTree : ISet<T>
{

 public:

	using value_type = T;
	using size_type = size_t;
	using iterator = RBIterator<T>;
	using const_iterator = const RBIterator<T>;

	RBTree();
	explicit RBTree(const RBTree& other);

	explicit RBTree(RBTree&& other) noexcept;

	explicit RBTree(std::initializer_list<T> l);

	template<std::input_iterator IteratorType>
	requires Convertible<typename IteratorType::value_type, T>
	RBTree(IteratorType begin, IteratorType end);

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	explicit RBTree(const ContainerType& container);

	~RBTree() override;

	template<ValidNodeData O>
	requires Convertible<O, T>
	bool add(const O& data);

	template<ValidNodeData O>
	requires Convertible<O, T>
	bool remove(const O& data);

	void clear() override;

	template<ValidNodeData O>
	requires Convertible<O, T>
	bool contains(const O& key);

	size_type size() const noexcept;

	RBIterator<T> begin() const noexcept;
	RBIterator<T> end() const noexcept;

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	RBTree setUnion(const ContainerType& container);

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	RBTree setDifference(const ContainerType& container);

	/*template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	RBTree setSymmDifference(const ContainerType& container);*/

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	RBTree setIntersection(const ContainerType& container);

	template<Container ContainerType>
	requires Convertible<typename ContainerType::value_type, T>
	explicit RBTree(ContainerType&& container) noexcept;

	template<ValidNodeData O>
	requires Convertible<O, T>
	RBTree& operator=(const RBTree<O>& other); // copy

	RBTree& operator=(const RBTree& other); // copy


	RBTree& operator=(RBTree&& other) noexcept; // move

	template<ValidNodeData O>
	requires Convertible<O, T>
	RBTree& operator=(RBTree<O>&& other) noexcept; // move

	void print();

 protected:
	void rotateRight(NodePtr<T> node);
	void rotateLeft(NodePtr<T> node);
	NodePtr<T> findMin(const NodePtr<T>& root) const;
	void RBTreeFixInsert(NodePtr<T> insertedNode);
	void RBTreeFixRemove(NodePtr<T> node);
	NodePtr<T> find(NodePtr<T> root, const T& key) const;
	NodePtr<T> insertBin(NodePtr<T> root, NodePtr<T> nodeToInsert);
	NodePtr<T> removeBin(NodePtr<T> root, const T& key);

 private:
	NodePtr<T> root_;
	friend class RBIterator<T>;
	size_t size_;


};

#endif //_RB_TREE_
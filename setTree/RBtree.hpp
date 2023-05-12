#ifndef TREE_HPP_
#define TREE_HPP_

#include <iostream>
#include <compare>
#include <type_traits>
#include "tree.h"

template<ValidNodeData T>
NodeColor getColor(NodePtr<T> node)
{
	if (node == nullptr)
		return BLACK;
	return node->getColor();
}

template<ValidNodeData T>
void setColor(NodePtr<T> node, NodeColor color)
{
	if (node == nullptr)
		return;

	node->setColor(color);
}

template<ValidNodeData T>
RBTree<T>::RBTree() : size_(0), root_(nullptr)
{

}

template<ValidNodeData T>
RBTree<T>::RBTree(const RBTree& other)
{
	size_ = 0;
	for (auto& elem : other)
		this->add(elem);
}

template<ValidNodeData T>
RBTree<T>::RBTree(RBTree&& other) noexcept
{
	this->root_ = std::move(other.root_);
	this->size_ = std::move(other.size_);
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
RBTree<T>& RBTree<T>::operator=(const RBTree<O>& other) // copy
{
	this->clear();
	for (auto& elem : other)
		this->add(elem);
	return *this;
}

template<ValidNodeData T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& other) // copy
{
	this->clear();
	for (auto& elem : other)
		this->add(elem);
	return *this;
}

template<ValidNodeData T>
RBTree<T>& RBTree<T>::operator=(RBTree&& other) noexcept // move
{
	this->clear();
	this->root_ = std::move(other.root_);
	this->size_ = std::move(other.size_);
	return *this;
}

template<ValidNodeData T>
RBTree<T>::~RBTree()
{
	if (root_ != nullptr)
		root_->clear_subtree();
	root_ = nullptr;
}

template<ValidNodeData T>
void RBTree<T>::clear()
{
	size_ = 0;
	root_.reset();
}

template<ValidNodeData T>
NodePtr<T> RBTree<T>::findMin(const NodePtr<T>& root) const
{
	if (root == nullptr)
		return root;
	NodePtr<T> temp = root;
	while (temp->left() != nullptr)
		temp = temp->left();
	return temp;
}

template<ValidNodeData T>
RBIterator<T> RBTree<T>::begin() const noexcept
{
	return RBIterator<T>(findMin(root_));
}

template<ValidNodeData T>
RBIterator<T> RBTree<T>::end() const noexcept
{
	return RBIterator<T>(nullptr);
}

template<ValidNodeData T>
void RBTree<T>::rotateLeft(NodePtr<T> node)
{
	NodePtr<T> x = node;
	NodePtr<T> y = x->right();
	x->right() = y->left();
	if (y->left() != nullptr)
	{
		y->left()->parent() = x;
	}
	y->parent() = x->parent();
	if (x->parent().lock() == nullptr)
	{
		root_ = y;
	}
	else if (x == x->parent().lock()->left())
	{
		x->parent().lock()->left() = y;
	}
	else
	{
		x->parent().lock()->right() = y;
	}
	y->left() = x;
	x->parent() = y;

}

template<ValidNodeData T>
void RBTree<T>::rotateRight(NodePtr<T> node)
{
	NodePtr<T> y = node;
	NodePtr<T> x = y->left();
	y->left() = x->right();
	if (x->right() != nullptr)
		x->right()->parent() = y;

	x->parent() = y->parent();
	if (y->parent().lock() == nullptr)
		root_ = x;
	else
	{
		if (y == y->parent().lock()->right())
			y->parent().lock()->right() = x;
		else
			y->parent().lock()->left() = x;
	}
	x->right() = y;
	y->parent() = x;
}

/*template<ValidNodeData T>
NodePtr<T> RBTree<T>::insertBin(NodePtr<T> root_, NodePtr<T> nodeToInsert)
{
	if (root_ == nullptr)
		return nodeToInsert;
	while (nodeToInsert != root_ && nodeToInsert->parent().lock()->color_== RED)
	{
		NodePtr<T> parent = nodeToInsert->parent().lock();
		NodePtr<T> grandParent = parent->parent().lock();
		if (parent == grandParent->left())
		{
			NodePtr<T> uncle = grandParent->right();
			if (uncle->color_ == RED)
			{
				parent->color_ = BLACK;
				uncle->color_ = BLACK;
				grandParent->color_ = RED;
				nodeToInsert = grandParent;
			}
			else if (nodeToInsert == parent->right())
			{
				nodeToInsert = parent;
				rotateLeft(nodeToInsert);
			}
			parent->color_ = BLACK;
			grandParent->color_ = RED;
			rotateRight(grandParent);
		}
		else
		{
			NodePtr<T> uncle = grandParent->left();
			if (uncle->color_ == RED)
			{
				parent->color_ = BLACK;
				uncle->color_ = BLACK;
				grandParent->color_ = RED;
				nodeToInsert = grandParent;
			}
			else if (nodeToInsert == parent->left())
			{
				nodeToInsert = parent;
				rotateLeft(nodeToInsert);
			}
			parent->color_ = BLACK;
			grandParent->color_ = RED;
			rotateRight(grandParent);
		}
	}
	root_->color_ = BLACK;
	return root_;

}*/

template<ValidNodeData T>
NodePtr<T> RBTree<T>::insertBin(NodePtr<T> root, NodePtr<T> nodeToInsert)
{
	if (root == nullptr)
		return nodeToInsert;

	if (nodeToInsert->data() > root->data())
	{
		root->right() = insertBin(root->right(), nodeToInsert);
		root->right()->parent() = root;
	}
	else if (nodeToInsert->data() < root->data())
	{
		root->left() = insertBin(root->left(), nodeToInsert);
		root->left()->parent() = root;
	}
	else
	{
		return nullptr;
	}
	return root;

}

template<ValidNodeData T>
void RBTree<T>::RBTreeFixInsert(NodePtr<T> insertedNode)
{

	NodePtr<T> parent = nullptr;
	NodePtr<T> grandparent = nullptr;
	while (insertedNode != root_ && getColor(insertedNode) == RED && getColor(insertedNode->parent().lock()) == RED)
	{
		parent = insertedNode->parent().lock();
		grandparent = parent->parent().lock();
		if (parent == grandparent->left())
		{
			NodePtr<T> uncle = grandparent->right();
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				insertedNode = grandparent;
			}
			else
			{
				if (insertedNode == parent->right())
				{
					rotateLeft(parent);
					insertedNode = parent;
					parent = insertedNode->parent().lock();
				}
				rotateRight(grandparent);
				parent->setColor(grandparent->getColor());
				grandparent->setColor(parent->getColor());
				insertedNode = parent;
			}
		}
		else
		{
			NodePtr<T> uncle = grandparent->left();
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				insertedNode = grandparent;
			}
			else
			{
				if (insertedNode == parent->left())
				{
					rotateRight(parent);
					insertedNode = parent;
					parent = insertedNode->parent().lock();
				}
				rotateLeft(grandparent);
				parent->setColor(grandparent->getColor());
				grandparent->setColor(parent->getColor());
				insertedNode = parent;
			}
		}
	}
	setColor(root_, BLACK);
}

template<ValidNodeData T>
void RBTree<T>::RBTreeFixRemove(NodePtr<T> node)
{
	if (node == nullptr)
		return;

	if (node == root_)
	{
		if (root_->right())
		{
			root_->right()->parent() = Node<T>::create();
			root_ = root_->right();
		}
		else if (root_->left())
		{
			root_->left()->parent() = Node<T>::create();
			root_ = root_->left();
		}
		else
		{
			root_ = nullptr;
		}
		return;
	}

	if (getColor(node) == RED || getColor(node->left()) == RED || getColor(node->right()) == RED)
	{
		NodePtr<T> child = node->left() != nullptr ? node->left() : node->right();

		if (node == node->parent().lock()->left())
		{
			node->parent().lock()->left() = child;
			if (child != nullptr)
				child->parent().lock() = node->parent().lock();
			setColor(child, BLACK);
		}
		else
		{
			node->parent().lock()->right() = child;
			if (child != nullptr)
				child->parent().lock() = node->parent().lock();
			setColor(child, BLACK);
		}
	}
	else
	{
		NodePtr<T> sibling = Node<T>::create();
		NodePtr<T> parent = Node<T>::create();
		NodePtr<T> ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root_ && getColor(ptr) == DOUBLE_BLACK)
		{
			parent = ptr->parent().lock();
			if (ptr == parent->left() && parent->right())
			{
				sibling = parent->right();
				if (getColor(sibling) == RED)
				{
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				}
				else
				{
					if (getColor(sibling->left()) == BLACK && getColor(sibling->right()) == BLACK)
					{
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else
					{
						if (getColor(sibling->right()) == BLACK)
						{
							setColor(sibling->left(), BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right();
						}
						setColor(sibling, parent->getColor());
						setColor(parent, BLACK);
						setColor(sibling->right(), BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else
			{
				sibling = parent->left();
				if (getColor(sibling) == RED)
				{
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else
				{
					if (getColor(sibling->left()) == BLACK && getColor(sibling->right()) == BLACK)
					{
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						else
							setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else
					{
						if (getColor(sibling->left()) == BLACK)
						{
							setColor(sibling->right(), BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left();
						}
						setColor(sibling, parent->getColor());
						setColor(parent, BLACK);
						setColor(sibling->left(), BLACK);
						rotateRight(parent);
					}
				}
			}
		}
		if (node == node->parent().lock()->left())
			node->parent().lock()->left() = Node<T>::create();
		else
			node->parent().lock()->right() = Node<T>::create();
		setColor(root_, BLACK);
	}
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::add(const O& data)
{
	if (contains(data))
		return false;
	try
	{
		NodePtr<T> node = Node<T>::create(data);
		root_ = insertBin(root_, node);
		//RBTreeFixInsert(node);
	}
	catch (std::bad_alloc)
	{
		time_t timer = time(nullptr);
		throw MemoryException(__FILE__, __LINE__, "RBtree<T>", ctime(&timer));
	}

	++size_;

	return true;
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::add(O&& data)
{
	if (contains(data))
		return false;
	try
	{
		NodePtr<T> node = Node<T>::create(data);
		root_ = insertBin(root_, node);
		//RBTreeFixInsert(node);
	}
	catch (std::bad_alloc)
	{
		time_t timer = time(nullptr);
		throw MemoryException(__FILE__, __LINE__, "RBtree<T>", ctime(&timer));
	}

	++size_;

	return true;
}

template<ValidNodeData T>
NodePtr<T> RBTree<T>::removeBin(NodePtr<T> root, const T& key)
{
	if (root == nullptr)
		return nullptr;

	if (key < root->data())
		return removeBin(root->left(), key);

	if (key > root->data())
		return removeBin(root->right(), key);

	if (root->left() == nullptr || root->right() == nullptr)
		return root;

	NodePtr<T> temp = findMin(root->right());
	root->data() = temp->data();
	return removeBin(root->right(), temp->data());
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::remove(const O& data)
{
	if (!contains(data))
		return false;
	NodePtr<T> node = removeBin(root_, data);


	--size_;
	RBTreeFixRemove(node);
	return true;
}





template<ValidNodeData T>
NodePtr<T> RBTree<T>::find(NodePtr<T> root, const T& key) const
{
	if (root == nullptr)
		return root;

	if (root->data() > key)
		return find(root->left(), key);

	if (root->data() < key)
		return find(root->right(), key);

	return root;
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::contains(const O& key) const
{
	return find(root_, key) != nullptr;
}

template<ValidNodeData T>
void RBTree<T>::print()
{
	for (auto it = begin(); it != end(); ++it)
		std::cout << *it << " ";
}

template<ValidNodeData T>
size_t RBTree<T>::size() const noexcept
{
	return size_;
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setUnion(const ContainerType& other) const
{
	RBTree<T> result;

	for (auto it = other.begin(); it != other.end(); it++)
		result.add(*it);
	for (auto it = this->begin(); it != this->end(); it++)
		result.add(*it);
	return RBTree(result);

}

/*template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setSymmDifference(const ContainerType& other)
{

	this->setDifference(other);
	this->setDifference(this);

}*/

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setDifference(const ContainerType& other) const
{
	RBTree<T> result;
	result = *this;
	for (auto it = other.begin(); it != other.end(); it++)
		if (result.contains(*it))
			result.remove(*it);
	return RBTree<T>(result);

}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setIntersection(const ContainerType& other) const
{
	RBTree<T> result;

	for (auto elem : other)
		if (this->contains(elem))
			result.add(elem);

	return RBTree<T>(result);
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T>::RBTree(const ContainerType& container)
{
	this->size_ = 0;
	for (typename ContainerType::const_iterator it = container.begin(); it != container.end(); it++)
		this->add(*it);
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T>::RBTree(ContainerType&& container) noexcept
{
	this->size_ = 0;
	for (typename ContainerType::const_iterator it = container.begin(); it != container.end(); it++)
		this->add(std::move(*it));
}

template<ValidNodeData T>
RBTree<T>::RBTree(std::initializer_list<T> l)
{
	this->size_ = 0;
	for (auto elem : l)
		add(elem);
}

template<ValidNodeData T>
template<std::input_iterator IteratorType>
requires Convertible<typename IteratorType::value_type, T>
RBTree<T>::RBTree(IteratorType begin, IteratorType end)
{
	this->size_ = 0;
	for (auto it = begin; it != end; it++)
		add(*it);
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
RBTree<T>& RBTree<T>::operator=(RBTree<O>&& other) noexcept
{
	this->clear();
	this->root_ = std::move(other.root_);
	this->size_ = std::move(other.size_);
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::is_subset(const RBTree<O>& other) const
{
	for (auto it = begin(); it != end(); it++)
		if (!other.contains(*it))
			return false;
	return true;
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::is_upperset(const RBTree<O>& other) const
{
	if (!other.is_subset(*this))
		return false;
	return true;
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::operator<(const RBTree<O>& other)
{
	if (this->is_subset(other) && !this->is_upperset(other))
		return true;
	return false;
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
bool RBTree<T>::operator==(const RBTree<O>& other) const
{
	if (this->is_subset(other) && this->is_upperset(other))
		return true;
	return false;
}

template<ValidNodeData T>
bool RBTree<T>::operator<(const RBTree<T>& other)
{
	if (this->is_subset(other) && !this->is_upperset(other))
		return true;
	return false;
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
std::strong_ordering RBTree<T>::operator<=>(const RBTree<O>& other) const
{
	bool is_upper = other.is_subset(*this);
	bool is_subset = other.is_upperset(*this);
	if (is_upper && is_subset)
		return std::strong_ordering::equivalent;
	else if (is_upper)
		return std::strong_ordering::greater;
	else
		return std::strong_ordering::less;
}

template<ValidNodeData T>
std::strong_ordering RBTree<T>::operator<=>(const RBTree<T>& other) const
{
	bool is_upper = other.is_subset(*this);
	bool is_subset = other.is_upperset(*this);
	if (is_upper && is_subset)
		return std::strong_ordering::equivalent;
	else if (is_upper)
		return std::strong_ordering::greater;
	else
		return std::strong_ordering::less;
}
template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::operator|(const ContainerType& other) const
{
	return this->setUnion(other);
}
template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
void RBTree<T>::operator|=(const ContainerType& other)
{
	*this = this->setUnion(other);
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::operator&(const ContainerType& other) const
{
	return this->setIntersection(other);
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
void RBTree<T>::operator&=(const ContainerType& other)
{
	*this = this->setIntersection(other);
}
template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::operator-(const ContainerType& other) const
{
	return this->setDifference(other);
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
void RBTree<T>::operator-=(const ContainerType& other)
{
	*this = this->setDifference(other);
}


template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::operator+(const ContainerType& other) const
{
	return this->setUnion(other);
}
template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
void RBTree<T>::operator+=(const ContainerType& other)
{
	*this = this->setUnion(other);
}

#endif //TREE_HPP_
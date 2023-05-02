#ifndef TREE_HPP_
#define TREE_HPP_

#include <iostream>

#include "tree.h"

template<ValidNodeData T>
RBTree<T>::RBTree() : root_(nullptr),size_(0)
{

}

template<ValidNodeData T>
RBTree<T>::RBTree(const RBTree &other)
{
	for (auto &elem: other)
		this->add(elem);
}

template<ValidNodeData T>
RBTree<T>::RBTree(const RBTree &&other)
{
	this->root_ = std::move(other.root_);
	this->size_ = std::move(other.size_);
}

template<ValidNodeData T>
template<ValidNodeData O>
requires Convertible<O, T>
RBTree<T> &RBTree<T>::operator=(const RBTree<O> &other) // copy
{
	this->clear();
	for (auto &elem: other)
		this->add(elem);
	return *this;
}

template<ValidNodeData T>
RBTree<T> &RBTree<T>::operator=(const RBTree<T> &other) // copy
{
	this->clear();
	for (auto &elem: other)
		this->add(elem);
	return *this;
}

template<ValidNodeData T>

RBTree<T> &RBTree<T>::operator=(const  RBTree &&other) noexcept // move
{
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
	if (root_ != nullptr)
		root_->clear_subtree();
	root_ = nullptr;
}

template<ValidNodeData T>
NodePtr<T> RBTree<T>::findMin(const NodePtr<T>& root) const
{
	if (root == nullptr)
		return root;
	NodePtr<T> temp = root;
	while (temp->left_ != nullptr)
		temp = temp->left_;
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
	NodePtr<T> y = x->right_;
	x->right_ = y->left_;
	if (y->left_ != nullptr)
	{
		y->left_->parent_ = x;
	}
	y->parent_ = x->parent_;
	if (x->parent_.lock() == nullptr)
	{
		root_ = y;
	}
	else if (x == x->parent_.lock()->left_)
	{
		x->parent_.lock()->left_ = y;
	}
	else
	{
		x->parent_.lock()->right_ = y;
	}
	y->left_ = x;
	x->parent_ = y;

}

template<ValidNodeData T>
void RBTree<T>::rotateRight(NodePtr<T> node)
{
	NodePtr<T> y = node;
	NodePtr<T> x = y->left_;
	y->left_ = x->right_;
	if (x->right_ != nullptr)
		x->right_->parent_ = y;

	x->parent_ = y->parent_;
	if (y->parent_.lock() == nullptr)
		root_ = x;
	else
	{
		if (y == y->parent_.lock()->right_)
			y->parent_.lock()->right_ = x;
		else
			y->parent_.lock()->left_ = x;
	}
	x->right_ = y;
	y->parent_ = x;
}

/*template<ValidNodeData T>
NodePtr<T> RBTree<T>::insertBin(NodePtr<T> root_, NodePtr<T> nodeToInsert)
{
	if (root_ == nullptr)
		return nodeToInsert;
	while (nodeToInsert != root_ && nodeToInsert->parent_.lock()->color_== RED)
	{
		NodePtr<T> parent = nodeToInsert->parent_.lock();
		NodePtr<T> grandParent = parent->parent_.lock();
		if (parent == grandParent->left_)
		{
			NodePtr<T> uncle = grandParent->right_;
			if (uncle->color_ == RED)
			{
				parent->color_ = BLACK;
				uncle->color_ = BLACK;
				grandParent->color_ = RED;
				nodeToInsert = grandParent;
			}
			else if (nodeToInsert == parent->right_)
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
			NodePtr<T> uncle = grandParent->left_;
			if (uncle->color_ == RED)
			{
				parent->color_ = BLACK;
				uncle->color_ = BLACK;
				grandParent->color_ = RED;
				nodeToInsert = grandParent;
			}
			else if (nodeToInsert == parent->left_)
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

	if (nodeToInsert->data_ > root->data_)
	{
		root->right_ = insertBin(root->right_, nodeToInsert);
		root->right_->parent_ = root;
	}
	else if (nodeToInsert->data_ < root->data_)
	{
		root->left_ = insertBin(root->left_, nodeToInsert);
		root->left_->parent_ = root;
	}
	else
	{
		time_t timer = time(nullptr);
		throw AddException(__FILE__, __LINE__, "RBtree<T>", ctime(&timer));
	}
	return root;

}

template<ValidNodeData T>
void RBTree<T>::setColor(NodePtr<T> node, NodeColor color)
{
	if (node == nullptr)
		return;

	node->color_ = color;
}

template<ValidNodeData T>
NodeColor RBTree<T>::getColor(NodePtr<T> node)
{
	if (node == nullptr)
		return BLACK;
	return node->color_;
}

template<ValidNodeData T>
void RBTree<T>::RBTreeFixInsert(NodePtr<T> insertedNode)
{

	NodePtr<T> parent = nullptr;
	NodePtr<T> grandparent = nullptr;
	while (insertedNode != root_ && getColor(insertedNode) == RED && getColor(insertedNode->parent_.lock()) == RED)
	{
		parent = insertedNode->parent_.lock();
		grandparent = parent->parent_.lock();
		if (parent == grandparent->left_)
		{
			NodePtr<T> uncle = grandparent->right_;
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				insertedNode = grandparent;
			}
			else
			{
				if (insertedNode == parent->right_)
				{
					rotateLeft(parent);
					insertedNode = parent;
					parent = insertedNode->parent_.lock();
				}
				rotateRight(grandparent);
				std::swap(parent->color_, grandparent->color_);
				insertedNode = parent;
			}
		}
		else
		{
			NodePtr<T> uncle = grandparent->left_;
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				insertedNode = grandparent;
			}
			else
			{
				if (insertedNode == parent->left_)
				{
					rotateRight(parent);
					insertedNode = parent;
					parent = insertedNode->parent_.lock();
				}
				rotateLeft(grandparent);
				std::swap(parent->color_, grandparent->color_);
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
		if (root_->right_)
		{
			root_->right_->parent_ = NodePtr<T>(nullptr);
			root_ = root_->right_;
		}
		else if (root_->left_)
		{
			root_->left_->parent_ = NodePtr<T>(nullptr);
			root_ = root_->left_;
		}
		else
		{
			root_ = nullptr;
		}
		return;
	}

	if (getColor(node) == RED || getColor(node->left_) == RED || getColor(node->right_) == RED)
	{
		NodePtr<T> child = node->left_ != nullptr ? node->left_ : node->right_;

		if (node == node->parent_.lock()->left_)
		{
			node->parent_.lock()->left_ = child;
			if (child != nullptr)
				child->parent_.lock() = node->parent_.lock();
			setColor(child, BLACK);
		}
		else
		{
			node->parent_.lock()->right_ = child;
			if (child != nullptr)
				child->parent_.lock() = node->parent_.lock();
			setColor(child, BLACK);
		}
	}
	else
	{
		NodePtr<T> sibling = nullptr;
		NodePtr<T> parent = nullptr;
		NodePtr<T> ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root_ && getColor(ptr) == DOUBLE_BLACK)
		{
			parent = ptr->parent_.lock();
			if (ptr == parent->left_)
			{
				sibling = parent->right_;
				if (getColor(sibling) == RED)
				{
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				}
				else
				{
					if (getColor(sibling->left_) == BLACK && getColor(sibling->right_) == BLACK)
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
						if (getColor(sibling->right_) == BLACK)
						{
							setColor(sibling->left_, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right_;
						}
						setColor(sibling, parent->color_);
						setColor(parent, BLACK);
						setColor(sibling->right_, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else
			{
				sibling = parent->left_;
				if (getColor(sibling) == RED)
				{
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else
				{
					if (getColor(sibling->left_) == BLACK && getColor(sibling->right_) == BLACK)
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
						if (getColor(sibling->left_) == BLACK)
						{
							setColor(sibling->right_, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left_;
						}
						setColor(sibling, parent->color_);
						setColor(parent, BLACK);
						setColor(sibling->left_, BLACK);
						rotateRight(parent);
					}
				}
			}
		}
		if (node == node->parent_.lock()->left_)
			node->parent_.lock()->left_ = nullptr;
		else
			node->parent_.lock()->right_ = nullptr;
		setColor(root_, BLACK);
	}
}

template<ValidNodeData T>
bool RBTree<T>::add(const T& data)
{
	NodePtr<T> node = std::make_shared<Node<T>>(data);
	try
	{
		root_ = insertBin(root_, node);
	}
	catch (const AddException exception)
	{
		return false;
	}
	++size_;
	RBTreeFixInsert(node);
	return true;
}

template<ValidNodeData T>
NodePtr<T> RBTree<T>::removeBin(NodePtr<T> root, const T& key)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (key < root->data_)
		return removeBin(root->left_, key);

	if (key > root->data_)
		return removeBin(root->right_, key);

	if (root->left_ == nullptr || root->right_ == nullptr)
		return root;

	NodePtr<T> temp = findMin(root->right_);
	root->data_ = temp->data_;
	return removeBin(root->right_, temp->data_);
}

template<ValidNodeData T>
bool RBTree<T>::remove(const T& data)
{
	NodePtr<T> node;
	if (contains(data))
		return false;
	node = removeBin(root_, data);
	--size_;
	RBTreeFixRemove(node);
	return true;
}

template<ValidNodeData T>
NodePtr<T> RBTree<T>::find(NodePtr<T> root, const T& key) const
{
	if (root == nullptr)
		return root;

	if (root->data_ > key)
		return find(root->left_, key);

	if (root->data_ < key)
		return find(root->right_, key);

	return root;
}

template<ValidNodeData T>
bool RBTree<T>::contains(const T& key)
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
RBTree<T> RBTree<T>::setUnion(const ContainerType& other)
{
	RBTree<T> result;

	for (auto it = other.begin(); it != other.end(); it++)
		result.add(*it);
	for (auto it = this->begin(); it != this->end(); it++)
		result.add(*it);
	return result;

}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setSymmDifference(const ContainerType& other)
{

	this->setDifference(other);
	this->setDifference(this);

}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setDifference(const ContainerType& other)
{
	RBTree<T> result;
	result = *this;
	for (auto it = other.begin(); it != other.end(); it++)
		if (result.contains(*it))
			result.remove(*it);
	return result;

}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T> RBTree<T>::setIntersection(const ContainerType& other)
{
	RBTree<T> result;

	for (auto elem: other)
		if (this->contains(elem))
			result.add(elem);


	return result;
}

template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T>::RBTree(const ContainerType& container)
{
	for (typename ContainerType::const_iterator it = container.begin(); it != container.end(); it++)
		this->add(*it);
}

#endif //TREE_HPP_
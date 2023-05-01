#ifndef TREE_HPP_
#define TREE_HPP_

#include <iostream>

#include "tree.h"

template<ValidNodeData T>
RBTree<T>::RBTree() : root()
{
};

template<ValidNodeData T>
RBTree<T>::~RBTree()
{
	root->clear_subtree();
}

template<ValidNodeData T>
void RBTree<T>::clear()
{
	root->clear_subtree();
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
RBIterator<T> RBTree<T>::begin() noexcept
{
	return RBIterator<T>(findMin(root));
}

template<ValidNodeData T>
RBIterator<T> RBTree<T>::end() noexcept
{
	return RBIterator<T>(nullptr);
}

template<ValidNodeData T>
void RBTree<T>::rotateLeft(NodePtr<T> node)
{
	NodePtr<T> pivot = node->right_;
	pivot->parent_ = node->parent_;
	if (node->parent_.lock() != nullptr)
	{
		if (node->parent_.lock()->left_ == node)
			node->parent_.lock()->left_ = pivot;
		else
			node->parent_.lock()->right_ = pivot;
	}

	node->right_ = pivot->left_;
	if (pivot->left_ != nullptr)
		pivot->left_->parent_ = node;

	node->parent_ = pivot;
	pivot->left_ = node;

};

template<ValidNodeData T>
void RBTree<T>::rotateRight(NodePtr<T> node)
{
	NodePtr<T> pivot = node->left_;

	pivot->parent_ = node->parent_;
	if (node->parent_.lock())
	{
		if (node->parent_.lock()->left_ == node)
			node->parent_.lock()->left_ = pivot;
		else
			node->parent_.lock()->right_ = pivot;
	}

	node->left_ = pivot->right_;
	if (pivot->right_ != nullptr)
		pivot->right_->parent_ = node;

	node->parent_ = pivot;
	pivot->right_ = node;
};

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
	while (insertedNode != root && getColor(insertedNode) == RED && getColor(insertedNode->parent_.lock()) == RED)
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
	setColor(root, BLACK);
}

template<ValidNodeData T>
void RBTree<T>::RBTreeFixRemove(NodePtr<T> node)
{
	if (node == nullptr)
		return;

	if (node == root)
	{
		root = nullptr;
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
		while (ptr != root && getColor(ptr) == DOUBLE_BLACK)
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
		setColor(root, BLACK);
	}
}

template<ValidNodeData T>
void RBTree<T>::add(const T& data)
{
	NodePtr<T> node = std::make_shared<Node<T>>(data);
	root = insertBin(root, node);
	RBTreeFixInsert(node);
}

template<ValidNodeData T>
NodePtr<T> RBTree<T>::removeBin(NodePtr<T> root, const T& key)
{
	if (root == nullptr)
		return root;

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
void RBTree<T>::remove(const T& data)
{
	NodePtr<T> node = removeBin(root, data);

	if (root != nullptr)
	{
		time_t timer = time(nullptr);
		throw RemoveException(__FILE__, __LINE__, "RBtree<T>", ctime(&timer));
	}

	RBTreeFixRemove(node);
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
bool RBTree<T>::isIn(const T& key)
{
	return find(root, key) != nullptr;
}

template<ValidNodeData T>
void  RBTree<T>::print()
{
	for (auto it = begin();it != end();++it)
		std::cout<< *it << " ";
}




template<ValidNodeData T>
void RBTree<T>::set_union(ISet<T>* other)
{

}
template<ValidNodeData T>
void RBTree<T>::set_symmDifference(ISet<T>* other)
{
	// TODO::Implement this
}
template<ValidNodeData T>
void RBTree<T>::set_intersection(ISet<T>* other)
{
	// TODO::Implement this
}




template<ValidNodeData T>
template<Container ContainerType>
requires Convertible<typename ContainerType::value_type, T>
RBTree<T>::RBTree(const ContainerType& container)
{
	for (auto it = container.begin(); it != container.end();it++)
		this->add(*it);
}

#endif //TREE_HPP_
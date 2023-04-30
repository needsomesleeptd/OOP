#ifndef TREE_HPP_
#define TREE_HPP_

#include "tree.h"


template<typename T>
RBTree<T>::RBTree() : root()
{
};


template<typename T>
void RBTree<T>::rotateLeft(NodePtr<T> node)
{
	Node<T> pivot = node->right_;
	pivot->parent_ = node->parent_;
	if (node->parent_ != nullptr)
	{
		if (node->parent_->left_ == node)
			node->parent_->left_ = pivot;
		else
			node->parent_->right_ = pivot;
	}

	node->right_ = pivot->left_;
	if (pivot->left_ != nullptr)
		pivot->left_->parent_ = node;

	node->parent_ = pivot;
	pivot->left_ = node;

};

template<typename T>
void RBTree<T>::rotateRight(NodePtr<T> node)
{
	struct node* pivot = node->left;

	pivot->parent = node->parent;
	if (node->parent != NULL)
	{
		if (node->parent->left == node)
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}

	node->left = pivot->right;
	if (pivot->right != NULL)
		pivot->right->parent = node;

	node->parent = pivot;
	pivot->right = node;
};

template<typename T>
NodePtr<T> RBTree<T>::insertBin(NodePtr<T> root, NodePtr<T> nodeToInsert)
{
	if (root == nullptr)
		return nodeToInsert;
	if (nodeToInsert->data_ > root->data_)
		root->right_ = insertBin(root->right_, nodeToInsert);
	else if (nodeToInsert->data_ > root->data_)
		root->left_ = insertBin(root->left_, nodeToInsert);
	/*
	 * Todo::Implement Error throwing
	 */
}

template<typename T>
void RBTree<T>::setColor(NodePtr<T> node, int color)
{
	if (node == nullptr)
		return;

	node->color = color;
}

template<typename T>
NodeColor RBTree<T>::getColor(NodePtr<T> node)
{

	return node->color_;
}


template<typename T>
void RBTree<T>::RBTreeFixInsert(NodePtr<T> insertedNode)
{

	NodePtr<T> parent = nullptr;
	NodePtr<T> grandparent = nullptr;
	while (insertedNode != root && getColor(insertedNode) == RED && getColor(*insertedNode->parent_) == RED)
	{
		parent = insertedNode->parent_;
		grandparent = parent->parent_;
		if (parent == grandparent->left)
		{
			NodePtr<T> uncle = grandparent->right;
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
					parent = insertedNode->parent;
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
					parent = insertedNode->parent_;
				}
				rotateLeft(grandparent);
				std::swap(parent->color_, grandparent->color_);
				insertedNode = parent;
			}
		}
	}
	setColor(root, BLACK);
}

template<typename T>
void RBTree<T>::add(const T& data)
{
	NodePtr<T> node = std::make_shared<Node<T>>(data);
	root = insertBin(root, node);
	RBTreeFixInsert(node);
}

template<typename T>
NodePtr<T> RBTree<T>::findMin(const NodePtr<T>& root)
{
	NodePtr<T> temp = root;
	while (temp->left_ != nullptr)
		temp = temp->left_;
	return temp;
}

template<typename T>
RBIterator<T> RBTree<T>::begin()
{
	return RBIterator<T>(findMin(root));
}

template<typename T>
RBIterator<T> RBTree<T>::end()
{
	return RBIterator<T>(nullptr);
}

#endif //TREE_HPP_
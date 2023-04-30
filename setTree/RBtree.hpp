#ifndef TREE_HPP_
#define TREE_HPP_

#include "tree.h"

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
	if (nodeToInsert->data_ > root)
		root->right_ = insertBin(root->right_, nodeToInsert);
	else if (nodeToInsert->data_ > root)
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
void RBTree<T>::RBTreeFixInsert(NodePtr<T> insertedNode)
{

	NodePtr<T> parent = nullptr;
	NodePtr<T> grandparent = nullptr;
	while (insertedNode != root && getColor(insertedNode) == RED && getColor(insertedNode->parent) == RED)
	{
		parent = insertedNode->parent;
		grandparent = parent->parent;
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
				if (insertedNode == parent->right)
				{
					rotateLeft(parent);
					insertedNode = parent;
					parent = insertedNode->parent;
				}
				rotateRight(grandparent);
				std::swap(parent->color, grandparent->color);
				insertedNode = parent;
			}
		}
		else
		{
			NodePtr<T> uncle = grandparent->left;
			if (getColor(uncle) == RED)
			{
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				insertedNode = grandparent;
			}
			else
			{
				if (insertedNode == parent->left)
				{
					rotateRight(parent);
					insertedNode = parent;
					parent = insertedNode->parent;
				}
				rotateLeft(grandparent);
				std::swap(parent->color, grandparent->color);
				insertedNode = parent;
			}
		}
	}
	setColor(root, BLACK);
}


template<typename T>
void RBTree<T>::add(const T &data)
{
	NodePtr<T> node = std::make_shared<Node<T>>(data);
	root = insertBin(root);
	RBTreeFixInsert(node);
}

#endif //TREE_HPP_
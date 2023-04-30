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
	struct node *pivot = node->left;

	pivot->parent = node->parent; 
	if (node->parent != NULL) {
		if (node->parent->left==node)
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


#endif //TREE_HPP_
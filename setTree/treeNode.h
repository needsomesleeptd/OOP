//
// Created by Андрей on 30.04.2023.
//

#ifndef LAB_02__TREENODE_H_
#define LAB_02__TREENODE_H_

#include <memory>
#include "concepts.h"

enum NodeColor
{
	RED, BLACK,DOUBLE_BLACK
};
template<ValidNodeData T>
struct Node
{
	T data_;
	std::weak_ptr<Node<T>> parent_;
	std::shared_ptr<Node<T>> left_;
	std::shared_ptr<Node<T>> right_;
	NodeColor color_;

	explicit Node(const T& data) : parent_(), left_(), right_(), data_(data), color_(RED)
	{

	}
	explicit Node() : parent_(), left_(), right_(), data_(), color_(RED)
	{

	}
	void setColor(NodeColor color);
	NodeColor getColor();
	void clear_subtree();


};

template<ValidNodeData T>
void Node<T>::clear_subtree()
{
	if (left_)
		left_->clear_subtree();
	if (right_)
		right_->clear_subtree();

	right_ = nullptr;
	left_ = nullptr;
};


template<ValidNodeData T>
void Node<T>::setColor(NodeColor color)
{
	color_ = color;
}

template<ValidNodeData T>
NodeColor Node<T>::getColor()
{
	return color_;
}

template<ValidNodeData T>
using NodePtr = std::shared_ptr<Node<T>>;

#endif //LAB_02__TREENODE_H_

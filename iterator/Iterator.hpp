#include "tree.h"

template<typename T>
class RBTree;

template<typename T>
class RBIterator : std::iterator<std::random_access_iterator_tag, NodePtr<T>>
{
 private:
	friend class RBTree<T>;
	std::weak_ptr<NodePtr<T>> cur_node;
	const NodePtr<T> prev();
	const NodePtr<T> next();
	NodePtr<T> find_next_up();
	NodePtr<T> find_next_down();
	NodePtr<T> find_prev_up();
	NodePtr<T> find_prev_down();

	explicit RBIterator(NodePtr<T> node);
 public:
	// Операции, необходимые для всех категорий итераторов.
	RBIterator() = default;
	RBIterator(const RBIterator&) = default;
	RBIterator& operator=(const RBIterator&) = default;
	~RBIterator() = default;

	T get();

	T& operator*();
	T* operator->();

	const RBIterator operator++();
	const RBIterator operator++(int);

	// Операции, необходимые для InputIterator.
	const T* operator->() const;

	// Операции, необходимые для BidirectionalIterator.
	const RBIterator operator--();
	const RBIterator operator--(int);

	bool operator==(const RBIterator& other);
	bool operator!=(const RBIterator& other);
};

template<typename T>
const RBIterator<T> RBIterator<T>::operator++()
{
	return next();

}

template<typename T>
const RBIterator<T> RBIterator<T>::operator--()
{
	return prev();

}

template<typename T>
const RBIterator<T> RBIterator<T>::operator++(int)
{
	NodePtr<T> save_node_ptr = cur_node;
	next();
	return save_node_ptr;
}

template<typename T>
const RBIterator<T> RBIterator<T>::operator--(int)
{
	NodePtr<T> save_node_ptr = cur_node;
	prev();
	return save_node_ptr;
}

template<typename T>
NodePtr<T> RBIterator<T>::find_next_down()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	shared_node_ptr = shared_node_ptr->right;
	while (shared_node_ptr->left != nullptr)
		shared_node_ptr = shared_node_ptr->left;
	return shared_node_ptr;
}

template<typename T>
NodePtr<T> RBIterator<T>::find_next_up()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent;
	while (parent != nullptr && shared_node_ptr == parent->right)
	{
		shared_node_ptr = parent;
		parent = parent->parent;
	}
	return parent;
}

template<typename T>
NodePtr<T> RBIterator<T>::find_prev_down()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	shared_node_ptr = shared_node_ptr->left;
	while (shared_node_ptr->left != nullptr)
		shared_node_ptr = shared_node_ptr->right;
	return shared_node_ptr;

}

template<typename T>
NodePtr<T> RBIterator<T>::find_prev_up()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent;
	while (parent != nullptr && shared_node_ptr == parent->left)
	{
		shared_node_ptr = parent;
		parent = parent->parent;
	}
	return parent;

}

template<typename T>
const NodePtr<T> RBIterator<T>::next()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();

	//if (shared_node_ptr == nullptr)
	//Todo::Throw out of bounds exc
	if (shared_node_ptr->right != nullptr)
		return find_next_down();
	else
		return find_next_up();
	//return *this;
}

template<typename T>
const NodePtr<T> RBIterator<T>::prev()
{
	//if (shared_node_ptr == nullptr)
	//Todo::Throw out of bounds exc
	if (cur_node->right != nullptr)
		return find_prev_down();
	else
		return find_prev_up();
}

template<typename T>
bool RBIterator<T>::operator==(const RBIterator& other)
{
	return this->get() == other.get();
}

template<typename T>
bool RBIterator<T>::operator!=(const RBIterator& other)
{
	return this->get() != other.get();
}

template<typename T>
T RBIterator<T>::get()
{
	return cur_node->data;
}

template<typename T>
T &RBIterator<T>::operator*()
{
	return this->cur_node.lock().data;
}

template<typename T>
T *RBIterator<T>::operator->()
{
	return &(this->cur_node.lock().data);
}

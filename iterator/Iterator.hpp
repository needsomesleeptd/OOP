#include "tree.h"
#include "iostream"

template<typename T>
class RBTree;

template<typename T>
class RBIterator : std::iterator<std::random_access_iterator_tag, Node<T>>
{
 private:
	friend class RBTree<T>;
	std::weak_ptr<Node<T>> cur_node;
	const NodePtr<T> prev();
	const NodePtr<T> next();
	NodePtr<T> find_next_up();
	NodePtr<T> find_next_down();
	NodePtr<T> find_prev_up();
	NodePtr<T> find_prev_down();

	//explicit RBIterator(NodePtr<T> node);
 public:
	// Операции, необходимые для всех категорий итераторов.
	RBIterator() = default;
	explicit RBIterator(const RBIterator&) = default;
	explicit RBIterator(NodePtr<T> ptr);

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
RBIterator<T>::RBIterator(NodePtr<T> ptr)
{
	//std::shared_ptr<NodePtr<T>> new_node(ptr);
	cur_node = ptr;
}

template<typename T>
const RBIterator<T> RBIterator<T>::operator++()
{
	cur_node = next();
	return RBIterator<T>(cur_node.lock());

}

template<typename T>
const RBIterator<T> RBIterator<T>::operator--()
{
	cur_node = prev();
	return RBIterator<T>(cur_node.lock());
}

template<typename T>
const RBIterator<T> RBIterator<T>::operator++(int)
{
	NodePtr<T> save = cur_node.lock();
	cur_node = next();
	return  RBIterator<T>(save);
}

template<typename T>
const RBIterator<T> RBIterator<T>::operator--(int)
{
	NodePtr<T> save = cur_node.lock();
	cur_node = prev();
	return  RBIterator<T>(save);
}

template<typename T>
NodePtr<T> RBIterator<T>::find_next_down()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	shared_node_ptr = shared_node_ptr->right_;
	while (shared_node_ptr->left_ != nullptr)
		shared_node_ptr = shared_node_ptr->left_;
	return shared_node_ptr;
}

template<typename T>
NodePtr<T> RBIterator<T>::find_next_up()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent_.lock();
	while (parent != nullptr && shared_node_ptr == parent->right_)
	{
		shared_node_ptr = parent;
		parent = parent->parent_.lock();
	}
	return parent;
}

template<typename T>
NodePtr<T> RBIterator<T>::find_prev_down()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	shared_node_ptr = shared_node_ptr->left_;
	while (shared_node_ptr->left_ != nullptr)
		shared_node_ptr = shared_node_ptr->right_;
	return shared_node_ptr;

}

template<typename T>
NodePtr<T> RBIterator<T>::find_prev_up()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent_.lock();
	while (parent != nullptr && shared_node_ptr == parent->left_)
	{
		shared_node_ptr = parent;
		parent = parent->parent_.lock();
	}
	return parent;

}

template<typename T>
const NodePtr<T> RBIterator<T>::next()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();

	//if (shared_node_ptr == nullptr)
	//Todo::Throw out of bounds exc
	if (shared_node_ptr->right_ != nullptr)
		return find_next_down();
	else
		return find_next_up();
	//return *this;
}

template<typename T>
const NodePtr<T> RBIterator<T>::prev()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	//if (shared_node_ptr == nullptr)
	//Todo::Throw out of bounds exc
	if (shared_node_ptr->left_ != nullptr)
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
T& RBIterator<T>::operator*()
{
	return this->cur_node.lock()->data_;
}

template<typename T>
T* RBIterator<T>::operator->()
{
	return &(this->cur_node.lock().data);
}

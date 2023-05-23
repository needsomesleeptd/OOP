#include <ctime>

#include "tree.h"
#include "exceptions.h"

template<ValidNodeData T>
class RBTree;

template<ValidNodeData T>
class RBIterator
{
 private:
	friend class RBTree<T>;
	std::weak_ptr<Node<T>> cur_node;
	int index;
	const NodePtr<T> prev();
	const NodePtr<T> next();
	NodePtr<T> find_next_up();
	NodePtr<T> find_next_down();
	NodePtr<T> find_prev_up();
	NodePtr<T> find_prev_down();

	RBIterator() = default;
	explicit RBIterator(NodePtr<T> ptr);

 public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = std::ptrdiff_t;


	// Операции, необходимые для всех категорий итераторов.




	RBIterator(const RBIterator&) = default;
	RBIterator& operator=(const RBIterator&) = default;
	~RBIterator() = default;

	reference operator*();

	pointer operator->();

	RBIterator& operator++();
	RBIterator operator++(int)&;
	RBIterator& operator--();
	RBIterator operator--(int)&;

	bool operator!=(const RBIterator& other) const;
	bool operator==(const RBIterator& other) const;

	T get() const;
};

template<ValidNodeData T>
RBIterator<T>::RBIterator(NodePtr<T> ptr)
{

	cur_node = ptr;
	index = 0;
}

template<ValidNodeData T>
RBIterator<T>& RBIterator<T>::operator++()
{
	try
	{
		cur_node = next();
	}
	catch (const OutOfBoundsException& exception)
	{
		throw;
	}
	index++;
	return *this;

}

template<ValidNodeData T>
RBIterator<T>& RBIterator<T>::operator--()
{
	try
	{
		cur_node = prev();
	}
	catch (const OutOfBoundsException& exception)
	{
		throw;
	}
	index--;
	return *this;
}

template<ValidNodeData T>
RBIterator<T> RBIterator<T>::operator++(int)&
{
	NodePtr<T> save = cur_node.lock();
	++(*this);
	return RBIterator<T>(save);
}

template<ValidNodeData T>
RBIterator<T> RBIterator<T>::operator--(int)&
{
	NodePtr<T> save = cur_node.lock();
	--(*this);
	return RBIterator<T>(save);
}

template<ValidNodeData T>
NodePtr<T> RBIterator<T>::find_next_down()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	shared_node_ptr = shared_node_ptr->right();
	while (shared_node_ptr->left() != nullptr)
		shared_node_ptr = shared_node_ptr->left();
	return shared_node_ptr;
}

template<ValidNodeData T>
NodePtr<T> RBIterator<T>::find_next_up()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent().lock();
	while (parent != nullptr && shared_node_ptr != parent->left())
	{
		shared_node_ptr = parent;
		parent = parent->parent().lock();
	}
	return parent;
}

template<ValidNodeData T>
NodePtr<T> RBIterator<T>::find_prev_down()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	shared_node_ptr = shared_node_ptr->left();
	while (shared_node_ptr->left() != nullptr)
		shared_node_ptr = shared_node_ptr->right();
	return shared_node_ptr;

}

template<ValidNodeData T>
NodePtr<T> RBIterator<T>::find_prev_up()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent().lock();
	while (parent != nullptr && shared_node_ptr == parent->left())
	{
		shared_node_ptr = parent;
		parent = parent->parent().lock();
	}
	return parent;

}

template<ValidNodeData T>
const NodePtr<T> RBIterator<T>::next()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();

	if (shared_node_ptr == nullptr)
	{
		time_t timer = time(nullptr);
		throw OutOfBoundsException(__FILE__, __LINE__, "NodePtr<T>", ctime(&timer));
	}

	if (shared_node_ptr->right() != nullptr)
		return find_next_down();
	else
		return find_next_up();
	//return *this;
}

template<ValidNodeData T>
const NodePtr<T> RBIterator<T>::prev()
{
	NodePtr<T> shared_node_ptr = cur_node.lock();
	if (shared_node_ptr == nullptr)
	{
		time_t timer = time(nullptr);
		throw OutOfBoundsException(__FILE__, __LINE__, "NodePtr<T>", ctime(&timer));
	}

	if (shared_node_ptr->left() != nullptr)
		return find_prev_down();
	else
		return find_prev_up();

}

template<ValidNodeData T>
bool RBIterator<T>::operator==(const RBIterator& other) const
{
	return this->cur_node.lock() == other.cur_node.lock();
}

template<ValidNodeData T>
bool RBIterator<T>::operator!=(const RBIterator& other) const
{

	return this->cur_node.lock() != other.cur_node.lock();
}

template<ValidNodeData T>
T RBIterator<T>::get() const
{
	return cur_node.lock()->data();
}

template<ValidNodeData T>
T& RBIterator<T>::operator*()
{
	if (cur_node.expired())
	{
		time_t timer = time(nullptr);
		throw InvalidIteratorAccessException(__FILE__, __LINE__, "NodePtr<T>", ctime(&timer));
	}
	return this->cur_node.lock()->data();
}

template<ValidNodeData T>
T* RBIterator<T>::operator->()
{
	return &(this->cur_node.lock().data);
}


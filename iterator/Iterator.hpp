#include "tree.h"


template<typename T>
class RBTree;

template <typename T>
class RBIterator : std::iterator<std::random_access_iterator_tag, NodePtr<T>> {
private:
	friend class RBTree<T>;
	std::weak_ptr<NodePtr<T>> cur_node;
	void prev();
	void next();
	void find_next_up();
	void find_next_down();

	explicit RBIterator(NodePtr<T> node);
 public:
	// Операции, необходимые для всех категорий итераторов.
	RBIterator() = default;
	RBIterator(const RBIterator&) = default;
	RBIterator& operator=(const RBIterator&) = default;
	~RBIterator() = default;

	T get();

	const &T &operator*();
	RBIterator& operator++();
	RBIterator operator++(int);




	// Операции, необходимые для InputIterator.
	const &T *operator->() const;

	// Операции, необходимые для BidirectionalIterator.
	RBIterator& operator--();
	RBIterator operator--(int);

	bool operator == (const RBIterator &other);
	bool operator != (const RBIterator &other);
};

template<typename T>
void RBIterator<T>::operator++()
{
	next();
	return *this;
}

template<typename T>
void RBIterator<T>::operator--()
{
	prev();
	return *this;
}

template<typename T>
void RBIterator<T>::operator++(int)
{
	NodePtr<T> save_node_ptr = cur_node;
	next();
	return save_node_ptr;
}

template<typename T>
void RBIterator<T>::operator--(int)
{
	NodePtr<T> save_node_ptr = cur_node;
	prev();
	return save_node_ptr;
}


template<typename T>
NodePtr RBIterator<T>::find_next_down()
{
	NodePtr<T> shared_node_ptr = current_node.lock();
	shared_node_ptr = shared_node_ptr->right;
	while (shared_node_ptr->left != nullptr)
		shared_node_ptr = shared_node_ptr->left;
	return shared_node_ptr
}

template<typename T>
NodePtr  RBIterator<T>::find_next_up()
{
	NodePtr<T> shared_node_ptr = current_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent;
	while (parent != nullptr && shared_node_ptr == parent->right)
	{
		shared_node_ptr = parent;
		parent = parent->parent;
	}
	return parent;
}


template<typename T>
void RBIterator<T>::find_prev_down()
{
	NodePtr<T> shared_node_ptr = current_node.lock();
	shared_node_ptr = shared_node_ptr->left;
	while (shared_node_ptr->left != nullptr)
		shared_node_ptr = shared_node_ptr->right;
	current_node = shared_node_ptr;
}

template<typename T>
void RBIterator<T>::find_prev_up()
{
	NodePtr<T> shared_node_ptr = current_node.lock();
	NodePtr<T> parent = shared_node_ptr->parent;
	while (parent != nullptr && shared_node_ptr == parent->left)
	{
		shared_node_ptr = parent;
		parent = parent->parent;
	}
	current_node = parent;
}


template<typename T>
void RBIterator<T>::next()
{
	NodePtr<T> shared_node_ptr = current_node.lock();

	//if (shared_node_ptr == nullptr)
		//Todo::Throw out of bounds exc
	 if (shared_node_ptr->right != nullptr)
		find_next_down();
	 else
		find_next_up();
	return *this;
}

template<typename T>
void RBIterator<T>::prev()
{
	//if (shared_node_ptr == nullptr)
	//Todo::Throw out of bounds exc
	if (shared_node_ptr->right != nullptr)
		find_prev_down();
	else
		find_prev_up();
}


template<typename T>
bool RBIterator<T>::operator==(const RBIterator &other)
{
	return this->get() == other.get()
}

template<typename T>
bool RBIterator<T>::operator!=(const RBIterator &other)
{
	return this->get() != other.get()
}



template<typename T>
T get()
{
	return cur_node->data;
}

template<typename T>
const T &RBTreeIterator<T>::operator*() const
{
	return this->cur_node->data;
}




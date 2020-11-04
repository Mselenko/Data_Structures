
template <typename T>

class SortedList
{
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_;

		Node(const T& data = T{}, Node* nx = nullptr, Node* pr = nullptr)
		{
			data_ = data;
			next_ = nx;
			prev_ = pr;
		}
	};

	Node* front_;
	Node* back_;
	int size_;

public:
	class const_iterator
	{
		friend class SortedList;
		Node* curr_;

		/**
		 * Private constructor
		 *
		 * Initializes new constant iterator
		 *
		 * @param curr - node pointer to set current iterator
		 */
		const_iterator(Node* curr)
		{
			curr_ = curr;
		}

	public:

		/**
		 * Default constructor
		 *
		 * Sets the iterator to safe state.
		 */
		const_iterator()
		{
			curr_ = nullptr;
		}

		/**
		 * Prefix increment
		 *
		 * Makes the operand point to the next node (one closer to the end) in the list
		 *
		 * @return Constant iterator that refers to the same object as the operand
		 */
		const_iterator& operator++()
		{
			curr_ = curr_->next_;
			return *this;
		}

		/**
		 * Postfix increment
		 *
		 * Makes the operand point to the next node (one closer to the end) in the list
		 *
		 * @param Dummy parameter to differentiate postfix
		 *
		 * @return Constant iterator to the object the operand pointed at before it was altered
		 */
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}

		/**
		 * Prefix decrement
		 *
		 * Makes the operand point to the previous node (one closer to the beginning of the list)
		 *
		 * @return Constant iterator that refers to the same object as the operand
		 */
		const_iterator& operator--()
		{
			curr_ = curr_->prev_;
			return *this;
		}

		/**
		 * Postfix decrement
		 *
		 * Makes the operand point to the previous node (one closer to the beginning of the list)
		 *
		 * @param Dummy parameter to differentiate postfix
		 *
		 * @return Constant iterator to the object the operand pointed at before it was altered
		 */
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			curr_ = curr_->prev_;
			return old;
		}

		/**
		 * Comparison operator (Equal)
		 *
		 * Compares two iterators
		 *
		 * @param const_iterator data - will be compared to the current one
		 *
		 * @return True if they refer to the same piece of data
		 */
		bool operator==(const_iterator data)
		{
			return curr_ == data.curr_;
		}

		/**
		 * Comparison operator (Not equal)
		 *
		 * Compares two iterators
		 *
		 * @param const_iterator data - will be compared to the current one
		 *
		 * @return True if they do not refer to the same piece of data
		 */
		bool operator!=(const_iterator data)
		{
			return !(*this == data);
		}

		/**
		 * Dereference operator
		 *
		 * @return Constant reference to the data
		 */
		const T& operator*() const
		{
			return curr_->data_;
		}
	};

	class iterator : public const_iterator
	{
		friend class SortedList;

		/**
		 * Private constructor
		 *
		 * Initializes new iterator through const_iterator constructor call
		 *
		 * @param curr - node pointer to set current iterator
		 */
		iterator(Node* curr) : const_iterator(curr) {};

	public:

		/**
		 * Default constructor
		 *
		 * Sets the iterator to safe state.
		 */
		iterator() : const_iterator() {}

		/**
		 * Prefix increment
		 *
		 * Makes the operand point to the next node (one closer to the end) in the list
		 *
		 * @return Iterator that refers to the same object as the operand
		 */
		iterator& operator++()
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}

		/**
		 * Postfix increment
		 *
		 * Makes the operand point to the next node (one closer to the end) in the list
		 *
		 * @param Dummy parameter to differentiate postfix
		 *
		 * @return Iterator to the object the operand pointed at before it was altered
		 */
		iterator operator++(int)
		{
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}

		/**
		 * Prefix decrement
		 *
		 * Makes the operand point to the previous node (one closer to the beginning of the list)
		 *
		 * @return Iterator that refers to the same object as the operand
		 */
		iterator& operator--()
		{
			this->curr_ = this->curr_->prev_;
			return *this;
		}

		/**
		 * Postfix decrement
		 *
		 * Makes the operand point to the previous node (one closer to the beginning of the list)
		 *
		 * @param Dummy parameter to differentiate postfix
		 *
		 * @return Iterator to the object the operand pointed at before it was altered
		 */
		iterator operator--(int)
		{
			iterator old = *this;
			this->curr_ = this->curr_->prev_;
			return old;
		}

		/**
		 * Dereference operator
		 *
		 * @return Reference to the data
		 */
		T& operator*()
		{
			return this->curr_->data_;
		}

		/**
		 * Dereference operator
		 *
		 * @return Constant reference to the data
		 */
		const T& operator*() const
		{
			return this->curr_->data_;
		}
	};

	/**
	 * @return Iterator that refers to the first piece of data in the SortedList
	 * Since in this case the first node is Sentinel, function returns iterator to the next node
	 */
	iterator begin()
	{
		return iterator(front_->next_);
	}

	/**
	 * @return Iterator to the last node in the SortedList
	 */
	iterator end()
	{
		return iterator(back_);
	}

	/**
	 * @return Constant iterator that refers to the first piece of data in the SortedList
	 * Since in this case the first node is Sentinel, function returns constant iterator to the next node
	 */
	const_iterator cbegin() const
	{
		return const_iterator(front_->next_);
	}

	/**
	 * @return Constant iterator to the last node in the SortedList
	 */
	const_iterator cend() const
	{
		return const_iterator(back_);
	}

	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);
	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};

/**
 * Default Constructor
 *
 * Creates empty SortedList object and sets Sentinel nodes
 */
template <typename T>
SortedList<T>::SortedList()
{
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
	size_ = 0;
}

/**
 * Destructor
 *
 * Loops through all nodes and deallocates a memory that was allocated for nodes
 */
template <typename T>
SortedList<T>::~SortedList()
{
	Node* curr = front_;
	while (curr != nullptr)
	{
		Node* rm = curr;
		curr = curr->next_;
		delete rm;
	}
}

/**
 * Copy constructor
 *
 * Initializes a new SortedList by making a copy of an object of the same class
 *
 * @param list - A SortedList object for copying
 */
template <typename T>
SortedList<T>::SortedList(const SortedList& list) : SortedList()
{
	*this = list;
}

/**
 * Copy assignment operator
 *
 * Deletes currently existing SortedList and assigns the received one to the
 * current empty list
 *
 * @param list - The list that should be assigned to the current existing list
 */
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& list)
{
	// Checks if the current object is not the same as the one that got passed. If not, process with assigning
	if (&list != this)
	{
		// Deletes currently existing data and inserts new data if received list is not empty
		erase(begin(), end());
		if (!list.empty())
		{
			for (const_iterator it = list.cbegin(); it != list.cend(); it++)
				insert(it.curr_->data_);
			size_ = list.size_;
		}
	}

	return *this;
}

/**
 * Move constructor
 *
 * Moves ownership of the resources from one object to another
 *
 * @param list - The SortedList object, whose ownership should be transfered to the current object
 */
template <typename T>
SortedList<T>::SortedList(SortedList && list)
{
	size_ = list.size_;
	front_ = list.front_;
	back_ = list.back_;

	list.size_ = 0;
	list.front_ = nullptr;
	list.back_ = nullptr;
}

/**
 * Move assignment operator
 *
 * Moves ownership of the resources from one object to another
 *
 * @param other The sorted list that will be transferred into the existing list
 * @return current object
 */
template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList && other)
{
	// Checks if the current object is not the same as the one that get passed. If not, keep processing
	if (this != &other)
	{
		Node* temp = other.front_;
		other.front_ = this->front_;
		this->front_ = temp;

		temp = other.back_;
		other.back_ = this->back_;
		this->back_ = temp;

		int tempSize = other.size_;
		other.size_ = this->size_;
		this->size_ = tempSize;
	}

	return *this;
}

/**
 * Adds data to the linked list
 *
 * Creates a new node with the data that get passed into the function and adds the new node into the SortedList object
 * Keeps the list sorted by inserting new node into the appropriate position
 *
 * @param data - The data that should be added to the linked list
 *
 * @return Iterator to a newly added node
 */
template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T & data)
{
	Node* newNode;
	Node* currentNode = front_;

	// The SortedList does not have any nodes besides Sentinels
	if (begin() == end())
	{
		// Inserts to the front of the SortedList
		newNode = new Node(data, back_, front_);
		back_->prev_ = newNode;
		front_->next_ = newNode;
		size_++;
		return begin();
	}

	// The linked list has at least one node
	for (const_iterator it = begin(); it != end(); it++)
	{
		currentNode = currentNode->next_;

		// Compares received and existing data to find appropriate spot for insertion to keep list sorted
		if (data < *it)
		{
			if (it == begin())
			{
				// The insertion is done into the beginning (front) of the linked list
				newNode = new Node(data, front_->next_, front_);
				front_->next_->prev_ = newNode;
				front_->next_ = newNode;
			}
			else
			{
				// The insertion is done into one of the linked list spot besides beginning or the end
				newNode = new Node(data, currentNode, currentNode->prev_);
				currentNode->prev_->next_ = newNode;
				currentNode->prev_ = newNode;
			}
			size_++;
			return iterator(newNode);
		}
	}

	// Inserts to the end of the SortedList if the received data is greater than any existing ones
	newNode = new Node(data, back_, back_->prev_);
	back_->prev_->next_ = newNode;
	back_->prev_ = newNode;
	size_++;

	return iterator(newNode);
}

/**
 * Search
 *
 * Searches for the data that was received
 *
 * @param data - The data that should be searched for
 *
 * @return Iterator to the node containing data
 *         If data is not found, returns the iterator that refers to the last node (Sentinel)
 */
template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T & data)
{
	iterator it;
	for (it = begin(); it != end(); it++)
	{
		if (*it == data)
			return it;
	}
	return end();
}

/**
 * Search (Constant)
 *
 * Searches for the data
 *
 * @param data - The data that should be searched for, can not be modified
 *
 * @return Constant iterator to the node containing data
 *         If data is not found, returns the constant iterator that refers to the last node (Sentinel)
 */
template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T & data) const
{
	const_iterator it = cbegin();
	for (it; it != cend(); it++)
	{
		if (*it == data)
			return it;
	}
	return cend();
}

/**
 * Erase
 *
 * Removes the node from the SortedList object based on the iterator reference
 *
 * @param it - The iterator that refers to the node for deletion
 *
 * @return Iterator to the node after the node is removed
		   If data is not found, returns the iterator that refers to the last node (Sentinel)
 */
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it)
{
	Node* delNode = it.curr_;
	iterator afterDelIter(delNode->next_);

	if (back_->prev_ == delNode)
	{
		// The element that should be deleted located at the back of the list
		Node* B = delNode->prev_;
		B->next_ = back_;
		back_->prev_ = B;
	}
	else if (front_->next_ == delNode)
	{
		// The element that should be deleted located at the front of the list
		Node* B = delNode->next_;
		front_->next_ = B;
		B->prev_ = front_;
	}
	else
	{
		// The element that should be deleted located not on the edges of the list
		delNode->prev_->next_ = delNode->next_;
		delNode->next_->prev_ = delNode->prev_;
	}

	--size_;
	delete delNode;

	return afterDelIter;
}

/**
 * Erase by range
 *
 * Removes nodes between the first (inclusive) and the last one
 *
 * @param first - The iterator where the deletion should start from
 * @param last  - The iterator where the deletion should end
 *
 * @return Iterator to the last element from the list
 */
template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last)
{
	for (iterator start = first; start != last;)
		start = erase(start);

	return last;
}

/**
 * @return The state of the current linked list, true if the list is empty, false otherwise
 */
template <typename T>
bool SortedList<T>::empty() const
{
	return (front_->next_ == back_);
}

/**
 * @return The size of the current SortedList
 */
template <typename T>
int SortedList<T>::size() const
{
	return size_;
}
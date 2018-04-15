#ifndef BANCH_NOSTL_SET_HXX
#define BANCH_NOSTL_SET_HXX

#include "nostl/list.hxx"

namespace nostl {

/// \brief re-implementation of std::Set<T>
///
/// @tparam T type of elements that the Set contains
///
/// I had to re-implement the Set class because using STL containers was
/// prohibited. This set uses the previously made custom List class. The
/// only addition is that it checks for multiple addition (the Set can only
/// contain each element only once).
template <typename T>
class Set {
public:
	/// \brief costructor w/o parameters --- only initialises memory
	Set() : number_of_elements_(0), list_(new List<T>) {}

	/// \brief copy constructor
	///
	/// \param obj Set to copy
	///
	/// The default copy constructor needs to be overridden because it would
	/// only copy a pointer to the List the Set uses.
	Set(Set const & obj)
	{
		this->number_of_elements_ = obj.number_of_elements_;
		*(this->list_) = obj.list_;
	}

	/// \brief assignment operator
	///
	/// \param Set to set *this* equal to
	///
	/// \return the Set itself
	Set & operator=(Set const &);


	/// \brief add element to the Set
	///
	/// \param value of new element
	void insert(T const &);

	/// \brief remove an element from the Set
	///
	/// \param value of element to remove
	void remove(T const &);

	/// \brief clear the Set (i.e. remove all of its elements)
	void clear();


	/// \brief get the size of the Set (i.e. the number of its elements)
	///
	/// \return the Set's size
	unsigned int size() const { return this->number_of_elements_; }


	/// \brief destructor
	///
	/// The destructor function needs to overridden because the class allocates
	/// memory for it's internal List
	~Set() { delete this->list_; }

public:
	/// \brief custom made iterator to navigate the Set mode easily
	class Iterator {
	public:
		/// \brief constructor for the Set's Iterator (uses Lists class')
		///
		/// \param list_iterator List Iterator to use
		Iterator(typename List<T>::Iterator list_iterator)
		{
			this->list_iterator_ = list_iterator;
		}


		/// \brief dereference operator
		///
		/// \return the value of the List Node currently pointed to
		T & operator*() { return *(this->list_iterator_); }

		/// \brief const dereference operator
		///
		/// \return the value of the List Node currently pointed to
		T const & operator*() const { return *(this->list_iterator_); }

		/// \brief member access operator
		///
		/// \return pointer to itself
		Iterator * operator->() const { return this; }


		/// \brief preincrement operator
		///
		/// \return Iterator of next List Node
		Iterator operator++()
		{
			++this->list_iterator_;
			return *this;
		}

		/// \brief postincrement operator
		///
		/// \param int dummy parameter
		///
		/// \return Iterator of current List Node
		Iterator operator++(int)
		{
			Iterator rv = *this;
			++this->list_iterator_;
			return rv;
		}

		/// \brief predecrement operator
		///
		/// \return Iterator of previous List Node
		Iterator operator--()
		{
			--this->list_iterator_;
			return *this;
		}

		/// \brief postdecrement operator
		///
		/// \param int dummy parameter
		///
		/// \return Iterator of current List Node
		Iterator operator--(int)
		{
			Iterator rv = *this;
			--this->list_iterator_;
			return rv;
		}


		/// \brief equality operator
		///
		/// \param rhs Iterator to check equality with
		///
		/// \return true if the Iterators point to the same List Node
		bool operator==(Iterator const & rhs) const
		{
			return this->list_iterator_ == rhs.list_iterator_;
		}

		/// \brief inequality operator
		///
		/// \param rhs Iterator to check inequality with
		///
		/// \return true if the Iterators point to different List Nodes
		bool operator!=(Iterator const & rhs) const { return !(*this == rhs); }


	private:
		typename List<T>::Iterator list_iterator_; ///< using already
													///< implemented List
													/// Itearator
	}; // class Iterator

public:
	/// \brief get Iterator to the first element of the Set
	///
	/// \return Iterator to first element
	Iterator begin()
	{
		typename List<T>::Iterator i = this->list_->begin();
		return Iterator(i);
	}

	/// \brief get Iterator to the last element of the Set
	///
	/// \return Iterator to last element
	Iterator end()
	{
		typename List<T>::Iterator i = this->list_->end();
		return Iterator(i);
	}


private:
	List<T> * list_; ///< Set is implemented using a doubly-linked List
	unsigned int number_of_elements_; ///< size of the Set

}; // class Set

template <typename T>
typename Set<T>::Set & Set<T>::operator=(Set const & rhs)
{
	// check for self assignment
	if (this == &rhs)
	{
		return *this;
	}

	this->clear();
	this->number_of_elements_ = rhs.number_of_elements_;
	this->list_ = rhs.list_;

	return *this;
}

template <typename T>
void Set<T>::insert(T const & val)
{
	// make sure list/set doesn't contain item yet
	if (this->number_of_elements_ != 0)
	{
		for (typename List<T>::Iterator i = this->list_->begin();
				i != this->list_->end(); ++i)
		{
			if (*i == val)
			{
				return;
			}
		}
	}

	this->list_->append(val);
	++this->number_of_elements_;
}

template <typename T>
void Set<T>::remove(T const & val)
{
	this->list_->remove(val);
	--this->number_of_elements_;
}

template <typename T>
void Set<T>::clear()
{
	this->list_->clear();
	this->number_of_elements_ = 0;
}

}

#endif // BANCH_NOSTL_SET_HXX

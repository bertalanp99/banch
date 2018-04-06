#ifndef BANCH_NOSTL_SET_HXX
#define BANCH_NOSTL_SET_HXX

#include "nostl/list.hxx"

namespace nostl {

template <typename T>
class Set { // implementing Set class for STL containers are prohibited
public:
	Set() : number_of_elements_(0), list_(new List<T>) {}

	Set(const Set& obj) : number_of_elements_(obj.number_of_elements_), list_(obj.list_) {}

	Set& operator=(const Set&);

	void insert(const T&);
	void remove(const T&);
	void clear();

	unsigned int size() const { return this->number_of_elements_; }

	~Set() { delete this->list_; }


private: // data members
	List<T> * list_;
	unsigned int number_of_elements_;

private: // nested class
	class Iterator {
	public:
		Iterator(typename List<T>::Iterator list_iterator) : list_iterator_(list_iterator) {}

		T& operator*() { return *(this->list_iterator_); } // derefence with *
		Iterator * operator->() { return this; } // dereference with ->
		Iterator operator++() // preincrement
		{
			++this->list_iterator_;
			return *this;
		}
		Iterator operator++(int) // postincrement
		{
			Iterator rv = *this;
			++this->list_iterator_;
			return rv;
		}
		Iterator operator--() // predecrement
		{
			--this->list_iterator_;
			return *this;
		}
		Iterator operator--(int) // postdecrement
		{
			Iterator rv = *this;
			--this->list_iterator_;
			return rv;
		}
		bool operator==(Iterator& rhs) { return this->list_iterator_ == rhs.list_iterator_; }
		bool operator!=(Iterator& rhs) { return (*this == rhs); }


	private:
		typename List<T>::Iterator list_iterator_;
	};
}; // class Set

template <typename T>
typename Set<T>::Set& Set<T>::operator=(const Set& rhs)
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
void Set<T>::insert(const T& val)
{
	// make sure list/set doesn't contain item yet
	if (this->number_of_elements_ != 0)
	{
		for (typename List<T>::Iterator i = this->list_->begin(); i != this->list_->end(); i++)
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
void Set<T>::remove(const T& val)
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

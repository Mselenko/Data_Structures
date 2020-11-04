
#include <string>
#include <utility>
#include <functional>
#include <iostream>
#include "mylist.h"

using namespace std;

template <class TYPE>
class Table {
public:
	Table() {}
	virtual void update(const string& key, const TYPE& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual bool find(const string& key, TYPE& value) = 0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
	virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}
	};

	Record** records_;   //the table
	int capacity_;       //capacity of the array

	void grow() {
		Record** tmp = new Record * [capacity_ + 10];
		for (int i = 0; i < capacity_; i++) {
			tmp[i] = records_[i];
		}
		for (int i = capacity_; i < capacity_ + 10; i++) {
			tmp[i] = nullptr;
		}
		delete[] records_;
		records_ = tmp;
		capacity_ += 10;
	}
public:
	SimpleTable(int capacity);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
	virtual bool isEmpty() const { return numRecords() == 0; }
	virtual int numRecords() const;
};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
	int rc = 0;
	for (int i = 0; records_[i] != nullptr; i++) {
		rc++;
	}
	return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
	records_ = new Record * [capacity];
	capacity_ = capacity;
	for (int i = 0; i < capacity_; i++) {
		records_[i] = nullptr;
	}
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	records_ = new Record * [other.capacity_];
	capacity_ = other.capacity_;
	for (int i = 0; i < other.numRecords(); i++) {
		update(other.records_[i]->key_, other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	capacity_ = other.capacity_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.capacity_ = 0;
}

template <class TYPE>
void SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = -1;
	int size = numRecords();
	for (int i = 0; i < size; i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx == -1) {
		if (size == capacity_) {
			grow();
		}
		records_[size++] = new Record(key, value);
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - 1 - i; j++) {
				if (records_[j]->key_ > records_[j + 1]->key_) {
					Record* tmp = records_[j];
					records_[j] = records_[j + 1];
					records_[j + 1] = tmp;
				}
			}
		}
	}
	else {
		records_[idx]->data_ = value;
	}

}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
	int idx = -1;
	for (int i = 0; i < numRecords(); i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx != -1) {
		delete records_[idx];
		int size = numRecords();
		for (int i = idx; i < size - 1; i++) {
			records_[i] = records_[i + 1];
		}
		records_[size - 1] = nullptr;
		return true;
	}
	else {
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = -1;
	for (int i = 0; i < numRecords(); i++) {
		if (records_[i]->key_ == key) {
			idx = i;
		}
	}
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}



template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			int sz = numRecords();
			for (int i = 0; i < sz; i++) {
				remove(records_[0]->key_);
			}
			delete[] records_;
		}
		records_ = new Record * [other.capacity_];
		capacity_ = other.capacity_;
		int size = other.numRecords();
		for (int i = 0; i < size; i++) {
			update(other.records_[i]->key_, other.records_[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(capacity_, other.capacity_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {
		int sz = numRecords();
		for (int i = 0; i < sz; i++) {
			remove(records_[0]->key_);
		}
		delete[] records_;
	}
}

template <class TYPE>
class ChainingTable :public Table<TYPE>
{
	struct Record
	{
		TYPE value_;
		string key_;

		Record(const string& key = "", const TYPE& data = TYPE{})
		{
			key_ = key;
			value_ = data;
		}

		bool operator==(const Record& rhs)
		{
			return key_ == rhs.key_;
		}

	};

	/**
	 * Grow function
	 *
	 * Increases the size of the SortedList array (records_) in 2 times and rehash the existing indexes of the elements based on new capacity
	 *
	 */
	void grow()
	{
		SortedList<Record>* resized = records_;
		size_ = 0;
		capacity_ *= 2;
		records_ = new SortedList<Record>[capacity_];

		// Loops through all the existing SortedList objects
		for (int i = 0; i < capacity_ / 2; i++)
		{
			// Loops through all the existing nodes in SortedList objects
			for (typename SortedList<Record>::const_iterator it = resized[i].cbegin(); it != resized[i].cend(); it++)
			{
				size_t hashIndex = getIndex((*it).key_);
				// Inserts items to the new array
				records_[hashIndex].insert(*it);
				size_++;
			}
		}
	}

	SortedList<Record>* records_;
	hash<string> hashedFunction;
	int capacity_;
	int size_;
	double maxLoadFactor_;

	/**
	 * Get index by a key
	 *
	 * Hashes the index based on the capacity and a key
	 *
	 * @param - The key for which the index should be returned
	 *
	 * @return The hashed index for the certain key
	 */
	size_t getIndex(const string& key)
	{
		return hashedFunction(key) % capacity_;
	}

public:
	ChainingTable(int maxExpected, double maxLoadFactor);
	ChainingTable(const ChainingTable& other);
	ChainingTable(ChainingTable&& other);
	virtual void update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	int capacity() const;
	virtual const ChainingTable& operator=(const ChainingTable& other);
	virtual const ChainingTable& operator=(ChainingTable&& other);
	virtual ~ChainingTable();

	/**
	 * @return The load status of the current records_. True if there are no records
	 */
	virtual bool isEmpty() const
	{
		return size_ == 0;
	}

	/**
	 * @return the size of the current records
	 */
	virtual int numRecords() const
	{
		return size_;
	}

};

/**
 * Constructor
 *
 * Initializes current object to the passed parameters
 *
 * @param Capacity      - The capacity of the new array
 * @param maxLoadFactor - The maximum load factor of the given array
 *
 */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor) : Table<TYPE>()
{
	records_ = new SortedList<Record>[capacity];
	capacity_ = capacity;
	maxLoadFactor_ = maxLoadFactor;
	size_ = 0;
}

/**
 * Copy constructor
 *
 * Initializes a new ChainingTable by making a copy of an object of the same class
 *
 * @param other - A ChainingTable object for copying
 */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other)
{
	records_ = nullptr;
	*this = other;
}

/**
 * Move constructor
 *
 * Moves ownership of the resources from one object to another
 *
 * @param other - The ChainingTable object, whose ownership should be transfered to the current object
 */
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other)
{
	records_ = other.records_;
	capacity_ = other.capacity_;
	size_ = other.size_;
	maxLoadFactor_ = other.maxLoadFactor_;

	other.records_ = nullptr;
	other.capacity_ = 0;
	other.size_ = 0;
	other.maxLoadFactor_ = 0.0;
}

/**
 * Checks if a table has a record with a matching key, the record's value is replaced by the value passed to this function.
 * If no record exists, a record with key-value pair is added.
 *
 * @param key - The key for which the value will be searched for
 * @param value - The reference where the value will be stored if found
 */
template <class TYPE>
void ChainingTable<TYPE>::update(const string& key, const TYPE& value)
{
	int val = value;
	Record newRecord(key, value);

	if (!find(key, val))
	{
		if ((double(size_) / capacity_) == maxLoadFactor_)
			grow();

		records_[getIndex(key)].push_back(newRecord);
		size_++;
	}
	else
	{
		// Uses the temporary record to search if the record in the current SortetList object exist
		Record* existingRecord = &*(&records_[getIndex(key)])->search(newRecord);

		if (*existingRecord == newRecord)
			existingRecord->value_ = newRecord.value_;
	}
}

/**
 * Removes a record with a matching key, the record (both the key and the value) is removed from the table
 *
 * @param key - The key for which the value will be searched for
 *
 * @return The status of the search
 */
template <class TYPE>
bool ChainingTable<TYPE>::remove(const string& key)
{
	size_t hashedIndex = getIndex(key);

	if (!records_[hashedIndex].empty())
	{
		SortedList<Record>* removalList = &records_[hashedIndex];

		for (auto it = removalList->begin(); it != removalList->end(); it++)
		{
			if ((&*it)->key_ == key)
			{
				removalList->erase(it);
				size_--;
				return true;
			}
		}
	}
	return false;
}

/**
 * Searches for the specific key in the current records array and stores the
 * value of the found record in the received value parameter
 *
 * @param key - The key for which the value will be searched for
 * @param value - The reference where the value will be stored if found
 *
 * @return The status of the search
 */
template <class TYPE>
bool ChainingTable<TYPE>::find(const string& key, TYPE& value)
{
	size_t hashIndex = getIndex(key);

	if (!records_[hashIndex].empty())
	{
		Record tempRecord(key, value);

		// Uses the temporary record to search if the record in the current SortetList object exist
		Record* existingRecord = &*(&records_[hashIndex])->search(tempRecord);

		if (*existingRecord == tempRecord)
		{
			value = existingRecord->value_;
			return true;
		}
	}
	return false;
}

/**
 * @return The capacity of the current records array
 */
template <class TYPE>
int ChainingTable<TYPE>::capacity() const
{
	return capacity_;
}

/**
 * Copy assignment operator
 *
 * Deletes currently existing records and assigns the received one to the current object
 *
 * @param other - The table that should be assigned to the current existing list
 */
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other)
{
	if (this != &other)
	{
		delete[] records_;
		records_ = new SortedList<Record>[other.capacity_];
		size_ = other.size_;
		maxLoadFactor_ = other.maxLoadFactor_;
		capacity_ = other.capacity_;

		for (int i = 0; i < capacity_; i++)
		{
			if (!other.records_[i].empty())
				records_[i] = other.records_[i];
		}
	}
	return *this;
}

/**
 * Move assignment operator
 *
 * Moves ownership of the resources from one object to another
 *
 * @param other - The ChainingTable array that will be transferred into the existing object
 *
 * @return Current object
 */
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other)
{
	if (this != &other)
	{
		records_ = other.records_;
		capacity_ = other.capacity_;
		size_ = other.size_;
		maxLoadFactor_ = other.maxLoadFactor_;

		other.records_ = nullptr;
		other.capacity_ = 0;
		other.size_ = 0;
		other.maxLoadFactor_ = 0.0;
	}
	return *this;
}

/**
 * Destructor
 *
 * Deallocates a memory that was allocated for array of SortedList objects
 */
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable()
{
	delete[] records_;
}



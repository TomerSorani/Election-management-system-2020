#pragma once
#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
private:
	T* _arr;
	int _logicalSize;
	int _physicalSize;

	void resize() {
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

public:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	// example iterator implementation:
	// (causes code duplication)
	class iterator
	{
	private:
		DynamicArray*	_da;
		int				_i;
		bool            _reverse;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T * ;
		using reference = T & ;

		// const_iterator should also be constructible from regular iterator
		friend class const_iterator;

		iterator(DynamicArray& arr, int i, bool reverse=false) : _da(&arr), _i(i), _reverse(reverse) {}
		iterator(const iterator& other) : _da(other._da), _i(other._i), _reverse(other._reverse) {}

		friend class const_iterator;

		// in const_iterator:	const_iterator(const iterator& other)
		//     					operator=(const iterator& other)

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			_reverse = other._reverse;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		iterator& operator++() {
			if (!_reverse)
				++_i;
			else
				--_i;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			if (!_reverse)
				++_i;
			else
				--_i;
			return temp;
		}
		iterator& operator--() {
			if (!_reverse)
				--_i;
			else
				++_i;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			if (!_reverse)
				--_i;
			else
				++_i;
			return temp;
		}
	};
	// and here we duplicate the 'iterator' class to 'const_iterator' 
	class const_iterator {
	private:
		const DynamicArray*	_da;
		int				    _i;
		bool               _reverse;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T * ;
		using reference = T & ;

		const_iterator(DynamicArray& arr, int i, bool reverse = false) : _da(&arr), _i(i), _reverse(reverse) {}
		const_iterator(const iterator& other) : _da(other._da), _i(other._i),_reverse(other._reverse) {}
		const_iterator(const const_iterator& other) : _da(other._da), _i(other._i),_reverse(other._reverse) {}


		const const_iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			_reverse = other._reverse;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const const_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const const_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		const T& operator*() {
			return _da->_arr[_i];
		}
		const T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		const_iterator& operator++() {
			if (!_reverse)
				++_i;
			else
				--_i;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator temp(*this);
			if (!_reverse)
				++_i;
			else
				--_i;
			return temp;
		}
		const_iterator& operator--() {
			if (!_reverse)
				--_i;
			else
				++_i;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator temp(*this);
			if (!_reverse)
				--_i;
			else
				++_i;
			return temp;
		} 
	};


	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	const iterator& erase(const iterator& iter)
	{
		iterator itrBeg = begin();
		iterator itrCurrent = itrBeg, itrPrev, itrNext = itrBeg++;
		while (iter != itrCurrent)
		{
			itrPrev = itrCurrent;
			itrCurrent++;
		}
		if (itrCurrent == end())
			return end();
		else if (itrCurrent == begin())
		{
			while (itrNext != end())
			{
				*itrCurrent = *itrNext;
				itrCurrent = itrNext++;
			}
			_logicalSize--;
			return --begin();
		}
		else
		{
			while (itrNext != end())
			{
				*itrCurrent = *itrNext;
				itrCurrent = itrNext++;
			}
			_logicalSize--;
			return itrPrev;
		}
	}
	const iterator& erase(const iterator& first, const iterator& last)
	{
		iterator itrBeg = begin();
		iterator itrCurrent = first, itrPrev, itrNext = itrBeg++;
		int counter = 0;
		if (first == last)
			return erase(first);

		if (first == begin() && last == end())
		{
			_logicalSize = 0;
			return --begin();
		}
		while (itrCurrent != last)
		{
			itrCurrent++;
			counter++;
		}
		counter++;
		if (last == end())
		{
			_logicalSize -= counter;
			return first--;
		}
		else if (first == begin())
		{
			iterator itrMove = last, itrPre = last, itrDest = begin(), itrPlace;
			itrPre++;
			itrPlace = itrPre;
			while (itrPlace != end())
			{
				while (itrMove != itrDest)
				{
					*itrMove = *itrPre;
					itrPre = itrMove--;
				}
				*itrMove = *itrPre;
				itrPre = itrPlace++;
				itrMove = itrPre;
				itrMove--;
				itrDest++;
			}
			_logicalSize -= counter;
			return --begin();
		}
		else
		{
			iterator itrMove = last, itrPre = last, itrDest = first, itrPlace;
			itrDest--;
			itrPre++;
			itrPlace = itrPre;
			while (itrPlace != end())
			{
				while (itrMove != itrDest)
				{
					*itrMove = *itrPre;
					itrPre = itrMove--;
				}
				itrPre = itrPlace++;
				itrMove = itrPre;
				itrMove--;
				itrDest++;
			}
			_logicalSize -= counter;
			return itrDest;
		}

	}

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}
	const_iterator begin() const {
		return const_iterator(*this, 0);
	}
	const_iterator end() const {
		return const_iterator(*this, _logicalSize);
	}
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}
	const_iterator cend() const {

		return const_iterator(*this, _logicalSize);
	}
	
	iterator rbegin() const {
		return iterator(*this, _logicalSize-1, true);
	}
	iterator rend() const {

		return iterator(*this, 0, true);
	}
};


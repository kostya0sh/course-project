#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
class list {
public:

	typedef int size_type;

	class iterator {
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++(int junk) { ptr_++; return *this; }
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
		pointer ptr_;
	};

	class const_iterator {
	public:
		typedef const_iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		const_iterator(pointer ptr) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		self_type operator++(int junk) { ptr_++; return *this; }
		const reference operator*() { return *ptr_; }
		const pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
		pointer ptr_;
	};

	list() : size_(0) {
		data_ = new T[1];
		allocatedSize_ = 1;
	}

	size_type size() const { return size_; }

	void put(const T& item) {
		auto copy = (T*)malloc((allocatedSize_ + 1) * sizeof(T));

		if (size_ > 0) {
			memcpy(copy, data_, size_ * sizeof(T));
		}

		copy[size_] = item;

		delete[] data_;
		data_ = copy;
		size_++;
		allocatedSize_++;
	}

	void remove(const_iterator iterator) {
		if (size_ <= 0) {
			return;
		}

		auto copy = (T*)malloc((allocatedSize_ - 1) * sizeof(T));

		bool removed = false;

		int copyIndex = 0;
		for (int i = 0; i < allocatedSize_; i++) {
			if (data_[i] == *iterator) {
				removed = true;
				continue;
			}

			memcpy(&copy[copyIndex], &data_[i], sizeof(T));
			copyIndex++;
		}

		delete[] data_;
		data_ = copy;

		if (removed) {
			size_--;
			allocatedSize_--;
		}
	}

	void remove(iterator iterator) {
		if (size_ <= 0) {
			return;
		}

		auto copy = (T*)malloc((allocatedSize_ - 1) * sizeof(T));

		bool removed = false;
		
		int copyIndex = 0;
		for (int i = 0; i < allocatedSize_; i++) {
			if (data_[i] == *iterator) {
				removed = true;
				continue;
			}

			memcpy(&copy[copyIndex], &data_[i], sizeof(T));
			copyIndex++;
		}
		
		delete[] data_;
		data_ = copy;

		if (removed) {
			size_--;
			allocatedSize_--;
		}
	}

	T& operator[](size_type index)
	{
		assert(index < size_);
		return data_[index];
	}

	const T& operator[](size_type index) const
	{
		assert(index < size_);
		return data_[index];
	}

	iterator begin()
	{
		return iterator(data_);
	}

	iterator end()
	{
		return iterator(data_ + size_);
	}

	const_iterator begin() const
	{
		return const_iterator(data_);
	}

	const_iterator end() const
	{
		return const_iterator(data_ + size_);
	}

private:
	T* data_;
	size_type allocatedSize_;
	size_type size_;
};
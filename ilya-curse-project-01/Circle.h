#pragma once

template <typename T>
class circle {
public:

	struct CircleItem {
		T v;
		CircleItem* next;
		CircleItem* prev;
	};

	circle() {

	}

	~circle() {
		while (first != nullptr) {
			pop();
		}
	}

	CircleItem* raw_first() {
		return first;
	}

	CircleItem* raw_last() {
		return last;
	}

	void push(const T& item) {
		CircleItem* newItem = new CircleItem();
		newItem->v = item;

		if (first != nullptr) {
			last->next = newItem;
			newItem->prev = last;
			last = newItem;
		}
		else {
			first = newItem;
			last = newItem;
		}

		last->next = first;
		first->prev = last;

		size_++;
	}

	void pop() {
		if (last == nullptr) {
			return;
		}

		auto tmp = last;
		auto prev = last->prev;
		
		if (prev == last) {
			last = nullptr;
			first = nullptr;
		}
		else {
			first->prev = prev;
			last = prev;
			last->next = first;
		}

		delete tmp;

		size_--;
	}

	int size() {
		return size_;
	}
	
private:
	CircleItem* last;
	CircleItem* first;
	int size_;
};
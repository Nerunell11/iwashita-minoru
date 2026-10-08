/**
 * @file DoublyLinkedList.inl
 * @date 2026-10-08
 */
#pragma once
#include <cassert>

 //--------------------------------------------------------
 // 参考文献- 後置戻り値型 ※要C++11以降
 // 戻り値型は->の後ろに明記されている
 // 宣言側は前置
 // https://cpprefjp.github.io/lang/cpp11/trailing_return_types.html
 //--------------------------------------------------------

 //--------------------------------------------------------
 // DoublyLinkedList
 //--------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : sentinel_(&sentinel_, &sentinel_, T{ }) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* p = sentinel_.next;
	while (p != &sentinel_) {
		Node* next = p->next;
		delete p;
		p = next;
	}
}

template <typename T>
auto DoublyLinkedList<T>::toMessage(Result result) -> const char* {
	switch (result) {
	case Result::Success: return "成功";
	case Result::NoOwner: return "どのリストにも属さないイテレータ";
	case Result::OtherList: return "別のリストのイテレータ";
	case Result::EndIterator: return "末尾を示すイテレータは削除できない";
	}
	return "不明なエラー";
}

template <typename T>
auto DoublyLinkedList<T>::insert(ConstIterator pos, const T& data, Iterator* outIt) -> Result {
	//どのリストにも属さないイテレータ
	if (pos.owner_ == nullptr) return Result::NoOwner;
	//別のリストのイテレータ
	if (pos.owner_ != this) return Result::OtherList;

	Node* added = new Node(pos.current_->prev, pos.current_, data);
	pos.current_->prev->next = added;
	pos.current_->prev = added;
	++count_;

	//挿入した要素を指すイテレータの格納先があれば格納
	if (outIt != nullptr) {
		*outIt = Iterator(added, this);
	}
	return Result::Success;
}

template <typename T>
auto DoublyLinkedList<T>::erase(ConstIterator pos, Iterator* outNext) -> Result {
	//どのリストにも属さないイテレータ
	if (pos.owner_ == nullptr) return Result::NoOwner;
	//別のリストのイテレータ
	if (pos.owner_ != this) return Result::OtherList;
	//末尾を示すイテレータ
	if (pos.current_ == &sentinel_) return Result::EndIterator;

	Node* target = pos.current_;
	Node* next = target->next;

	target->prev->next = target->next;
	target->next->prev = target->prev;
	delete target;
	--count_;

	//削除した要素の次の要素を指すイテレータの格納先があれば格納
	if (outNext != nullptr) {
		*outNext = Iterator(next, this);
	}
	return Result::Success;
}

template <typename T>
auto DoublyLinkedList<T>::begin() -> Iterator {
	return Iterator(sentinel_.next, this);
}

template <typename T>
auto DoublyLinkedList<T>::begin() const -> ConstIterator {
	return cbegin();
}

template <typename T>
auto DoublyLinkedList<T>::cbegin() const -> ConstIterator {
	return ConstIterator(sentinel_.next, this);
}

template <typename T>
auto DoublyLinkedList<T>::end() -> Iterator {
	return Iterator(&sentinel_, this);
}

template <typename T>
auto DoublyLinkedList<T>::end() const -> ConstIterator {
	return cend();
}

template <typename T>
auto DoublyLinkedList<T>::cend() const -> ConstIterator {
	//ConstIteratorはNode*で保持するためconstを外す。
	//ダミーノードの書き換えは非constのinsert/eraseからのみ行われるので安全
	return ConstIterator(const_cast<Node*>(&sentinel_), this);
}

template <typename T>
auto DoublyLinkedList<T>::size() const -> int {
	return count_;
}


//--------------------------------------------------------
// ConstIterator
//--------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(Node* node, const DoublyLinkedList* owner) : current_(node), owner_(owner) {}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator++() -> ConstIterator& {
	assert(hasOwner() && "イテレータの所有者が存在しません");
	assert(!isEnd() && "末尾を示すイテレータをインクリメントしようとしています");
	current_ = current_->next;
	return *this;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator++(int) -> ConstIterator {
	ConstIterator old = *this;
	++(*this);
	return old;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator--() -> ConstIterator& {
	assert(hasOwner() && "イテレータの所有者が存在しません");
	assert(!isBegin() && "先頭を示すイテレータをデクリメントしようとしています");
	current_ = current_->prev;
	return *this;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator--(int) -> ConstIterator {
	ConstIterator old = *this;
	--(*this);
	return old;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator*() const -> const T& {
	assert(hasOwner() && "イテレータの所有者が存在しません");
	assert(!isEnd() && "末尾を示すイテレータを参照しようとしています");
	return current_->data;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const -> bool {
	return current_ == other.current_;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const -> bool {
	return current_ != other.current_;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::hasOwner() const -> bool {
	return owner_ != nullptr && current_ != nullptr;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::isEnd() const -> bool {
	return current_ == owner_->cend().current_;
}

template <typename T>
auto DoublyLinkedList<T>::ConstIterator::isBegin() const -> bool {
	return current_ == owner_->cbegin().current_;
}

//--------------------------------------------------------
// Iterator
//--------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node, const DoublyLinkedList* owner) : ConstIterator(node, owner) {}

template <typename T>
auto DoublyLinkedList<T>::Iterator::operator*() const -> T& {
	assert(this->hasOwner() && "イテレータの所有者が存在しません");
	assert(!this->isEnd() && "末尾を示すイテレータを参照しようとしています");
	return this->current_->data;
}

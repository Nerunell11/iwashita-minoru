/**
 * @file DoublyLinkedList.inl
 * @date 2026-10-08
 */
#pragma once
#include <cassert>

//--------------------------------------------------------
// DoublyLinkedList
//--------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : sentinel(&sentinel, &sentinel, T{ }){ }

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* p = sentinel.next;
    while (p != &sentinel) {
        Node* next = p->next;
        delete p;
        p = next;
    }
}

template <typename T>
const char* DoublyLinkedList<T>::toMessage(Result result) {
    switch (result){
        case Result::Success: return "成功";
        case Result::NoOwner: return "どのリストにも属さないイテレータ";
        case Result::OtherList: return "別のリストのイテレータ";
        case Result::EndIterator: return "末尾を示すイテレータは削除できない";
    }
    return "不明なエラー";
}

template <typename T>
typename DoublyLinkedList<T>::Result DoublyLinkedList<T>::insert(ConstIterator pos, const T& data, Iterator* outIt) {
    //どのリストにも属さないイテレータ
    if (pos.owner == nullptr) return Result::NoOwner;
    //別のリストのイテレータ
    if (pos.owner != this) return Result::OtherList;

    Node* added = new Node(pos.current->prev, pos.current, data);
    pos.current->prev->next = added;
    pos.current->prev = added;
    ++count;
    
    //挿入した要素を指すイテレータの格納先があれば格納
    if (outIt != nullptr) {
        *outIt = Iterator(added,this);
    }
    return Result::Success;
}

template <typename T>
typename DoublyLinkedList<T>::Result DoublyLinkedList<T>::erase(ConstIterator pos, Iterator* outNext) {
    //どのリストにも属さないイテレータ
    if (pos.owner == nullptr) return Result::NoOwner;
    //別のリストのイテレータ
    if (pos.owner != this) return Result::OtherList;
    //末尾を示すイテレータ
    if (pos.current == &sentinel) return Result::EndIterator;

    Node* target = pos.current;
    Node* next = target->next;

    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;
    --count;
    
    //削除した要素の次の要素を指すイテレータの格納先があれば格納
    if(outNext != nullptr){
        *outNext = Iterator(next, this);
    }
    return Result::Success;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(sentinel.next, this);
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::begin() const {
    return cbegin();
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::cbegin() const {
    return ConstIterator(sentinel.next, this);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(&sentinel, this);
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::end() const {
    return cend();
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::cend() const {
    //ConstIteratorはNode*で保持するためconstを外す。
    //ダミーノードの書き換えは非constのinsert/eraseからのみ行われるので安全
    return ConstIterator(const_cast<Node*>(&sentinel), this);
}

template <typename T>
int DoublyLinkedList<T>::size() const {
    return count;
}


//--------------------------------------------------------
// ConstIterator
//--------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator(Node* node, const DoublyLinkedList<T>* owner) : current(node) ,owner(owner) {}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++() {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isEnd() && "末尾を示すイテレータをインクリメントしようとしています");
    current = current->next;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator++(int){
    ConstIterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--() {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isBegin() && "先頭を示すイテレータをデクリメントしようとしています");
    current = current->prev;
    return *this;
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::ConstIterator::operator--(int){
    ConstIterator old = *this;
    --(*this);
    return old;
}

template <typename T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isEnd() && "末尾を示すイテレータを参照しようとしています");
    return current->data;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::hasOwner() const {
    return owner != nullptr && current != nullptr;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::isEnd() const {
    return current == owner->cend().current;
}

template <typename T>
bool DoublyLinkedList<T>::ConstIterator::isBegin() const {
    return current == owner->cbegin().current;
}

//--------------------------------------------------------
// Iterator
//--------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node, const DoublyLinkedList<T>* owner) : ConstIterator(node, owner) {}

template <typename T>
T& DoublyLinkedList<T>::Iterator::operator*() const {
    assert(this->hasOwner() && "イテレータの所有者が存在しません");
    assert(!this->isEnd() && "末尾を示すイテレータを参照しようとしています");
    return this->current->data;
}

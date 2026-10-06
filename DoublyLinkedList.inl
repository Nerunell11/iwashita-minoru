//2026-10-06 iwashita-minoru


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    node = new Node(nullptr, nullptr, T{});
    node->prev = node;
    node->next = node;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* p = node->next;
    while (p != node) {
        Node* next = p->next;
        delete p;
        p = next;
    }
    delete node;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::insert(ConstIterator pos, const T& data) {
    //不正なイテレータが渡された場合はエラー
    if (pos.owner != this) {
        return Iterator(pos.current, this);
    }

    Node* added = new Node(pos.current->prev, pos.current, data);
    pos.current->prev->next = added;
    pos.current->prev = added;
    return Iterator(added, this);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::erase(ConstIterator pos) {
    //不正なイテレータが渡された場合はエラー
    if(pos.owner != this || pos.current == nullptr || pos.current == node) {
        return end();
    }

    Node* target = pos.current;
    Node* next = target->next;

    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;

    return Iterator(next, this);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(node->next, this);
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::begin() const {
    return cbegin();
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::cbegin() const {
    return ConstIterator(node->next, this);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(node, this);
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::end() const {
    return cend();
}

template <typename T>
typename DoublyLinkedList<T>::ConstIterator DoublyLinkedList<T>::cend() const {
    return ConstIterator(node, this);
}

template <typename T>
int DoublyLinkedList<T>::size() const {
    int count = 0;
    for (ConstIterator it = cbegin(); it != cend(); ++it) {
        ++count;
    }
    return count;
}


//-----------------------------------------------------------------------------------------------------------------
// ConstIteratorの実装
//-----------------------------------------------------------------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::ConstIterator::ConstIterator() : current(nullptr),owner(nullptr) {}

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


//-----------------------------------------------------------------------------------------------------------------
//Iteratorの実装
//-----------------------------------------------------------------------------------------------------------------

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator() : ConstIterator() {}

template <typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node, const DoublyLinkedList<T>* owner) : ConstIterator(node, owner) {}

template <typename T>
T& DoublyLinkedList<T>::Iterator::operator*() const {
    assert(this->hasOwner() && "イテレータの所有者が存在しません");
    assert(!this->isEnd() && "末尾を示すイテレータを参照しようとしています");
    return this->current->data;
}

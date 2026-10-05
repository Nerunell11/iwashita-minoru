//2026-10-01 iwashita-minoru
#include "ConstIterator.h"
#include "ScoreList.h"
#include "Node.h"
#include <cassert>

ConstIterator::ConstIterator() : current(nullptr),owner(nullptr) {}

ConstIterator::ConstIterator(Node* node, const ScoreList* owner) : current(node) ,owner(owner) {}

ConstIterator::ConstIterator(const ConstIterator& other) : current(other.current) ,owner(other.owner){}

ConstIterator& ConstIterator::operator=(const ConstIterator& other) {
    current = other.current;
    owner = other.owner;
    return *this;
}

ConstIterator& ConstIterator::operator++() {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isEnd() && "末尾を示すイテレータをインクリメントしようとしています");
    current = current->next;
    return *this;
}

ConstIterator ConstIterator::operator++(int){
    ConstIterator old = *this;
    ++(*this);
    return old;
}

ConstIterator& ConstIterator::operator--() {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isBegin() && "先頭を示すイテレータをデクリメントしようとしています");
    current = current->prev;
    return *this;
}

ConstIterator ConstIterator::operator--(int){
    ConstIterator old = *this;
    --(*this);
    return old;
}

const ScoreData& ConstIterator::operator*() const {
    return current->data;
}

bool ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

bool ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

bool ConstIterator::hasOwner() const {
    return owner != nullptr && current != nullptr;
}

bool ConstIterator::isEnd() const {
    return current == owner->end().current;
}

bool ConstIterator::isBegin() const {
    return current == owner->begin().current;
}

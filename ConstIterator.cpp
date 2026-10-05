//2026-10-01 iwashita-minoru
#include "ScoreList.h"
#include <cassert>

ScoreList::ConstIterator::ConstIterator() : current(nullptr),owner(nullptr) {}

ScoreList::ConstIterator::ConstIterator(Node* node, const ScoreList* owner) : current(node) ,owner(owner) {}

ScoreList::ConstIterator& ScoreList::ConstIterator::operator++() {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isEnd() && "末尾を示すイテレータをインクリメントしようとしています");
    current = current->next;
    return *this;
}

ScoreList::ConstIterator ScoreList::ConstIterator::operator++(int){
    ConstIterator old = *this;
    ++(*this);
    return old;
}

ScoreList::ConstIterator& ScoreList::ConstIterator::operator--() {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isBegin() && "先頭を示すイテレータをデクリメントしようとしています");
    current = current->prev;
    return *this;
}

ScoreList::ConstIterator ScoreList::ConstIterator::operator--(int){
    ConstIterator old = *this;
    --(*this);
    return old;
}

const ScoreData& ScoreList::ConstIterator::operator*() const {
    return current->data;
}

bool ScoreList::ConstIterator::operator==(const ConstIterator& other) const {
    return current == other.current;
}

bool ScoreList::ConstIterator::operator!=(const ConstIterator& other) const {
    return current != other.current;
}

bool ScoreList::ConstIterator::hasOwner() const {
    return owner != nullptr && current != nullptr;
}

bool ScoreList::ConstIterator::isEnd() const {
    return current == owner->cend().current;
}

bool ScoreList::ConstIterator::isBegin() const {
    return current == owner->cbegin().current;
}

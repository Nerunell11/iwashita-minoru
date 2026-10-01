//2026-10-01 iwashita-minoru
#include "ConstIterator.h"
#include "Node.h"

ConstIterator::ConstIterator(Node* node) : current(node) {}

ConstIterator::ConstIterator(const ConstIterator& other) : current(other.current) {}

ConstIterator& ConstIterator::operator=(const ConstIterator& other) {
    current = other.current;
    return *this;
}

ConstIterator& ConstIterator::operator++() {
    current = current->next;
    return *this;
}

ConstIterator& ConstIterator::operator--() {
    current = current->prev;
    return *this;
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

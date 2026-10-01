//2026-10-01 iwashita-minoru
#include "Iterator.h"
#include "Node.h"

Iterator::Iterator(Node* node) : ConstIterator(node) {}

ScoreData& Iterator::operator*() const {
    return current->data;
}

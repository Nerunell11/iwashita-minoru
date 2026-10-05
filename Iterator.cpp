//2026-10-01 iwashita-minoru
#include "Iterator.h"
#include "Node.h"
#include <cassert>

Iterator::Iterator() : ConstIterator() {}

Iterator::Iterator(Node* node, const ScoreList* owner) : ConstIterator(node, owner) {}

ScoreData& Iterator::operator*() const {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isEnd() && "末尾を示すイテレータを参照しようとしています");
    return current->data;
}

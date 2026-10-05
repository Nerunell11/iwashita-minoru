//2026-10-01 iwashita-minoru
#include "ScoreList.h"
#include <cassert>

ScoreList::Iterator::Iterator() : ConstIterator() {}

ScoreList::Iterator::Iterator(Node* node, const ScoreList* owner) : ConstIterator(node, owner) {}

ScoreData& ScoreList::Iterator::operator*() const {
    assert(hasOwner() && "イテレータの所有者が存在しません");
    assert(!isEnd() && "末尾を示すイテレータを参照しようとしています");
    return current->data;
}

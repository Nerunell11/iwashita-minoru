//2026-10-01 iwashita-minoru
#include "ScoreList.h"

ScoreList::ScoreList() {
    node = new Node(nullptr, nullptr, ScoreData{});
    node->prev = node;
    node->next = node;
}

ScoreList::~ScoreList() {
    Node* p = node->next;
    while (p != node) {
        Node* next = p->next;
        delete p;
        p = next;
    }
    delete node;
}

ScoreList::Iterator ScoreList::insert(ConstIterator pos, const ScoreData& data) {
    //不正なイテレータが渡された場合はエラー
    if (pos.owner != this) {
        return Iterator(pos.current, this);
    }

    Node* added = new Node(pos.current->prev, pos.current, data);
    pos.current->prev->next = added;
    pos.current->prev = added;
    return Iterator(added, this);
}

ScoreList::Iterator ScoreList::erase(ConstIterator pos) {
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

ScoreList::Iterator ScoreList::begin() {
    return Iterator(node->next, this);
}

ScoreList::ConstIterator ScoreList::begin() const {
    return cbegin();
}

ScoreList::ConstIterator ScoreList::cbegin() const {
    return ConstIterator(node->next, this);
}

ScoreList::Iterator ScoreList::end() {
    return Iterator(node, this);
}

ScoreList::ConstIterator ScoreList::end() const {
    return cend();
}

ScoreList::ConstIterator ScoreList::cend() const {
    return ConstIterator(node, this);
}

int ScoreList::size() const {
    int count = 0;
    for (ConstIterator it = cbegin(); it != cend(); ++it) {
        ++count;
    }
    return count;
}


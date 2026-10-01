//2026-10-01 iwashita-minoru
#include "ScoreList.h"
#include "Node.h"
#include <ostream>

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

Iterator ScoreList::insert(Iterator pos, const ScoreData& data) {
    Node* added = new Node(pos.current->prev, pos.current, data);
    pos.current->prev->next = added;
    pos.current->prev = added;
    return Iterator(added);
}

void ScoreList::pushBack(int score, const std::string& name) {
    insert(end(), ScoreData{ score, name });
}

Iterator ScoreList::erase(Iterator pos) {
    Node* target = pos.current;
    Node* next = target->next;

    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;

    return Iterator(next);
}

Iterator ScoreList::begin() {
    return Iterator(node->next);
}

ConstIterator ScoreList::begin() const {
    return ConstIterator(node->next);
}

Iterator ScoreList::end() {
    return Iterator(node);
}

ConstIterator ScoreList::end() const {
    return ConstIterator(node);
}

int ScoreList::size() const {
    int count = 0;
    for (ConstIterator it = begin(); it != end(); ++it) {
        ++count;
    }
    return count;
}

void ScoreList::print(std::ostream& os) const {
    for (ConstIterator it = begin(); it != end(); ++it) {
        const ScoreData& data = *it;
        os << data.score << '\t' << data.userName << '\n';
    }
}

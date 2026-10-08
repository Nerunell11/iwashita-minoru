//2026-10-01 iwashita-minoru
#include "ScoreList.h"

ScoreList::ScoreList() : sentinel(&sentinel, &sentinel, ScoreData{ }){ }

ScoreList::~ScoreList() {
    Node* p = sentinel.next;
    while (p != &sentinel) {
        Node* next = p->next;
        delete p;
        p = next;
    }
}

const char* ScoreList::toMessage(Result result) {
    switch (result){
        case Result::Success: return "成功";
        case Result::NoOwner: return "どのリストにも属さないイテレータ";
        case Result::OtherList: return "別のリストのイテレータ";
        case Result::EndIterator: return "末尾を示すイテレータは削除できない";
    }
    return "不明なエラー";
}

ScoreList::Result ScoreList::insert(ConstIterator pos, const ScoreData& data, Iterator* outIt) {
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

ScoreList::Result ScoreList::erase(ConstIterator pos, Iterator* outNext) {
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

ScoreList::Iterator ScoreList::begin() {
    return Iterator(sentinel.next, this);
}

ScoreList::ConstIterator ScoreList::begin() const {
    return cbegin();
}

ScoreList::ConstIterator ScoreList::cbegin() const {
    return ConstIterator(sentinel.next, this);
}

ScoreList::Iterator ScoreList::end() {
    return Iterator(&sentinel, this);
}

ScoreList::ConstIterator ScoreList::end() const {
    return cend();
}

ScoreList::ConstIterator ScoreList::cend() const {
    //ConstIteratorはNode*で保持するためconstを外す。
    //ダミーノードの書き換えは非constのinsert/eraseからのみ行われるので安全
    return ConstIterator(const_cast<Node*>(&sentinel), this);
}

int ScoreList::size() const {
    return count;
}


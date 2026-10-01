//2026-10-01 iwashita-minoru
#pragma once
#include "ScoreData.h"

class Node;
class ScoreList;


class ConstIterator {
    friend class ScoreList;
public:
    ConstIterator(const ConstIterator& other);
    ConstIterator& operator=(const ConstIterator& other);
    ConstIterator& operator++();
    ConstIterator& operator--();
    const ScoreData& operator*() const;
    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

    protected:
    explicit ConstIterator(Node* node);
    Node* current;
};

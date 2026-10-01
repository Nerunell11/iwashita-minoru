//2026-10-01 iwashita-minoru
#pragma once
#include "ScoreData.h"

class Node;
class ScoreList;


class ConstIterator {
    friend class ScoreList;
protected:
    Node* current;

public:
    explicit ConstIterator(Node* node);
    ConstIterator(const ConstIterator& other);
    ConstIterator& operator=(const ConstIterator& other);
    ConstIterator& operator++();
    ConstIterator& operator--();
    const ScoreData& operator*() const;
    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;
};

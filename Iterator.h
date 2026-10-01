//2026-10-01 iwashita-minoru
#pragma once
#include "ConstIterator.h"

class Node;

class Iterator : public ConstIterator {
    friend class ScoreList;

    public:
    ScoreData& operator*() const;
    
    private:
    explicit Iterator(Node* node);
};

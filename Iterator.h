//2026-10-01 iwashita-minoru
#pragma once
#include "ConstIterator.h"

class Node;

class Iterator : public ConstIterator {
public:
    explicit Iterator(Node* node);
    ScoreData& operator*();
};

//2026-10-01 iwashita-minoru
#pragma once

#pragma once
#include "ScoreData.h"
class ConstIterator;
class Iterator;
class ScoreList;
class Node {
    friend class ConstIterator;
    friend class Iterator;
    friend class ScoreList;
    Node* prev;
    Node* next;
    ScoreData data;
public:
    Node(Node* prev, Node* next, const ScoreData& data)
        : prev(prev), next(next), data(data) {}
};

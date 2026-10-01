//2026-10-01 iwashita-minoru
#pragma once
#include "Iterator.h"
#include "ScoreData.h"

class Node;

class ScoreList {
    Node* node;

public:
    ScoreList();
    ~ScoreList();

    ScoreList(const ScoreList&) = delete;
    ScoreList& operator=(const ScoreList&) = delete;
    ScoreList(ScoreList&&) = delete;
    ScoreList& operator=(ScoreList&&) = delete;

    Iterator insert(Iterator pos, const ScoreData& data);
    void pushBack(int score, const std::string& name);
    Iterator erase(Iterator pos);

    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;

    int size() const;
    void print() const;
};

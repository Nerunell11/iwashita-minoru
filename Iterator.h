//2026-10-01 iwashita-minoru
#pragma once
#include "ConstIterator.h"

class Node;

/**
 * @brief スコアとユーザー名を保持する双方向リストのイテレータ
 * 
 * 読み書き可能なイテレータ
 * コピーとムーブは禁止し、所有権はリスト自身が持つ
 * 親クラスのConstIteratorを継承している
 */
class Iterator : public ConstIterator {
    friend class ScoreList;

    public:
    Iterator();

    /**
     * @brief イテレータの現在のデータを取得する
     * 
     * @return ScoreData& 現在のデータ
     */
    ScoreData& operator*() const;
    
    private:
    explicit Iterator(Node* node, const ScoreList* owner);
};

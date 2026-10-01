//2026-10-01 iwashita-minoru
#pragma once
#include "ScoreData.h"

class Node;
class ScoreList;

/**
 * @brief スコアとユーザー名を保持する双方向リストのイテレータ
 * 
 * 読み取り専用のイテレータ
 * コピーとムーブは禁止し、所有権はリスト自身が持つ
 */
class ConstIterator {
    friend class ScoreList;
public:
    ConstIterator(const ConstIterator& other);
    ConstIterator& operator=(const ConstIterator& other);
    /**
     * @brief イテレータをインクリメントする
     * 
     * @return ConstIterator& インクリメント後のイテレータ
     */
    ConstIterator& operator++();

    /**
     * @brief 
     *
     * @return ConstIterator& デクリメント後のイテレータ
     */
    ConstIterator& operator--();
    
    /**
     * @brief イテレータの現在のデータを取得する
     * 
     * @return const ScoreData& 現在のデータ
     */
    const ScoreData& operator*() const;

    /**
     * @brief イテレータが等しいかどうかを比較する
     * 
     * @param other 比較するイテレータ
     * @return true 等しい場合
     * @return false 等しくない場合
     */
    bool operator==(const ConstIterator& other) const;

    /**
     * @brief イテレータが等しくないかどうかを比較する
     * 
     * @param other 比較するイテレータ
     * @return true 等しくない場合
     * @return false 等しい場合
     */
    bool operator!=(const ConstIterator& other) const;

    protected:
    explicit ConstIterator(Node* node);
    Node* current;
};

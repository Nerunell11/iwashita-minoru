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
    ConstIterator();
    ConstIterator(const ConstIterator& other);
    ConstIterator& operator=(const ConstIterator& other);
    /**
     * @brief イテレータをインクリメントする
     * 
     * @return ConstIterator& インクリメント後のイテレータ
     */
    ConstIterator& operator++();


    /**
     * @brief イテレータを後置インクリメントする
     *
     * @return ConstIterator インクリメント前のイテレータ
     */
    ConstIterator operator++(int);

    /**
     * @brief 
     *
     * @return ConstIterator& デクリメント後のイテレータ
     */
    ConstIterator& operator--();

    /**
     * @brief イテレータを後置デクリメントする
     * 
     * @return ConstIterator デクリメント前のイテレータ
     */
    ConstIterator operator--(int);
    
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
    ConstIterator(Node* node, const ScoreList* owner);

    /**
     * @brief イテレータが所有者を持っているかどうかを返す
     * 
     * @return true 所有者を持っている場合
     * @return false 所有者を持っていない場合
     */
    bool hasOwner() const;

    /**
     * @brief イテレータが末尾を示すかどうかを返す
     * 
     * @return true 末尾を示す場合
     * @return false 末尾を示していない場合
     */
    bool isEnd() const;

    /**
     * @brief イテレータが先頭を示すかどうかを返す
     * 
     * @return true 先頭を示す場合
     * @return false 先頭を示していない場合
     */
    bool isBegin() const;

    Node* current;
    const ScoreList* owner;
};

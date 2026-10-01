//2026-10-01 iwashita-minoru
#pragma once
#include "Iterator.h"
#include "ScoreData.h"
#include <ostream>

class Node;

/**
 * @brief スコアとユーザー名を保持する双方向リスト
 * 
 * コピーとムーブは禁止し、所有権はリスト自身が持つ
 */
class ScoreList {
    Node* node;

public:
    ScoreList();
    ~ScoreList();

    ScoreList(const ScoreList&) = delete;
    ScoreList& operator=(const ScoreList&) = delete;
    ScoreList(ScoreList&&) = delete;
    ScoreList& operator=(ScoreList&&) = delete;

    /**
     * @brief 指定位置にデータを挿入する
     * 
     * @param pos 挿入位置のイテレータ
     * @param data 挿入するデータ
     * @return Iterator 挿入後の位置のイテレータ
     */
    Iterator insert(Iterator pos, const ScoreData& data);

    /**
     * @brief 末尾にデータを追加する
     * 
     * @param score 追加するスコア
     * @param name 追加するユーザー名
     */
    void pushBack(int score, const std::string& name);

    /**
     * @brief 指定位置のデータを削除する
     * 
     * @param pos 削除する位置のイテレータ
     * @return Iterator 削除後の位置のイテレータ
     */
    Iterator erase(Iterator pos);


    /**
     * @brief 先頭のデータの位置のイテレータを取得する
     * 
     * @return Iterator 先頭のデータの位置のイテレータ
     */
    Iterator begin();

    /**
     * @brief 先頭のデータの位置のイテレータを取得する
     * 
     * @return ConstIterator 先頭のデータの位置のイテレータ
     */
    ConstIterator begin() const;
    
    /**
     * @brief 末尾のデータの位置のイテレータを取得する
     * 
     * @return Iterator 末尾のデータの位置のイテレータ
     */
    Iterator end();

    /**
     * @brief 末尾のデータの位置のイテレータを取得する
     * 
     * @return ConstIterator 末尾のデータの位置のイテレータ
     */
    ConstIterator end() const;

    /**
     * @brief リストのサイズを取得する
     * 
     * @return int リストのサイズ
     */
    int size() const;

    /**
     * @brief リストのデータを出力する
     * 
     * @param os 出力ストリーム
     */
    void print(std::ostream& os) const;
};

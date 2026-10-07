//2026-10-01 iwashita-minoru
#pragma once
#include "ScoreData.h"


/**
 * @brief スコアとユーザー名を保持する双方向リスト
 * 
 * コピーとムーブは禁止し、所有権はリスト自身が持つ
 */
class ScoreList {
private:

    /**
    * @brief リストの1要素を表すノード
    *
    */
    struct Node {
        Node* prev;
        Node* next;
        ScoreData data;
        Node(Node* prev, Node* next, const ScoreData& data)
            : prev(prev), next(next), data(data) {}
    };

public:

    /**
    * @brief 読み取り専用のイテレータ
    */
    class ConstIterator {
        friend class ScoreList;

    public:
        ConstIterator();

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
        * @brief イテレータを前置デクリメントする
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

    /**
    * @brief 読み書き可能なイテレータ
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
    Iterator insert(ConstIterator pos, const ScoreData& data);

    /**
     * @brief 指定位置のデータを削除する
     * 
     * @param pos 削除する位置のイテレータ
     * @return Iterator 削除後の位置のイテレータ
     */
    Iterator erase(ConstIterator pos);


    /**
     * @brief 先頭のデータの位置のイテレータを取得する
     * 
     * @return Iterator 先頭のデータの位置のイテレータ
     */
    Iterator begin();

    /**
     * @brief （読み取り専用）先頭のデータの位置のイテレータを取得する
     * 
     * @return ConstIterator 先頭のデータの位置のイテレータ
     */
    ConstIterator begin() const;

    /**
     * @brief （読み取り専用）先頭のデータの位置のイテレータを取得する
     * 
     * @return ConstIterator 先頭のデータの位置のイテレータ
     */
    ConstIterator cbegin() const;
    
    /**
     * @brief 末尾のデータの位置のイテレータを取得する
     * 
     * @return Iterator 末尾のデータの位置のイテレータ
     */
    Iterator end();

    /**
     * @brief （読み取り専用）末尾のデータの位置のイテレータを取得する
     * 
     * @return ConstIterator 末尾のデータの位置のイテレータ
     */
     ConstIterator end() const;

    /**
     * @brief （読み取り専用）末尾のデータの位置のイテレータを取得する
     * 
     * @return ConstIterator 末尾のデータの位置のイテレータ
     */
    ConstIterator cend() const;

    /**
     * @brief リストのサイズを取得する
     * 
     * @return int リストのサイズ
     */
    int size() const;

private:
    Node* node;

};

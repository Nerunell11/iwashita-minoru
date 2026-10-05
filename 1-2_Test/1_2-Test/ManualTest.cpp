/**
 * @file ManualTest.cpp
 * @brief 手動テストコード
 * @date 2026-10-05
 */

//--------------------------------------------------------------------------------
// ファイル依存関係
//--------------------------------------------------------------------------------
#include "pch.h"
#include <gtest/gtest.h>
#include "ScoreList.h"
#include "ManualTest.h"

using Iterator = ScoreList::Iterator;
using ConstIterator = ScoreList::ConstIterator;

namespace ex01_List
{

    /**
     * @brief constのメソッドであるか
     * @details ID:T008 
     *          constのリストから呼び出して、コンパイルエラーとならないかをチェック
     */
    TEST(ManualTest, T008){
#if defined(ENABLE_T008)
        const ScoreList list;
        EXPECT_EQ(0,list.size());
#endif
        SUCCEED();
    }

    /**
     * @brief 非constのメソッドであるか
     * @details ID:T015 
     *          constのリストから呼び出して、コンパイルエラーとなるかをチェック
     */
    TEST(ManualTest, T015){
#if defined(ENABLE_T015)
        const ScoreList list;
        ConstIterator it = list.cbegin();
        list.insert(it,ScoreData{ 1, "test" });//ここでエラー
#endif
        SUCCEED();
    }

    /**
     * @brief 非constのメソッドであるか
     * @details ID:T022 
     *          constのリストから呼び出して、コンパイルエラーとなることをチェック
     */
    TEST(ManualTest, T022){

#if defined(ENABLE_T022)
        const ScoreList list;
        list.erase(list.cbegin());//ここでエラー
#endif
        SUCCEED();
    }

    /**
     * @brief constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
     * @details ID:T028 
     *          コンパイルエラーになることを確認する
     */
    TEST(ManualTest, T028){

#if defined(ENABLE_T028)
        const ScoreList list;
        Iterator it = list.begin();//ここでエラー
#endif
        SUCCEED();

    }

    /**
     * @brief constのメソッドであるか
     * @details ID:T034 
     *          constのリストから呼び出して、コンパイルエラーとならないかをチェック
     */
    TEST(ManualTest, T034){

#if defined(ENABLE_T034)
        const ScoreList list;
        ConstIterator it =list.cbegin();
        EXPECT_TRUE(it == list.cend());
#endif
        SUCCEED();
    }

    /**
     * @brief constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
     * @details ID:T040 
     *          コンパイルエラーになることを確認する
     */
    TEST(ManualTest, T040){

#if defined(ENABLE_T040)
        const ScoreList list;
        Iterator it = list.end(); //ここでエラー
#endif
        SUCCEED();
    }

    /**
     * @brief constのメソッドであるか
     * @details ID:T046 
     *          constのリストから呼び出して、コンパイルエラーとならないかをチェック
     */
    TEST(ManualTest, T046){

#if defined(ENABLE_T046)
        const ScoreList list;
        ConstIterator it = list.cend();
        EXPECT_TRUE(it == list.cbegin());
#endif
        SUCCEED();
    }
}

namespace ex02_Iterator{

    /**
     * @brief ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
     * @details ID:T102 
     *          コンパイルエラーになることを確認する
     */
    TEST(ManualTest, T102){

#if defined(ENABLE_T102)
        ScoreList list;
        list.insert(list.end(), ScoreData{ 10, "test" });
        ConstIterator it = list.cbegin();
        (*it).score = 5; //ここでエラー
#endif
        SUCCEED();
    }

    /**
     * @brief ConstIteratorから、Iteratorのコピーが作成されないかをチェック
     * @details ID:T117 
     *          コンパイルエラーになることを確認する
     */
    TEST(ManualTest, T117){

#if defined(ENABLE_T117)
        ScoreList list;
        ConstIterator cit = list.cbegin();
        Iterator it(cit); //ここでエラー
#endif
        SUCCEED();
    }

    /**
     * @brief IteratorにConstIteratorを代入できない事をチェック
     * @details ID:T119 
     *          コンパイルエラーになることを確認する
     */
    TEST(ManualTest, T119){
#if defined(ENABLE_T119)
        Iterator it;
        ConstIterator cit;
        it = cit;
#endif
        SUCCEED();
    }


}

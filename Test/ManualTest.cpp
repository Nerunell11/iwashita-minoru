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
#include "DoublyLinkedList.h"
#include "QuickSort.h"
#include "ManualTest.h"
#include "ScoreData.h"

//成績データを格納する双方向リスト
using ScoreList = DoublyLinkedList<ScoreData>;
using Iterator = ScoreList::Iterator;
using ConstIterator = ScoreList::ConstIterator;

namespace ex01_List
{

	/**
	 * @brief constのメソッドであるか
	 * @details ID:T008
	 *          constのリストから呼び出して、コンパイルエラーとならないかをチェック
	 */
	TEST(ManualTest, ConstListAllowsSize) {
#if defined(ENABLE_CONST_LIST_ALLOWS_SIZE)
		const ScoreList list;
		EXPECT_EQ(0, list.size());
#endif
		SUCCEED();
	}


	/**
	 * @brief 非constのメソッドであるか
	 * @details ID:T015
	 *          constのリストから呼び出して、コンパイルエラーとなるかをチェック
	 */
	TEST(ManualTest, ConstListRejectsInsert) {
#if defined(ENABLE_CONST_LIST_REJECTS_INSERT)
		const ScoreList list;
		ConstIterator it = list.cbegin();
		list.insert(it, ScoreData{ 1, "test" });//ここでエラー
#endif
		SUCCEED();
	}


	/**
	 * @brief 非constのメソッドであるか
	 * @details ID:T022
	 *          constのリストから呼び出して、コンパイルエラーとなることをチェック
	 */
	TEST(ManualTest, ConstListRejectsErase) {

#if defined(ENABLE_CONST_LIST_REJECTS_ERASE)
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
	TEST(ManualTest, ConstListRejectsMutableBegin) {

#if defined(ENABLE_CONST_LIST_REJECTS_MUTABLE_BEGIN)
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
	TEST(ManualTest, ConstListAllowsCbegin) {

#if defined(ENABLE_CONST_LIST_ALLOWS_CBEGIN)
		const ScoreList list;
		ConstIterator it = list.cbegin();
		EXPECT_TRUE(it == list.cend());
#endif
		SUCCEED();
	}


	/**
	 * @brief constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
	 * @details ID:T040
	 *          コンパイルエラーになることを確認する
	 */
	TEST(ManualTest, ConstListRejectsMutableEnd) {

#if defined(ENABLE_CONST_LIST_REJECTS_MUTABLE_END)
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
	TEST(ManualTest, ConstListAllowsCend) {

#if defined(ENABLE_CONST_LIST_ALLOWS_CEND)
		const ScoreList list;
		ConstIterator it = list.cend();
		EXPECT_TRUE(it == list.cbegin());
#endif
		SUCCEED();
	}

}

namespace ex02_Iterator {

	/**
	 * @brief ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
	 * @details ID:T102
	 *          コンパイルエラーになることを確認する
	 */
	TEST(ManualTest, ConstIteratorRejectsAssignment) {

#if defined(ENABLE_CONST_ITERATOR_REJECTS_ASSIGNMENT)
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
	TEST(ManualTest, IteratorRejectsCopyFromConst) {

#if defined(ENABLE_ITERATOR_REJECTS_COPY_FROM_CONST)
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
	TEST(ManualTest, IteratorRejectsAssignFromConst) {
#if defined(ENABLE_ITERATOR_REJECTS_ASSIGN_FROM_CONST)
		Iterator it;
		ConstIterator cit;
		it = cit;
#endif
		SUCCEED();
	}

}

namespace ex03_QuickSort {

	/**
	 * @brief 型などが不適切なキー指定が引数で渡された時の挙動
	 * @details ID:T007
	 * 　　　　　コンパイルエラーとなる
	 */
	TEST(ManualTest, QuickSortRejectsInvalidKey) {
#if defined(ENABLE_QUICK_SORT_REJECTS_UNCOMPARABLE_KEY)
		{
			ScoreList list;
			//operator<で比較できないキー
			quickSort(list, [](const ScoreData& data) { return data; }); //ここでエラー
		}
#endif

#if defined(ENABLE_QUICK_SORT_REJECTS_WRONG_ARGUMENT_KEY)
		{
			ScoreList list;
			//要素を受け取れないキー関数
			quickSort(list, [](const char* name) { return name; }); //ここでエラー
		}
#endif
		SUCCEED();
	}


	/**
	 * @brief 非constのメソッドであるか
	 * @details ID:T008
	 * 　　　　　コンパイルエラーとなる
	 */
	TEST(ManualTest, QuickSortRejectsConstList) {
#if defined(ENABLE_QUICK_SORT_REJECTS_CONST_LIST)
		const ScoreList list;
		quickSort(list, [](const ScoreData& data) { return data.score; }); //ここでエラー
#endif
		SUCCEED();
	}

}

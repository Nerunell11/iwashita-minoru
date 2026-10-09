/********************************************************************************
 * @file TestHelper.h
 * @brief テスト用のヘルパー
 * @date 2026-10-07
 *********************************************************************************/
#pragma once
#include "gtest/gtest.h"
#include "DoublyLinkedList.h"
#include "ScoreData.h"
#include "QuickSort.h"

 //----------------------------------------------------------------------------------
 // エイリアス
 //----------------------------------------------------------------------------------

 //成績データを格納する双方向リスト
using ScoreList = DoublyLinkedList<ScoreData>;
using Iterator = ScoreList::Iterator;
using ConstIterator = ScoreList::ConstIterator;
using Result = ScoreList::Result;

//----------------------------------------------------------------------------------
// テスト用定数
//----------------------------------------------------------------------------------
const ScoreData kNew{ 0, "new" };
const ScoreData kFirst{ 1, "first" };
const ScoreData kSecond{ 2, "second" };
const ScoreData kThird{ 3, "third" };
const ScoreData kFourth{ 4, "fourth" };
const ScoreData kOther{ 100, "other" };

//----------------------------------------------------------------------------------
// リスト・イテレータ用ヘルパー関数
//----------------------------------------------------------------------------------

/**
 * @brief リストの末尾に要素を追加し、成功したことを確認する
 */
inline void PushBack(ScoreList& list, const ScoreData& data) {
	ASSERT_EQ(Result::Success, list.insert(list.end(), data));
}

/**
 * @brief 要素1つを比較する
 */
inline void ExpectData(const ScoreData& expected, const ScoreData& actual) {
	EXPECT_EQ(expected.score, actual.score);
	EXPECT_EQ(expected.userName, actual.userName);
}

/**
 * @brief リストの中身を先頭から比較する
 * @note 空であることは確認できない
 */
template <int N>
void ExpectElements(const ScoreList& list, const ScoreData(&expected)[N]) {
	ASSERT_EQ(N, list.size());
	ConstIterator it = list.cbegin();
	for (int i = 0; i < N; ++i) {
		SCOPED_TRACE(i);
		ASSERT_TRUE(it != list.cend());
		ExpectData(expected[i], *it);
		++it;
	}

	EXPECT_TRUE(it == list.cend());
}

/**
 * @brief 前後のリンクの整合性を確認する
 */
inline void ExpectLinksConsistent(const ScoreList& list) {
	int forward = 0;
	for (ConstIterator it = list.cbegin(); it != list.cend(); ++it) {
		++forward;
	}
	EXPECT_EQ(list.size(), forward);

	//後ろ向き
	int backward = 0;
	for (ConstIterator it = list.cend(); it != list.cbegin(); --it) {
		++backward;
	}
	EXPECT_EQ(list.size(), backward);

}

/**
 * @brief イテレータを進める・戻す
 */
template <class It>
It Next(It it, int n = 1) {
	for (int i = 0; i < n; ++i) {
		++it;
	}
	return it;
}

template <class It>
It Prev(It it, int n = 1) {
	for (int i = 0; i < n; ++i) {
		--it;
	}
	return it;
}

/**
 * @brief リスト末尾に3要素追加する
 */
inline void PushBackThreeItems(ScoreList& list) {
	ASSERT_NO_FATAL_FAILURE(PushBack(list, kFirst));
	ASSERT_NO_FATAL_FAILURE(PushBack(list, kSecond));
	ASSERT_NO_FATAL_FAILURE(PushBack(list, kThird));
}

/**
 * @brief 配列の要素を順にリスト末尾へ追加する
 */
 template <int N>
 void PushBackAll(ScoreList& list, const ScoreData(&data)[N]) {
	 for (int i = 0; i < N; ++i) {
		 ASSERT_NO_FATAL_FAILURE(PushBack(list, data[i]));
	 }
 }
 
 //----------------------------------------------------------------------------------
 // ソート用ヘルパー
 //----------------------------------------------------------------------------------
 
 /**
  * @brief スコアをキーとして取り出す
  */
 inline int ScoreKey(const ScoreData& data) {
	 return data.score;
 }
 
 /**
  * @brief ユーザー名をキーとして取り出す
  */
 inline const std::string& UserNameKey(const ScoreData& data) {
	 return data.userName;
 }
 
 /**
  * @brief リストがスコア順に並んでいるかを確認する
  * @note 同じスコアの要素同士の順序は問わない
  */
 inline void ExpectSortedByScore(const ScoreList& list, SortOrder order) {
	 if (list.cbegin() == list.cend()) {
		 return;
	 }
 
	 ConstIterator it = list.cbegin();
	 ConstIterator next = Next(it);
	 for (int i = 1; next != list.cend(); ++it, ++next, ++i) {
		 SCOPED_TRACE(i);
		 if (order == SortOrder::Ascending) {
			 EXPECT_LE((*it).score, (*next).score);
		 }
		 else {
			 EXPECT_GE((*it).score, (*next).score);
		 }
	 }
 }
 
 /**
  * @brief 並び順を問わず、期待した要素がちょうど1つずつ含まれているかを確認する
  * @note ソートで要素が消えたり重複したりしていないかの確認に使う
  */
 template <int N>
 void ExpectSameElements(const ScoreList& list, const ScoreData(&expected)[N]) {
	 ASSERT_EQ(N, list.size());
 
	 bool found[N] = {};
	 for (ConstIterator it = list.cbegin(); it != list.cend(); ++it) {
		 bool matched = false;
		 for (int i = 0; i < N; ++i) {
			 if (!found[i] && expected[i].score == (*it).score && expected[i].userName == (*it).userName) {
				 found[i] = true;
				 matched = true;
				 break;
			 }
		 }
		 EXPECT_TRUE(matched) << "想定外の要素: " << (*it).score << " " << (*it).userName;
	 }
 }

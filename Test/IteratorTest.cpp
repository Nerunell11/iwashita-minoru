/********************************************************************************
 * @file IteratorTest.cpp
 * @brief 自動テストコード
 * @date 2026-10-01
 *********************************************************************************/
#include "pch.h"
#include "TestHelper.h"

 //================================================================================
 // 参考文献:http://opencv.jp/googletestdocs/advancedguide.html
 // TYPED_TEST_CASE、TYPED_TESTを用いると、
 // 型に応じてテストを行うことができるため、採用しました
 //================================================================================

namespace Test_Iterator {

	/**
	 * @brief 型に応じた先頭イテレータを返す
	 */
	template <class T> T BeginOf(ScoreList& list);
	template <> Iterator BeginOf<Iterator>(ScoreList& list) { return list.begin(); }
	template <> ConstIterator BeginOf<ConstIterator>(ScoreList& list) { return list.cbegin(); }


	/**
	* @brief 型に応じた末尾イテレータを返す
	*/
	template <class T> T EndOf(ScoreList& list);
	template <> Iterator EndOf<Iterator>(ScoreList& list) { return list.end(); }
	template <> ConstIterator EndOf<ConstIterator>(ScoreList& list) { return list.cend(); }


	/**
	* @brief 空のリストを用意する型付きフィクスチャ
	* @tparam T Iterator または ConstIterator
	*/
	template <class T>
	class IteratorTest : public ::testing::Test {
	protected:
		void TearDown() override {
			ExpectLinksConsistent(list);
		}

		T Begin() { return BeginOf<T>(list); }   ///< 型に応じた先頭イテレータ
		T End() { return EndOf<T>(list); }       ///< 型に応じた末尾イテレータ

		ScoreList list;
	};


	/**
	* @brief 要素が2つのリストを用意する型付きフィクスチャ
	*/
	template <class T>
	class TwoItemIteratorTest : public IteratorTest<T> {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(IteratorTest<T>::SetUp());
			ASSERT_NO_FATAL_FAILURE(PushBack(this->list, kFirst));
			ASSERT_NO_FATAL_FAILURE(PushBack(this->list, kSecond));
		}
	};


	/**
	* @brief Death テスト用の型付きフィクスチャ
	*/
	template <class T>
	class IteratorDeathTest : public IteratorTest<T> {};


	/**
	* @brief 要素が1つのリストを用意するフィクスチャ
	*/
	class MutableIteratorTest : public ::testing::Test {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(PushBack(list, kFirst));
		}
		void TearDown() override {
			ExpectLinksConsistent(list);
		}

		ScoreList list;
	};

	using IteratorTypes = ::testing::Types<Iterator, ConstIterator>;
	TYPED_TEST_CASE(IteratorTest, IteratorTypes);
	TYPED_TEST_CASE(TwoItemIteratorTest, IteratorTypes);
	TYPED_TEST_CASE(IteratorDeathTest, IteratorTypes);


	//===================イテレータの指す要素を取得する======================
	namespace DereferenceTest {

		/**
		 * @brief リストの参照がない状態で呼び出した際の挙動をテスト
		 * @details ID:T100
		 *      Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, DereferenceWithoutOwnerAsserts) {
#ifndef NDEBUG
			TypeParam it;
			EXPECT_DEATH((void)*it, "hasOwner");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

		/**
		 * @brief Iteratorから取得した要素に対して、値の代入が行えるかをチェック
		 * @details ID:T101
		 * @note    代入後に再度呼び出し、値が変更されていることを確認
		 */
		TEST_F(MutableIteratorTest, DereferenceAllowsAssignment) {
			Iterator it = list.begin();
			(*it).score = 2;

			//代入後に再度呼び出し、値が変更されていること
			EXPECT_EQ(2, (*it).score);
			EXPECT_EQ(kFirst.userName, (*it).userName);

			//リストの要素そのものが書き換わっていること
			EXPECT_EQ(2, (*list.cbegin()).score);
		}

		/**
		 * @brief リストが空の際の、先頭イテレータに対して呼び出した際の挙動
		 * @details ID:T103
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, DereferenceBeginOfEmptyAsserts) {
#ifndef NDEBUG
			ASSERT_EQ(0, this->list.size());

			TypeParam it = this->Begin();
			EXPECT_DEATH((void)*it, "isEnd");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

		/**
		 * @brief 末尾イテレータに対して呼び出した際の挙動
		 * @details ID:T104
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, DereferenceEndAsserts) {
#ifndef NDEBUG
			ASSERT_NO_FATAL_FAILURE(PushBack(this->list, kFirst));

			TypeParam it = this->End();
			EXPECT_DEATH((void)*it, "isEnd");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

	}

	//===================イテレータをリストの末尾に向かって一つ進める=========
	namespace IncrementTest {

		/**
		 * @brief リストの参照がない状態で呼び出した際の挙動
		 * @details ID:T105
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, IncrementWithoutOwnerAsserts) {
#ifndef NDEBUG
			TypeParam it;
			EXPECT_DEATH(++it, "hasOwner");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

		/**
		 * @brief リストが空の際の、先頭イテレータに対して呼び出した際の挙動
		 * @details ID:T106
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, IncrementBeginOfEmptyAsserts) {
#ifndef NDEBUG
			ASSERT_EQ(0, this->list.size());

			TypeParam it = this->Begin();
			EXPECT_DEATH(++it, "isEnd");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}


		/**
		 * @brief 末尾イテレータに対して呼び出した際の挙動
		 * @details ID:T107
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, IncrementEndAsserts) {
#ifndef NDEBUG
			ASSERT_NO_FATAL_FAILURE(PushBack(this->list, kFirst));

			TypeParam it = this->End();
			EXPECT_DEATH(++it, "isEnd");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

		/**
		 * @brief リストに二つ以上の要素がある場合に呼び出した際の挙動
		 * @details ID:T108
		 *             次の要素を指す
		 * @note    リストの先頭から末尾まで呼び出しを行い、期待されている要素が格納されているかを確認
		 */
		TYPED_TEST(TwoItemIteratorTest, IncrementVisitsAllItems) {
			TypeParam it = this->Begin();
			ASSERT_TRUE(it != this->End());
			ExpectData(kFirst, *it);

			++it;
			ASSERT_TRUE(it != this->End());
			ExpectData(kSecond, *it);

			//末尾まで進むこと
			++it;
			EXPECT_TRUE(it == this->End());
		}

		/**
		 * @brief 前置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
		 * @details ID:T109
		 *             次の要素を指す
		 * @note    インクリメント呼び出し時の値と、インクリメント実行後の値の両方を確認
		 */
		TYPED_TEST(TwoItemIteratorTest, PreIncrementReturnsSelf) {
			TypeParam it = this->Begin();

			ConstIterator& result = ++it;

			//呼び出し時の値：自分自身の参照が返り、次の要素（second）を指していること
			EXPECT_EQ(static_cast<ConstIterator*>(&it), &result);
			ExpectData(kSecond, *result);

			//実行後の値：次の要素（second）を指していること
			ExpectData(kSecond, *it);
		}

		/**
		 * @brief 後置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
		 * @details ID:T110
		 *             次の要素を指す
		 * @note    インクリメント呼び出し時の値と、インクリメント実行後の値の両方を確認
		 */
		TYPED_TEST(TwoItemIteratorTest, PostIncrementReturnsOld) {
			TypeParam it = this->Begin();

			ConstIterator old = it++;

			//呼び出し時の値：進む前の位置（first）が返ること
			EXPECT_TRUE(old == this->Begin());
			ExpectData(kFirst, *old);

			//実行後の値：次の要素（second）を指していること
			EXPECT_TRUE(it == Next(this->Begin()));
			ExpectData(kSecond, *it);
		}
	}

	//===================イテレータをリストの先頭に向かって一つ進める=========
	namespace DecrementTest {


		/**
		 * @brief リストの参照がない状態で呼び出した際の挙動
		 * @details ID:T111
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, DecrementWithoutOwnerAsserts) {
#ifndef NDEBUG
			TypeParam it;
			EXPECT_DEATH(--it, "hasOwner");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";

#endif
		}

		/**
		 * @brief リストが空の際の、末尾イテレータに対して呼び出した際の挙動
		 * @details ID:T112
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, DecrementEndOfEmptyAsserts) {
#ifndef NDEBUG
			ASSERT_EQ(0, this->list.size());

			TypeParam it = this->End();
			EXPECT_DEATH(--it, "isBegin");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

		/**
		 * @brief 先頭イテレータに対して呼び出した際の挙動
		 * @details ID:T113
		 *             Assert発生
		 */
		TYPED_TEST(IteratorDeathTest, DecrementBeginAsserts) {
#ifndef NDEBUG
			ASSERT_NO_FATAL_FAILURE(PushBack(this->list, kFirst));

			TypeParam it = this->Begin();
			EXPECT_DEATH(--it, "isBegin");

#else
			SUCCEED() << "Releaseビルドではassertが無効のためスキップ";
#endif
		}

		/**
		 * @brief リストに二つ以上の要素がある場合に呼び出した際の挙動
		 * @details ID:T114
		 *             前の要素を指す
		 * @note    リストの末尾から先頭まで呼び出しを行い、期待されている要素が格納されているかを確認
		 */
		TYPED_TEST(TwoItemIteratorTest, DecrementVisitsAllItems) {
			TypeParam it = this->End();

			--it;
			ASSERT_TRUE(it != this->End());
			ExpectData(kSecond, *it);

			--it;
			ExpectData(kFirst, *it);

			//先頭まで戻ること
			EXPECT_TRUE(it == this->Begin());
		}

		/**
		 * @brief 前置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
		 * @details ID:T115
		 *             前の要素を指す
		 * @note    デクリメント呼び出し時の値と、デクリメント実行後の値の両方を確認
		 */
		TYPED_TEST(TwoItemIteratorTest, PreDecrementReturnsSelf) {
			TypeParam it = Prev(this->End());   //second を指している

			ConstIterator& result = --it;

			//呼び出し時の値：自分自身の参照が返り、前の要素（first）を指していること
			EXPECT_EQ(static_cast<ConstIterator*>(&it), &result);
			ExpectData(kFirst, *result);

			//実行後の値：前の要素（first）を指していること
			ExpectData(kFirst, *it);
		}

		/**
		 * @brief 後置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
		 * @details ID:T116
		 *             前の要素を指す
		 * @note    デクリメント呼び出し時の値と、デクリメント実行後の値の両方を確認
		 */
		TYPED_TEST(TwoItemIteratorTest, PostDecrementReturnsOld) {
			TypeParam it = Prev(this->End());   //second を指している

			ConstIterator old = it--;

			//呼び出し時の値：戻る前の位置（second）が返ること
			EXPECT_TRUE(old == Prev(this->End()));
			ExpectData(kSecond, *old);

			//実行後の値：前の要素（first）を指していること
			EXPECT_TRUE(it == this->Begin());
			ExpectData(kFirst, *it);
		}

	}

	//===================イテレータのコピーを行う======================
	namespace CopyTest {

		/**
		 * @brief コピーコンストラクト後の値がコピー元と等しいことをチェック
		 * @details ID:T118
		 */
		TYPED_TEST(TwoItemIteratorTest, CopyPointsToSameItem) {
			TypeParam it = this->Begin();
			TypeParam copy = it;

			//コピー元と同じ要素（first）を指していること
			EXPECT_TRUE(copy == it);
			ExpectData(kFirst, *copy);

			//コピーを進めても、コピー元は変わらないこと
			++copy;
			EXPECT_TRUE(it == this->Begin());
			ExpectData(kFirst, *it);
		}

	}


	//===================イテレータの代入を行う======================
	namespace AssignTest {

		/**
		 * @brief 代入後の値がコピー元と等しいことをチェック
		 * @details ID:T120
		 */
		TYPED_TEST(TwoItemIteratorTest, AssignPointsToSameItem) {
			TypeParam it = this->Begin();
			TypeParam copy = Next(this->Begin());   //代入前は別の要素（second）を指している
			ASSERT_TRUE(copy != it);

			copy = it;

			//代入元と同じ要素（first）を指していること
			EXPECT_TRUE(copy == it);
			ExpectData(kFirst, *copy);

			//代入先を進めても、代入元は変わらないこと
			++copy;
			EXPECT_TRUE(it == this->Begin());
			ExpectData(kFirst, *it);
		}
	}


	//===================2つのイテレータが同一であるか比較を行う======================
	namespace EqualTest {

		/**
		 * @brief リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
		 * @details ID:T121
		 *           True:成功, False:失敗
		 */
		TYPED_TEST(IteratorTest, EqualIsTrueForEmptyBeginEnd) {
			ASSERT_EQ(0, this->list.size());

			TypeParam it = this->Begin();
			EXPECT_TRUE(it == this->End());
		}

		/**
		 * @brief 同一のイテレータを比較した際の挙動をチェック
		 * @details ID:T122
		 *           True:成功, False:失敗
		 */
		TYPED_TEST(TwoItemIteratorTest, EqualIsTrueForSameItem) {
			TypeParam a = this->Begin();
			TypeParam b = this->Begin();
			EXPECT_TRUE(a == b);
		}

		/**
		 * @brief 異なるイテレータを比較した際の挙動をチェック
		 * @details ID:T123
		 *           True:失敗, False:成功
		 */
		TYPED_TEST(TwoItemIteratorTest, EqualIsFalseForDifferentItems) {
			TypeParam a = this->Begin();
			TypeParam b = Next(this->Begin());
			ASSERT_TRUE(b != this->End());

			EXPECT_FALSE(a == b);
		}

	}

	//===================2つのイテレータが異なるか比較を行う======================
	namespace NotEqualTest {

		/**
		 * @brief リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
		 * @details ID:T124
		 *           True:失敗, False:成功
		 */
		TYPED_TEST(IteratorTest, NotEqualIsFalseForEmptyBeginEnd) {
			ASSERT_EQ(0, this->list.size());

			TypeParam it = this->Begin();
			EXPECT_FALSE(it != this->End());
		}

		/**
		 * @brief 同一のイテレータを比較した際の挙動をチェック
		 * @details ID:T125
		 *           True:失敗, False:成功
		 */
		TYPED_TEST(TwoItemIteratorTest, NotEqualIsFalseForSameItem) {
			TypeParam a = this->Begin();
			TypeParam b = this->Begin();
			EXPECT_FALSE(a != b);
		}

		/**
		 * @brief 異なるイテレータを比較した際の挙動をチェック
		 * @details ID:T126
		 *           True:成功, False:失敗
		 */
		TYPED_TEST(TwoItemIteratorTest, NotEqualIsTrueForDifferentItems) {
			TypeParam a = this->Begin();
			TypeParam b = Next(this->Begin());
			ASSERT_FALSE(b == this->End());

			EXPECT_TRUE(a != b);
		}
	}
}

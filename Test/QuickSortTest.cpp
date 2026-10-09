/********************************************************************************
 * @file QuickSortTest.cpp
 * @brief 自動テストコード
 * @date 2026-10-08
 *********************************************************************************/
#include "pch.h"
#include "TestHelper.h"
#include "ManualTest.h"


namespace Test_QuickSort
{

	//===================フィクスチャ===========================================

	const ScoreData kFifth{ 5, "fifth" };

	//同じスコアを持つ要素
	const ScoreData kDupA{ 2, "dupA" };
	const ScoreData kDupB{ 2, "dupB" };
	const ScoreData kDupC{ 2, "dupC" };

	/**
	 * @brief ソート用の空のリストを用意するフィクスチャ
	 * @note Test_List側のEmptyListTestとスイート名が衝突しないよう別名にしている
	 */
	class SortEmptyListTest : public ::testing::Test {
	protected:
		void TearDown() override {
			ExpectLinksConsistent(list);
		}

		ScoreList list;
	};

	/**
	 * @brief ソート用の1つの要素を持つリストを用意するフィクスチャ
	 */
	class SortOneItemListTest : public SortEmptyListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(SortEmptyListTest::SetUp());
			ASSERT_NO_FATAL_FAILURE(PushBack(list, kFirst));
		}
	};

	/**
	 * @brief 整列されていない4つの要素を持つリストを用意するフィクスチャ
	 * @note 並び: third, first, fourth, second
	 */
	class UnsortedListTest : public SortEmptyListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(SortEmptyListTest::SetUp());
			const ScoreData data[] = { kThird, kFirst, kFourth, kSecond };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(list, data));
		}
	};

	/**
	 * @brief 同じスコアの要素を含むリストを用意するフィクスチャ
	 * @note 並び: dupA(2), third(3), dupB(2), first(1), dupC(2)
	 */
	class DuplicateKeyListTest : public SortEmptyListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(SortEmptyListTest::SetUp());
			const ScoreData data[] = { kDupA, kThird, kDupB, kFirst, kDupC };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(list, data));
		}
	};

	/**
	 * @brief スコア昇順に整列済みで、重複のない4つの要素を持つリストを用意するフィクスチャ
	 * @note 並び: first, second, third, fourth
	 */
	class SortedListTest : public SortEmptyListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(SortEmptyListTest::SetUp());
			const ScoreData data[] = { kFirst, kSecond, kThird, kFourth };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(list, data));
		}
	};


	//===================クイックソート===========================================

	/**
	 * @brief 要素を持たないリストにソートを実行した時の挙動
	 * @details ID:T000
	 * 　　　　　エラー含めて、何も起こらない
	 */
	TEST_F(SortEmptyListTest, SortEmptyDoesNothing) {
		//昇順
		{
			SCOPED_TRACE("昇順");
			quickSort(list, ScoreKey, SortOrder::Ascending);
			EXPECT_EQ(0, list.size());
			EXPECT_TRUE(list.begin() == list.end());
		}

		//降順
		{
			SCOPED_TRACE("降順");
			quickSort(list, ScoreKey, SortOrder::Descending);
			EXPECT_EQ(0, list.size());
			EXPECT_TRUE(list.begin() == list.end());
		}
	}


	/**
	 * @brief 要素を1つだけ持つリストにソートを実行した時の挙動
	 * @details ID:T001
	 * 　　　　　エラー含めて、何も起こらない
	 */
	TEST_F(SortOneItemListTest, SortOneItemDoesNothing) {
		//昇順
		{
			SCOPED_TRACE("昇順");
			quickSort(list, ScoreKey, SortOrder::Ascending);
			const ScoreData expected[] = { kFirst };
			ExpectElements(list, expected);
		}

		//降順
		{
			SCOPED_TRACE("降順");
			quickSort(list, ScoreKey, SortOrder::Descending);
			const ScoreData expected[] = { kFirst };
			ExpectElements(list, expected);
		}
	}


	/**
	 * @brief 2つ以上要素を持つリストにソートを実行した時の挙動
	 * @details ID:T002
	 * 　　　　　要素が指定したキーに準じて指定した順に並ぶ
	 * @note    先頭から順にイテレータで確認し、ノードの差し替えが
	 * 　　　　　正常に行えているかをチェック
	 */
	TEST(UnsortedListTest, SortArrangesByKey) {
		//スコア昇順
		{
			SCOPED_TRACE("スコア昇順");
			ScoreList target;
			const ScoreData data[] = { kThird, kFirst, kFourth, kSecond };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(target, data));

			quickSort(target, ScoreKey, SortOrder::Ascending);

			const ScoreData expected[] = { kFirst, kSecond, kThird, kFourth };
			ExpectElements(target, expected);
			ExpectLinksConsistent(target);
		}

		//スコア降順
		{
			SCOPED_TRACE("スコア降順");
			ScoreList target;
			const ScoreData data[] = { kThird, kFirst, kFourth, kSecond };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(target, data));

			quickSort(target, ScoreKey, SortOrder::Descending);

			const ScoreData expected[] = { kFourth, kThird, kSecond, kFirst };
			ExpectElements(target, expected);
			ExpectLinksConsistent(target);
		}

		//ユーザー名昇順
		{
			SCOPED_TRACE("ユーザー名昇順");
			ScoreList target;
			const ScoreData data[] = { kThird, kFirst, kFourth, kSecond };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(target, data));

			quickSort(target, UserNameKey, SortOrder::Ascending);

			//"first" < "fourth" < "second" < "third"
			const ScoreData expected[] = { kFirst, kFourth, kSecond, kThird };
			ExpectElements(target, expected);
			ExpectLinksConsistent(target);
		}

		//ユーザー名降順
		{
			SCOPED_TRACE("ユーザー名降順");
			ScoreList target;
			const ScoreData data[] = { kThird, kFirst, kFourth, kSecond };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(target, data));

			quickSort(target, UserNameKey, SortOrder::Descending);

			const ScoreData expected[] = { kThird, kSecond, kFourth, kFirst };
			ExpectElements(target, expected);
			ExpectLinksConsistent(target);
		}
	}

	/**
	 * @brief 同じキーを持つ要素があるリストで、そのキーを指定しソートを実行した時の挙動
	 * @details ID:T003
	 * 　　　　　要素がソートされて並ぶが、同じ要素の順序は保証されない
	 */
	TEST_F(DuplicateKeyListTest, SortWithDuplicateKeys) {
		const ScoreData all[] = { kDupA, kThird, kDupB, kFirst, kDupC };

		//昇順
		{
			SCOPED_TRACE("昇順");
			quickSort(list, ScoreKey, SortOrder::Ascending);

			//スコア順に並んでいること（同じスコア同士の順序は問わない）
			ExpectSortedByScore(list, SortOrder::Ascending);

			//要素が欠けたり重複したりしていないこと
			ExpectSameElements(list, all);

			//重複のない要素は位置が確定すること
			ExpectData(kFirst, *list.begin());
			ExpectData(kThird, *Prev(list.end()));
		}

		//降順
		{
			SCOPED_TRACE("降順");
			quickSort(list, ScoreKey, SortOrder::Descending);

			ExpectSortedByScore(list, SortOrder::Descending);
			ExpectSameElements(list, all);
			ExpectData(kThird, *list.begin());
			ExpectData(kFirst, *Prev(list.end()));
		}
	}

	/**
	 * @brief 整列済みリストにソートを実行した時の挙動
	 * @details ID:T004
	 * 　　　　　同じキーの要素の間以外の順番が変動しない
	 * @note    重複要素なしの整列済みリストを使う
	 */
	TEST_F(SortedListTest, SortSortedKeepsOrder) {
		//昇順に整列済みのリストを昇順でソート
		{
			SCOPED_TRACE("昇順に整列済みのリストを昇順でソート");
			quickSort(list, ScoreKey, SortOrder::Ascending);

			const ScoreData expected[] = { kFirst, kSecond, kThird, kFourth };
			ExpectElements(list, expected);
		}

		//降順に整列済みのリストを降順でソート
		{
			SCOPED_TRACE("降順に整列済みのリストを降順でソート");
			ScoreList descList;
			const ScoreData data[] = { kFourth, kThird, kSecond, kFirst };
			ASSERT_NO_FATAL_FAILURE(PushBackAll(descList, data));

			quickSort(descList, ScoreKey, SortOrder::Descending);

			ExpectElements(descList, data);
			ExpectLinksConsistent(descList);
		}
	}

	/**
	 * @brief 一度整列したリストの各所に挿入し、再度ソートを実行した時の挙動
	 * @details ID:T005
	 * 　　　　　要素がソートされて並ぶ
	 * @note    重複要素なしの整列済みリストを使う
	 */
	TEST_F(SortedListTest, SortAfterInsert) {
		//一度整列する
		quickSort(list, ScoreKey, SortOrder::Ascending);

		//先頭に挿入：5, 1, 2, 3, 4
		ASSERT_EQ(Result::Success, list.insert(list.begin(), kFifth));

		//中央に挿入：5, 1, 2, 100, 3, 4
		ASSERT_EQ(Result::Success, list.insert(Next(list.begin(), 3), kOther));

		//末尾に挿入：5, 1, 2, 100, 3, 4, 0
		ASSERT_EQ(Result::Success, list.insert(list.end(), kNew));

		//再度ソートする
		quickSort(list, ScoreKey, SortOrder::Ascending);

		const ScoreData expected[] = { kNew, kFirst, kSecond, kThird, kFourth, kFifth, kOther };
		ExpectElements(list, expected);
	}

	/**
	 * @brief キー指定をしなかった(nullptrを渡した)時の挙動
	 * @details ID:T006
	 * 　　　　　エラー含めて、何も起こらない
	 */
	TEST_F(UnsortedListTest, NullKeyDoesNothing) {
		quickSort(list, nullptr);
		quickSort(list, nullptr, SortOrder::Descending);

		//中身と順番が変わっていないこと
		const ScoreData expected[] = { kThird, kFirst, kFourth, kSecond };
		ExpectElements(list, expected);
	}

	/**
	 * @brief 型などが不適切なキー指定が引数で渡された時の挙動
	 * @details ID:T007
	 * 　　　　　コンパイルエラーとなる
	 */
	TEST(ManualTest, QuickSortRejectsInvalidKey) {
		//  #if defined(ENABLE_QUICK_SORT_REJECTS_UNCOMPARABLE_KEY)
		//          //operator<で比較できないキー
		//          ScoreList list;
		//          quickSort(list, [](const ScoreData& data) { return data; }); //ここでエラー
		//  #endif

		//  #if defined(ENABLE_QUICK_SORT_REJECTS_WRONG_ARGUMENT_KEY)
		//          //要素を受け取れないキー関数
		//          ScoreList list2;
		//          quickSort(list2, [](const char* name) { return name; }); //ここでエラー
		//  #endif
		SUCCEED();
	}

	/**
	 * @brief 非constのメソッドであるか
	 * @details ID:T008
	 * 　　　　　コンパイルエラーとなる
	 */
	TEST(ManualTest, QuickSortRejectsConstList) {
		//  #if defined(ENABLE_QUICK_SORT_REJECTS_CONST_LIST)
		//          const ScoreList list;
		//          quickSort(list, ScoreKey); //ここでエラー
		//  #endif
		SUCCEED();
	}

}

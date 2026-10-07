/********************************************************************************
 * @file ListTest.cpp
 * @brief 自動テストコード
 * @date 2026-10-01
 *********************************************************************************/
#include "pch.h"
#include "TestHelper.h"


namespace Test_List
{

	/**
	 * @brief 空のリストを用意するフィクスチャ
	 */
	class EmptyListTest : public ::testing::Test {
	protected:
		void TearDown() override {
			ExpectLinksConsistent(list);
		}

		ScoreList list;
		const ScoreList& clist = list;
	};

	/**
	 * @brief 1つの要素を持つリストを用意するフィクスチャ
	 */
	class OneItemListTest : public EmptyListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(EmptyListTest::SetUp());
			ASSERT_NO_FATAL_FAILURE(PushBack(list, kFirst));
		}
	};

	/**
	 * @brief 2つの要素を持つリストを用意するフィクスチャ
	 */
	class TwoItemListTest : public OneItemListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(OneItemListTest::SetUp());
			ASSERT_NO_FATAL_FAILURE(PushBack(list, kSecond));
		}
	};

	/**
	 * @brief 3つの要素を持つリストを用意するフィクスチャ
	 */
	class ThreeItemListTest : public TwoItemListTest {
	protected:
		void SetUp() override {
			ASSERT_NO_FATAL_FAILURE(TwoItemListTest::SetUp());
			ASSERT_NO_FATAL_FAILURE(PushBack(list, kThird));
		}
	};


	//===================データ数の取得==================
	namespace GetDataCountTest {

		/**
		 * @brief　リストが空である場合のデータ数の取得テスト
		 * @details ID:T000
		 * 　　　　　データ数が0であれば成功
		 */
		TEST_F(EmptyListTest, SizeIsZero) {
			EXPECT_EQ(0, list.size());
		}


		/**
		 * @brief  リスト末尾への挿入を行った際のデータ数の取得テスト
		 * @details ID:T001
		 *          データ数が1であれば成功
		 */
		TEST_F(EmptyListTest, InsertAtEndAddsOne) {
			ASSERT_EQ(Result::Success, list.insert(list.end(), kFirst));
			EXPECT_EQ(1, list.size());
		}

		/**
		 * @brief リスト末尾への挿入が失敗した際のデータ数の取得テスト
		 * @details ID:T002
		 *          データ数が0であれば成功
		 */
		TEST_F(EmptyListTest, AllocFailureKeepsZero) {
			// //メモリ確保を失敗させる
			// g_failNextAlloc = true;
			//
			// //末尾への挿入で、メモリ確保の失敗により例外が投げられること
			// EXPECT_THROW(list.insert(list.end(), kFirst), std::bad_alloc);
			// g_failNextAlloc = false;
			//
			// //データ数が0のままであること
			// EXPECT_EQ(0, list.size());
			//
			// //リストの状態が変わっていないこと
			// EXPECT_TRUE(list.begin() == list.end());
			SUCCEED() << "末尾への挿入失敗はメモリ確保失敗時の為、スキップ";
		}

		/**
		 * @brief データの挿入を行った際のデータ数の取得テスト
		 * @details ID:T003
		 *          データ数が1であれば成功
		 */
		TEST_F(EmptyListTest, InsertAtBeginAddsOne) {
			ASSERT_EQ(Result::Success, list.insert(list.begin(), kFirst));
			EXPECT_EQ(1, list.size());
		}

		/**
		 * @brief データの挿入に失敗した際のデータ数の取得テスト
		 * @details ID:T004
		 *          データ数が0であれば成功
		 */
		TEST_F(EmptyListTest, InvalidInsertKeepsZero) {
			Iterator invalid;
			EXPECT_EQ(Result::NoOwner, list.insert(invalid, kFirst));
			EXPECT_EQ(0, list.size());
		}

		/**
		 * @brief データの削除を行った際のデータ数の取得テスト
		 * @details ID:T005
		 *          データ数が0であれば成功
		 */
		TEST_F(OneItemListTest, EraseRemovesOne) {
			ASSERT_EQ(Result::Success, list.erase(list.begin()));
			EXPECT_EQ(0, list.size());
			EXPECT_TRUE(list.begin() == list.end());
		}

		/**
		 * @brief データの削除が失敗した際のデータ数の取得テスト
		 * @details ID:T006
		 *          データ数が1であれば成功
		 *@note データを挿入した後、削除した場合
		 */
		TEST_F(OneItemListTest, InvalidEraseKeepsOne) {
			Iterator invalid;
			EXPECT_EQ(Result::NoOwner, list.erase(invalid));
			EXPECT_EQ(1, list.size());

			//中身が変わっていないこと
			const ScoreData expected[] = { kFirst };
			ExpectElements(list, expected);
		}

		/**
		 * @brief リストが空である場合に、データの取得を行った際のデータ数の取得テスト
		 * @details ID:T007
		 *          データ数が0であれば成功
		 * @note マイナスにならないかどうか
		 */
		TEST_F(EmptyListTest, EraseOnEmptyKeepsZero) {
			EXPECT_EQ(Result::EndIterator, list.erase(list.begin()));
			EXPECT_EQ(0, list.size());
		}

	}

	//===================データの挿入===================
	namespace InsertTest {

		/**
		 * @brief リストが空である場合に、挿入した際の挙動をテスト
		 * @details ID:T009
		 *          イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
		 * @note    先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックすること
		 * @return  True:成功, False:失敗
		 */
		TEST_F(EmptyListTest, InsertPlacesItem) {
			//先頭イテレータを渡すケース
			{
				SCOPED_TRACE("先頭イテレータを渡すケース");
				Iterator pos = list.begin();
				Iterator inserted;
				ASSERT_EQ(Result::Success, list.insert(pos, kNew, &inserted));

				//イテレータの指す位置に挿入されていること
				EXPECT_TRUE(inserted == list.begin());

				//その位置にあったものが、後ろにズレていること
				EXPECT_TRUE(Next(inserted) == pos);
				EXPECT_TRUE(pos == list.end());

				const ScoreData expected[] = { kNew };
				ExpectElements(list, expected);
			}

			//末尾イテレータを渡すケース
			{
				SCOPED_TRACE("末尾イテレータを渡すケース");
				ScoreList endList;
				Iterator pos = endList.end();
				Iterator inserted;
				ASSERT_EQ(Result::Success, endList.insert(pos, kNew, &inserted));

				//イテレータの指す位置に挿入されていること
				EXPECT_TRUE(inserted == endList.begin());

				//その位置にあったものが、後ろにズレていること
				EXPECT_TRUE(Next(inserted) == pos);
				EXPECT_TRUE(pos == endList.end());

				const ScoreData expected[] = { kNew };
				ExpectElements(endList, expected);
				ExpectLinksConsistent(endList);

			}
		}

		/**
		 * @brief リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動をテスト
		 * @details ID:T010
		 *          先頭に要素が挿入され、元々先頭だった要素が２番目になる。
		 * @return  True:成功, False:失敗
		 */
		TEST_F(TwoItemListTest, InsertAtBeginShiftsItems) {
			Iterator pos = list.begin();
			Iterator inserted;
			ASSERT_EQ(Result::Success, list.insert(pos, kNew, &inserted));

			//挿入した要素が先頭にあること
			EXPECT_TRUE(inserted == list.begin());

			//元々先頭だった要素が後ろにずれていること
			EXPECT_TRUE(Next(inserted) == pos);
			ExpectData(kFirst, *pos);

			//全体の並びを確認
			const ScoreData expected[] = { kNew, kFirst, kSecond };
			ExpectElements(list, expected);

		}

		/**
		 * @brief リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動をテスト
		 * @details ID:T011
		 *          イテレータの指す位置に要素が挿入される
		 * @return  True:成功, False:失敗
		 */
		TEST_F(TwoItemListTest, InsertAtEndAppendsItem) {
			Iterator pos = list.end();
			Iterator inserted;
			ASSERT_EQ(Result::Success, list.insert(pos, kNew, &inserted));

			//挿入した要素が末尾にあること
			EXPECT_TRUE(inserted == Prev(list.end()));

			//挿入した要素の後ろが末尾のままであること
			EXPECT_TRUE(Next(inserted) == pos);
			EXPECT_TRUE(pos == list.end());

			//全体の並び
			const ScoreData expected[] = { kFirst, kSecond, kNew };
			ExpectElements(list, expected);
		}

		/**
		 * @brief リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動をテスト
		 * @details ID:T012
		 *          イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
		 * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか。要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
		 * @return  True:成功, False:失敗
		 */
		TEST_F(ThreeItemListTest, InsertInMiddleShiftsItems) {
			Iterator pos = Next(list.begin());
			Iterator inserted;
			ASSERT_EQ(Result::Success, list.insert(pos, kNew, &inserted));

			//挿入した要素が2番目にあること
			EXPECT_TRUE(inserted == Next(list.begin()));

			//元々2番目だった要素が後ろにずれていること
			EXPECT_TRUE(Next(inserted) == pos);
			ExpectData(kSecond, *pos);

			//全体の並び
			const ScoreData expected[] = { kFirst, kNew, kSecond, kThird };
			ExpectElements(list, expected);

		}

		/**
		 * @brief ConstIteratorを指定して挿入を行った際の挙動をテスト
		 * @details ID:T013
		 *          イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
		 * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか。要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
		 * @return  True:成功, False:失敗
		 */
		TEST_F(ThreeItemListTest, ConstInsertShiftsItems) {
			//先頭に挿入するケース
			{
				SCOPED_TRACE("先頭に挿入するケース");
				ConstIterator pos = clist.cbegin();
				Iterator inserted;
				ASSERT_EQ(Result::Success, list.insert(pos, kNew, &inserted));

				//挿入した要素が先頭にあること
				EXPECT_TRUE(inserted == clist.cbegin());

				//元々先頭だった要素が後ろにずれていること
				EXPECT_TRUE(Next(inserted) == pos);
				ExpectData(kFirst, *pos);

				//全体の並び
				const ScoreData expected[] = { kNew, kFirst, kSecond, kThird };
				ExpectElements(list, expected);
			}

			//中央に挿入するケース
			{
				SCOPED_TRACE("中央に挿入するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));

				ConstIterator pos = Next(midList.cbegin());
				Iterator inserted;
				ASSERT_EQ(Result::Success, midList.insert(pos, kNew, &inserted));

				//挿入した要素が2番目にあること
				EXPECT_TRUE(inserted == Next(midList.cbegin()));

				//元々2番目だった要素が後ろにずれていること
				EXPECT_TRUE(Next(inserted) == pos);
				ExpectData(kSecond, *pos);

				//全体の並び
				const ScoreData expected[] = { kFirst, kNew, kSecond, kThird };
				ExpectElements(midList, expected);
				ExpectLinksConsistent(midList);
			}

			//末尾に挿入するケース
			{
				SCOPED_TRACE("末尾に挿入するケース");
				ScoreList endList;
				PushBackThreeItems(endList);

				ConstIterator pos = endList.cend();
				Iterator inserted;
				ASSERT_EQ(Result::Success, endList.insert(pos, kNew, &inserted));

				//挿入した要素が末尾にあること
				EXPECT_TRUE(inserted == Prev(endList.cend()));

				//挿入した要素が末尾のままであること
				EXPECT_TRUE(Next(inserted) == pos);
				EXPECT_TRUE(pos == endList.cend());

				//全体の並び
				const ScoreData expected[] = { kFirst, kSecond, kThird, kNew };
				ExpectElements(endList, expected);
				ExpectLinksConsistent(endList);
			}
		}

		/**
		 * @brief 不正なイテレータを渡して挿入を行った際の挙動をテスト
		 * @details ID:T014
		 *          何も起こらない
		 * @note    リストの参照がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動など
		 * @return  True:失敗, False:成功
		 */
		TEST_F(TwoItemListTest, InvalidInsertChangesNothing) {
			//リストの参照がないイテレータ
			{
				SCOPED_TRACE("リストの参照がないイテレータ");
				Iterator invalid;
				EXPECT_EQ(Result::NoOwner, list.insert(invalid, kNew));

				//既存要素が変わっていないこと
				const ScoreData expected[] = { kFirst, kSecond };
				ExpectElements(list, expected);
			}

			//別リストの要素を指すイテレータ
			{
				SCOPED_TRACE("別リストの要素を指すイテレータ");
				ScoreList other;
				ASSERT_NO_FATAL_FAILURE(PushBack(other, kOther));
				EXPECT_EQ(Result::OtherList, list.insert(other.begin(), kNew));

				//どちらのリストにも挿入されていないこと
				const ScoreData expected[] = { kFirst, kSecond };
				ExpectElements(list, expected);
				const ScoreData expectedOther[] = { kOther };
				ExpectElements(other, expectedOther);

			}
		}

	}


	//===================データの削除===================
	namespace EraseTest {

		/**
		 * @brief リストが空である場合に、削除を行った際の挙動をテスト
		 * @details ID:T016
		 *          何も起こらない
		 * @note    先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックすること
		 * @return  True:失敗, False:成功
		 */
		TEST_F(EmptyListTest, EraseOnEmptyReturnsEnd) {
			//先頭イテレータを渡すケース
			{
				SCOPED_TRACE("先頭イテレータを渡すケース");
				EXPECT_EQ(Result::EndIterator, list.erase(list.begin()));

				//空のままであること
				EXPECT_EQ(0, list.size());
				EXPECT_TRUE(list.begin() == list.end());
			}

			//末尾イテレータを渡すケース
			{
				SCOPED_TRACE("末尾イテレータを渡すケース");
				EXPECT_EQ(Result::EndIterator, list.erase(list.end()));

				//空のままであること
				EXPECT_EQ(0, list.size());
				EXPECT_TRUE(list.begin() == list.end());
			}
		}

		/**
		 * @brief 先頭要素の削除を行った際の挙動をテスト
		 * @details ID:T017
		 *          先頭要素が削除され、次の要素が先頭になる
		 * @return  True:成功, False:失敗
		 */
		TEST_F(TwoItemListTest, EraseBeginMakesNextFirst) {
			Iterator next;
			ASSERT_EQ(Result::Success, list.erase(list.begin(), &next));

			//次の要素が先頭になっていること
			EXPECT_TRUE(next == list.begin());
			ExpectData(kSecond, *next);

			//全体の並び
			const ScoreData expected[] = { kSecond };
			ExpectElements(list, expected);
		}

		/**
		 * @brief リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
		 * @details ID:T018
		 *          何も起こらない
		 * @return  True:失敗, False:成功
		 */
		TEST_F(TwoItemListTest, EraseEndChangesNothing) {
			//末尾イテレータを渡して削除できないこと
			EXPECT_EQ(Result::EndIterator, list.erase(list.end()));

			//中身と順番が変わっていないこと
			const ScoreData expected[] = { kFirst, kSecond };
			ExpectElements(list, expected);
		}


		/**
		 * @brief リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
		 * @details ID:T019
		 *          指定要素の削除
		 * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか
		 * @return  True:成功, False:失敗
		 */
		TEST_F(ThreeItemListTest, EraseMiddleLinksNeighbors) {
			Iterator pos = Next(list.begin());
			Iterator next;
			ASSERT_EQ(Result::Success, list.erase(pos, &next));

			//戻り値が削除した要素の次（third）を指していること
			EXPECT_TRUE(next == Next(list.begin()));
			ExpectData(kThird, *next);

			//前後の要素がつながっていること
			EXPECT_TRUE(Prev(next) == list.begin());

			//全体の並び
			const ScoreData expected[] = { kFirst, kThird };
			ExpectElements(list, expected);
		}

		/**
		 * @brief ConstIteratorを指定して削除を行った際の挙動をテスト
		 * @details ID:T020
		 *          指定要素の削除
		 * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか
		 * @return  True:成功, False:失敗
		 */
		TEST_F(ThreeItemListTest, ConstEraseLinksNeighbors) {
			ConstIterator pos = Next(clist.cbegin());
			Iterator next;
			ASSERT_EQ(Result::Success, list.erase(pos, &next));

			//削除した要素の次を指していること
			EXPECT_TRUE(next == Next(clist.cbegin()));
			ExpectData(kThird, *next);

			//前後の要素がつながっていること
			EXPECT_TRUE(Prev(next) == clist.cbegin());

			//全体の並び
			const ScoreData expected[] = { kFirst, kThird };
			ExpectElements(list, expected);
		}

		/**
		 * @brief 不正なイテレータを渡して、削除した場合の挙動
		 * @details ID:T021
		 *          何も起こらない
		 * @note    リストの参照がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動など
		 * @return  True:失敗, False:成功
		 */
		TEST_F(TwoItemListTest, InvalidEraseChangesNothing) {
			//リストの参照がないイテレータ
			{
				SCOPED_TRACE("リストの参照がないイテレータ");
				Iterator invalid;
				EXPECT_EQ(Result::NoOwner, list.erase(invalid));

				//失敗時は出力先のイテレータが変更されないこと
				Iterator out = list.begin();
				EXPECT_EQ(Result::NoOwner, list.erase(invalid, &out));
				EXPECT_TRUE(out == list.begin());

				//既存要素が変わっていないこと
				const ScoreData expected[] = { kFirst, kSecond };
				ExpectElements(list, expected);
			}

			//別リストの要素を指すイテレータ
			{
				SCOPED_TRACE("別リストの要素を指すイテレータ");
				ScoreList other;
				ASSERT_NO_FATAL_FAILURE(PushBack(other, kOther));
				EXPECT_EQ(Result::OtherList, list.erase(other.begin()));

				//どちらのリストからも削除されていないこと
				const ScoreData expected[] = { kFirst, kSecond };
				ExpectElements(list, expected);
				const ScoreData expectedOther[] = { kOther };
				ExpectElements(other, expectedOther);
			}

		}

	}

	//===================先頭イテレータの取得======================
	namespace BeginTest {

		/**
		 * @brief リストが空である場合に、呼び出した際の挙動
		 * @details ID:T023
		 *          ダミーノードを指すイテレータが返る
		 * @return  Iterator
		 */
		TEST_F(EmptyListTest, BeginEqualsEnd) {
			Iterator it = list.begin();
			EXPECT_TRUE(it == list.end());
		}

		/**
		 * @brief リストに要素が一つある場合に、呼び出した際の挙動
		 * @details ID:T024
		 *          先頭要素を指すイテレータが返る
		 * @return  Iterator
		 */
		TEST_F(OneItemListTest, BeginPointsToOnlyItem) {
			Iterator it = list.begin();
			ExpectData(kFirst, *it);

			//次が末尾であること
			EXPECT_TRUE(Next(it) == list.end());
		}


		/**
		 * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
		 * @details ID:T025
		 *          先頭要素を指すイテレータが返る
		 * @return  Iterator
		 */
		TEST_F(TwoItemListTest, BeginPointsToFirstItem) {
			Iterator it = list.begin();
			ExpectData(kFirst, *it);

			//先頭から順にたどれること
			ExpectData(kSecond, *Next(it));
			EXPECT_TRUE(Next(it, 2) == list.end());
		}

		/**
		 * @brief データの挿入を行った後に、呼び出した際の挙動
		 * @details ID:T026
		 *          先頭要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
		 * @return  Iterator
		 */
		TEST_F(ThreeItemListTest, BeginFollowsInsert) {
			//先頭に挿入するケース
			{
				SCOPED_TRACE("先頭に挿入するケース");
				Iterator inserted;
				ASSERT_EQ(Result::Success, list.insert(list.begin(), kNew, &inserted));

				//挿入した要素が先頭になること
				EXPECT_TRUE(list.begin() == inserted);
				ExpectData(kNew, *list.begin());
			}

			//中央に挿入するケース
			{
				SCOPED_TRACE("中央に挿入するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				Iterator oldBegin = midList.begin();

				ASSERT_EQ(Result::Success, midList.insert(Next(midList.begin()), kNew));

				//先頭は変わらないこと
				EXPECT_TRUE(midList.begin() == oldBegin);
				ExpectData(kFirst, *midList.begin());
				ExpectLinksConsistent(midList);
			}

			//末尾に挿入するケース
			{
				SCOPED_TRACE("末尾に挿入するケース");
				ScoreList endList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(endList));
				Iterator oldBegin = endList.begin();

				ASSERT_EQ(Result::Success, endList.insert(endList.end(), kNew));

				//先頭は変わらないこと
				EXPECT_TRUE(endList.begin() == oldBegin);
				ExpectData(kFirst, *endList.begin());
				ExpectLinksConsistent(endList);
			}
		}

		/**
		 * @brief データの削除を行った後に、呼び出した際の挙動
		 * @details ID:T027
		 *          先頭要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
		 * @return  Iterator
		 */
		TEST_F(ThreeItemListTest, BeginFollowsErase) {
			//先頭を削除するケース
			{
				SCOPED_TRACE("先頭を削除するケース");
				Iterator next;
				ASSERT_EQ(Result::Success, list.erase(list.begin(), &next));

				//削除した要素の次（second）が先頭になること
				EXPECT_TRUE(list.begin() == next);
				ExpectData(kSecond, *list.begin());
			}

			//中央を削除するケース
			{
				SCOPED_TRACE("中央を削除するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				Iterator oldBegin = midList.begin();

				ASSERT_EQ(Result::Success, midList.erase(Next(midList.begin())));

				//先頭は変わらないこと
				EXPECT_TRUE(midList.begin() == oldBegin);
				ExpectData(kFirst, *midList.begin());
				ExpectLinksConsistent(midList);
			}

			//末尾を削除するケース
			{
				SCOPED_TRACE("末尾を削除するケース");
				ScoreList endList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(endList));
				Iterator oldBegin = endList.begin();

				ASSERT_EQ(Result::Success, endList.erase(Prev(endList.end())));

				//先頭は変わらないこと
				EXPECT_TRUE(endList.begin() == oldBegin);
				ExpectData(kFirst, *endList.begin());
				ExpectLinksConsistent(endList);
			}
		}

	}

	//===================先頭コンストイテレータの取得======================
	namespace ConstBeginTest {

		/**
		 * @brief リストが空である場合に、呼び出した際の挙動
		 * @details ID:T029
		 *          ダミーノードを指すイテレータが返る
		 * @return  ConstIterator
		 */
		TEST_F(EmptyListTest, CbeginEqualsCend) {
			ConstIterator it = clist.cbegin();
			EXPECT_TRUE(it == clist.cend());

			//const版のbegin()もcbegin()と一致すること
			EXPECT_TRUE(clist.begin() == clist.cbegin());
		}

		/**
		 * @brief リストに要素が一つある場合に、呼び出した際の挙動
		 * @details ID:T030
		 *          先頭要素を指すイテレータが返る
		 * @return  ConstIterator
		 */
		TEST_F(OneItemListTest, CbeginPointsToOnlyItem) {
			ConstIterator it = clist.cbegin();
			ExpectData(kFirst, *it);

			//次が末尾であること
			EXPECT_TRUE(Next(it) == clist.cend());
		}


		/**
		 * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
		 * @details ID:T031
		 *          先頭要素を指すイテレータが返る
		 * @return  ConstIterator
		 */
		TEST_F(TwoItemListTest, CbeginPointsToFirstItem) {
			ConstIterator it = clist.cbegin();
			ExpectData(kFirst, *it);

			//先頭から順にたどれること
			ExpectData(kSecond, *Next(it));
			EXPECT_TRUE(Next(it, 2) == clist.cend());
		}

		/**
		 * @brief データの挿入を行った後に、呼び出した際の挙動
		 * @details ID:T032
		 *          先頭要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
		 * @return  ConstIterator
		 */
		TEST_F(ThreeItemListTest, CbeginFollowsInsert) {
			//先頭に挿入するケース
			{
				SCOPED_TRACE("先頭に挿入するケース");
				Iterator inserted;
				ASSERT_EQ(Result::Success, list.insert(clist.cbegin(), kNew, &inserted));

				//挿入した要素が先頭になること
				EXPECT_TRUE(clist.cbegin() == inserted);
				ExpectData(kNew, *clist.cbegin());
			}

			//中央に挿入するケース
			{
				SCOPED_TRACE("中央に挿入するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				ConstIterator oldBegin = midList.cbegin();

				ASSERT_EQ(Result::Success, midList.insert(Next(midList.cbegin()), kNew));

				//先頭は変わらないこと
				EXPECT_TRUE(midList.cbegin() == oldBegin);
				ExpectData(kFirst, *midList.cbegin());
				ExpectLinksConsistent(midList);
			}

			//末尾に挿入するケース
			{
				SCOPED_TRACE("末尾に挿入するケース");
				ScoreList endList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(endList));
				ConstIterator oldBegin = endList.cbegin();

				ASSERT_EQ(Result::Success, endList.insert(endList.cend(), kNew));

				//先頭は変わらないこと
				EXPECT_TRUE(endList.cbegin() == oldBegin);
				ExpectData(kFirst, *endList.cbegin());
				ExpectLinksConsistent(endList);
			}
		}


		/**
		 * @brief データの削除を行った後に、呼び出した際の挙動
		 * @details ID:T033
		 *          先頭要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
		 * @return  ConstIterator
		 */
		TEST_F(ThreeItemListTest, CbeginFollowsErase) {
			//先頭の要素を削除するケース
			{
				SCOPED_TRACE("先頭の要素を削除するケース");
				Iterator next;
				ASSERT_EQ(Result::Success, list.erase(clist.cbegin(), &next));

				//削除した要素の次（second）が先頭になること
				EXPECT_TRUE(clist.cbegin() == next);
				ExpectData(kSecond, *clist.cbegin());
			}

			//中央の要素を削除するケース
			{
				SCOPED_TRACE("中央の要素を削除するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				ConstIterator oldBegin = midList.cbegin();

				ASSERT_EQ(Result::Success, midList.erase(Next(midList.cbegin())));

				//先頭は変わらないこと
				EXPECT_TRUE(midList.cbegin() == oldBegin);
				ExpectData(kFirst, *midList.cbegin());
				ExpectLinksConsistent(midList);
			}

			//末尾の要素を削除するケース
			{
				SCOPED_TRACE("末尾の要素を削除するケース");
				ScoreList endList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(endList));
				ConstIterator oldBegin = endList.cbegin();

				ASSERT_EQ(Result::Success, endList.erase(Prev(endList.cend())));

				//先頭は変わらないこと
				EXPECT_TRUE(endList.cbegin() == oldBegin);
				ExpectData(kFirst, *endList.cbegin());
				ExpectLinksConsistent(endList);
			}
		}

	}

	//===================末尾イテレータの取得======================
	namespace EndTest {

		/**
		 * @brief リストが空である場合に、呼び出した際の挙動
		 * @details ID:T035
		 *          ダミーノードを指すイテレータが返る
		 * @return  Iterator
		 */
		TEST_F(EmptyListTest, EndEqualsBegin) {
			Iterator it = list.end();
			EXPECT_TRUE(it == list.begin());
		}

		/**
		 * @brief リストに要素が一つある場合に、呼び出した際の挙動
		 * @details ID:T036
		 *          末尾要素を指すイテレータが返る
		 * @return  Iterator
		 */
		TEST_F(OneItemListTest, EndFollowsOnlyItem) {
			Iterator it = list.end();

			//1つ前が唯一の要素（first）であること
			ExpectData(kFirst, *Prev(it));
			EXPECT_TRUE(Prev(it) == list.begin());
		}

		/**
		 * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
		 * @details ID:T037
		 *          末尾要素を指すイテレータが返る
		 * @return  Iterator
		 */
		TEST_F(TwoItemListTest, EndFollowsLastItem) {
			Iterator it = list.end();

			//1つ前が最後の要素（second）であること
			ExpectData(kSecond, *Prev(it));

			//末尾から順にたどれること
			ExpectData(kFirst, *Prev(it, 2));
			EXPECT_TRUE(Prev(it, 2) == list.begin());
		}

		/**
		 * @brief データの挿入を行った後に、呼び出した際の挙動
		 * @details ID:T038
		 *          末尾要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
		 * @return  Iterator
		 */
		TEST_F(ThreeItemListTest, EndFollowsInsert) {
			//先頭に挿入するケース
			{
				SCOPED_TRACE("先頭に挿入するケース");
				Iterator oldEnd = list.end();
				ASSERT_EQ(Result::Success, list.insert(list.begin(), kNew));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(list.end() == oldEnd);
				ExpectData(kThird, *Prev(list.end()));
			}

			//中央に挿入するケース
			{
				SCOPED_TRACE("中央に挿入するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				Iterator oldEnd = midList.end();

				ASSERT_EQ(Result::Success, midList.insert(Next(midList.begin()), kNew));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(midList.end() == oldEnd);
				ExpectData(kThird, *Prev(midList.end()));
				ExpectLinksConsistent(midList);
			}

			//末尾に挿入するケース
			{
				SCOPED_TRACE("末尾に挿入するケース");
				ScoreList endList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(endList));
				Iterator oldEnd = endList.end();

				Iterator inserted;
				ASSERT_EQ(Result::Success, endList.insert(endList.end(), kNew, &inserted));

				//末尾は変わらず、1つ前が挿入した要素になること
				EXPECT_TRUE(endList.end() == oldEnd);
				EXPECT_TRUE(Prev(endList.end()) == inserted);
				ExpectData(kNew, *Prev(endList.end()));
				ExpectLinksConsistent(endList);
			}
		}

		/**
		 * @brief データの削除を行った後に、呼び出した際の挙動
		 * @details ID:T039
		 *          末尾要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
		 * @return  Iterator
		 */
		TEST_F(ThreeItemListTest, EndFollowsErase) {
			//末尾の要素を削除するケース
			{
				SCOPED_TRACE("末尾の要素を削除するケース");
				Iterator oldEnd = list.end();
				Iterator next;
				ASSERT_EQ(Result::Success, list.erase(Prev(list.end()), &next));

				//削除した要素の次が末尾であり、1つ前が second になること
				EXPECT_TRUE(next == list.end());
				EXPECT_TRUE(list.end() == oldEnd);
				ExpectData(kSecond, *Prev(list.end()));
			}

			//中央の要素を削除するケース
			{
				SCOPED_TRACE("中央の要素を削除するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				Iterator oldEnd = midList.end();

				ASSERT_EQ(Result::Success, midList.erase(Next(midList.begin())));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(midList.end() == oldEnd);
				ExpectData(kThird, *Prev(midList.end()));
				ExpectLinksConsistent(midList);
			}

			//先頭の要素を削除するケース
			{
				SCOPED_TRACE("先頭の要素を削除するケース");
				ScoreList beginList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(beginList));
				Iterator oldEnd = beginList.end();

				ASSERT_EQ(Result::Success, beginList.erase(beginList.begin()));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(beginList.end() == oldEnd);
				ExpectData(kThird, *Prev(beginList.end()));
				ExpectLinksConsistent(beginList);
			}
		}

	}

	//===================末尾コンストイテレータの取得======================
	namespace ConstEndTest {

		/**
		 * @brief リストが空である場合に、呼び出した際の挙動
		 * @details ID:T041
		 *          ダミーノードを指すイテレータが返る
		 * @return  ConstIterator
		 */
		TEST_F(EmptyListTest, CendEqualsCbegin) {
			ConstIterator it = clist.cend();

			//空のリストでは末尾と先頭が一致すること
			EXPECT_TRUE(it == clist.cbegin());

			//const版のend()もcend()と一致すること
			EXPECT_TRUE(clist.end() == clist.cend());
		}

		/**
		 * @brief リストに要素が一つある場合に、呼び出した際の挙動
		 * @details ID:T042
		 *          末尾要素を指すイテレータが返る
		 * @return  ConstIterator
		 */
		TEST_F(OneItemListTest, CendFollowsOnlyItem) {
			ConstIterator it = clist.cend();

			//1つ前が唯一の要素（first）であること
			ExpectData(kFirst, *Prev(it));
			EXPECT_TRUE(Prev(it) == clist.cbegin());
		}



		/**
		 * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
		 * @details ID:T043
		 *          末尾要素を指すイテレータが返る
		 * @return  ConstIterator
		 */
		TEST_F(TwoItemListTest, CendFollowsLastItem) {
			ConstIterator it = clist.cend();

			//1つ前が最後の要素（second）であること
			ExpectData(kSecond, *Prev(it));

			//末尾から順にたどれること
			ExpectData(kFirst, *Prev(it, 2));
			EXPECT_TRUE(Prev(it, 2) == clist.cbegin());
		}

		/**
		 * @brief データの挿入を行った後に、呼び出した際の挙動
		 * @details ID:T044
		 *          末尾要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
		 * @return  ConstIterator
		 */
		TEST_F(ThreeItemListTest, CendFollowsInsert) {
			//先頭に挿入するケース
			{
				SCOPED_TRACE("先頭に挿入するケース");
				ConstIterator oldEnd = clist.cend();
				ASSERT_EQ(Result::Success, list.insert(clist.cbegin(), kNew));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(clist.cend() == oldEnd);
				ExpectData(kThird, *Prev(clist.cend()));
			}

			//中央に挿入するケース
			{
				SCOPED_TRACE("中央に挿入するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				ConstIterator oldEnd = midList.cend();

				ASSERT_EQ(Result::Success, midList.insert(Next(midList.cbegin()), kNew));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(midList.cend() == oldEnd);
				ExpectData(kThird, *Prev(midList.cend()));
				ExpectLinksConsistent(midList);
			}

			//末尾に挿入するケース
			{
				SCOPED_TRACE("末尾に挿入するケース");
				ScoreList endList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(endList));
				ConstIterator oldEnd = endList.cend();

				Iterator inserted;
				ASSERT_EQ(Result::Success, endList.insert(endList.cend(), kNew, &inserted));

				//末尾は変わらず、1つ前が挿入した要素になること
				EXPECT_TRUE(endList.cend() == oldEnd);
				EXPECT_TRUE(Prev(endList.cend()) == inserted);
				ExpectData(kNew, *Prev(endList.cend()));
				ExpectLinksConsistent(endList);
			}
		}

		/**
		 * @brief データの削除を行った後に、呼び出した際の挙動
		 * @details ID:T045
		 *          末尾要素を指すイテレータが返る
		 * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
		 * @return  ConstIterator
		 */
		TEST_F(ThreeItemListTest, CendFollowsErase) {
			//末尾の要素を削除するケース
			{
				SCOPED_TRACE("末尾の要素を削除するケース");
				ConstIterator oldEnd = clist.cend();
				Iterator next;
				ASSERT_EQ(Result::Success, list.erase(Prev(clist.cend()), &next));

				//削除した要素の次が末尾であり、1つ前が second になること
				EXPECT_TRUE(next == clist.cend());
				EXPECT_TRUE(clist.cend() == oldEnd);
				ExpectData(kSecond, *Prev(clist.cend()));
			}

			//中央の要素を削除するケース
			{
				SCOPED_TRACE("中央の要素を削除するケース");
				ScoreList midList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(midList));
				ConstIterator oldEnd = midList.cend();

				ASSERT_EQ(Result::Success, midList.erase(Next(midList.cbegin())));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(midList.cend() == oldEnd);
				ExpectData(kThird, *Prev(midList.cend()));
				ExpectLinksConsistent(midList);
			}

			//先頭の要素を削除するケース
			{
				SCOPED_TRACE("先頭の要素を削除するケース");
				ScoreList beginList;
				ASSERT_NO_FATAL_FAILURE(PushBackThreeItems(beginList));
				ConstIterator oldEnd = beginList.cend();

				ASSERT_EQ(Result::Success, beginList.erase(beginList.cbegin()));

				//末尾は変わらず、1つ前は third のままであること
				EXPECT_TRUE(beginList.cend() == oldEnd);
				ExpectData(kThird, *Prev(beginList.cend()));
				ExpectLinksConsistent(beginList);
			}
		}

	}

}

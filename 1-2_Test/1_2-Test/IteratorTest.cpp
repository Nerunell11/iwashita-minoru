/********************************************************************************
 * @file test.cpp
 * @brief 自動テストコード
 * @date 2026-10-01
 *********************************************************************************/
 #include "pch.h"
 #include "ScoreList.h"
 
 
 //===============================================================================
 //テストの番号を振っています
 //1桁目はテスト項目を表しており、0ならリスト、1ならイテレータです。
 //2,3桁目はテストのIDを表しています
 //===============================================================================

 namespace IteratorTest{
    //===================イテレータの指す要素を取得する======================
    namespace DereferenceTest{
      
      /**
       * @brief リストの参照がない状態で呼び出した際の挙動をテスト
       * @details ID:T100
       *      Assert発生
       */
      TEST(DereferenceTest,T100){
        Iterator it;
        EXPECT_DEATH((void)*it, "hasOwner");
      }
  
      /**
       * @brief Iteratorから取得した要素に対して、値の代入が行えるかをチェック
       * @details ID:T101
       * @note    代入後に再度呼び出し、値が変更されていることを確認
       */
      TEST(DereferenceTest,T101){
        ScoreList list;
        list.pushBack(1, "first");
        ASSERT_EQ(1,list.size());

        Iterator it = list.begin();
        (*it).score = 2;
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ("first", (*it).userName);
      }
  
      /**
       * @brief ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
       * @details ID:T102
       * @note    コンパイルエラーになることをチェック。自動テスト化しなくてよい。
       */
      TEST(DereferenceTest,T102){
        SUCCEED()<<"手動テスト項目のためスキップします";
      }
  
      /**
       * @brief リストが空の際の、先頭イテレータに対して呼び出した際の挙動
       * @details ID:T103
       *             Assert発生
       */
      TEST(DereferenceTest,T103){
        ScoreList list;
        ASSERT_EQ(0,list.size());

        Iterator it = list.begin();
        EXPECT_DEATH((void)*it, "isEnd");
      }
  
      /**
       * @brief 末尾イテレータに対して呼び出した際の挙動
       * @details ID:T104
       *             Assert発生
       */
      TEST(DereferenceTest,T104){
        ScoreList list;
        list.pushBack(1, "first");
        ASSERT_EQ(1,list.size());

        Iterator it = list.end();
        EXPECT_DEATH((void)*it, "isEnd");
      }
  
    }
  
    //===================イテレータをリストの末尾に向かって一つ進める=========
    namespace IncrementTest{
  
      /**
       * @brief リストの参照がない状態で呼び出した際の挙動
       * @details ID:T105
       *             Assert発生
       */
      TEST(IncrementTest,T105){
        Iterator it;
        EXPECT_DEATH(++it,"hasOwner");
      }
  
      /**
       * @brief リストが空の際の、先頭イテレータに対して呼び出した際の挙動
       * @details ID:T106
       *             Assert発生
       */
      TEST(IncrementTest,T106){
        ScoreList list;
        ASSERT_EQ(0,list.size());

        Iterator it = list.begin();
        EXPECT_DEATH(++it, "isEnd");
      }
  
  
      /**
       * @brief 末尾イテレータに対して呼び出した際の挙動
       * @details ID:T107
       *             Assert発生
       */
      TEST(IncrementTest,T107){
        ScoreList list;
        list.pushBack(1, "first");
        ASSERT_EQ(1,list.size());

        Iterator it = list.end();
        EXPECT_DEATH(++it, "isEnd");
      }
  
      /**
       * @brief リストに二つ以上の要素がある場合に呼び出した際の挙動
       * @details ID:T108
       *             次の要素を指す  
       * @note    リストの先頭から末尾まで呼び出しを行い、期待されている要素が格納されているかを確認
       */
       TEST(IncrementTest, T108) {
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());

        Iterator it = list.begin();
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
        
        ++it;
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ("second", (*it).userName);
        
        ++it;
        EXPECT_TRUE(it == list.end());
      }
  
      /**
       * @brief 前置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
       * @details ID:T109
       *             次の要素を指す
       * @note    インクリメント呼び出し時の値と、インクリメント実行後の値の両方を確認
       */
       TEST(IncrementTest, T109) {
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());

        Iterator it = list.begin();
        ASSERT_TRUE(it != list.end());
        
        ConstIterator& result = ++it;
        EXPECT_EQ(&it, &result);
        
        ASSERT_TRUE(result != list.end());
        EXPECT_EQ(2, (*result).score);
        EXPECT_EQ("second", (*result).userName);
        
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ("second", (*it).userName);
      }
  
      /**
       * @brief 後置インクリメントを行った際の挙動( ++演算子オーバーロードで実装した場合 )
       * @details ID:T110
       *             次の要素を指す
       * @note    インクリメント呼び出し時の値と、インクリメント実行後の値の両方を確認
       */
       TEST(IncrementTest, T110) {
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());
        
        Iterator it = list.begin();
        ASSERT_TRUE(it != list.end());
        
        ConstIterator old = it++;
        
        ASSERT_TRUE(old != list.end());
        EXPECT_EQ(1, (*old).score);
        EXPECT_EQ("first", (*old).userName);
        
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ("second", (*it).userName);
      }
    }
  
    //===================イテレータをリストの先頭に向かって一つ進める=========
    namespace DecrementTest{
    
  
      /**
       * @brief リストの参照がない状態で呼び出した際の挙動
       * @details ID:T111
       *             Assert発生
       */
      TEST(DecrementTest,T111){
        Iterator it;
        EXPECT_DEATH(--it, "hasOwner");
      }
  
      /**
       * @brief リストが空の際の、末尾イテレータに対して呼び出した際の挙動
       * @details ID:T112
       *             Assert発生
       */
      TEST(DecrementTest,T112){
        ScoreList list;
        ASSERT_EQ(0,list.size());

        Iterator it = list.end();
        EXPECT_DEATH(--it, "isBegin");
      }
      
      /**
       * @brief 先頭イテレータに対して呼び出した際の挙動
       * @details ID:T113
       *             Assert発生 
       */
      TEST(DecrementTest,T113){
        ScoreList list;
        list.pushBack(1, "first");
        ASSERT_EQ(1,list.size());

        Iterator it = list.begin();
        EXPECT_DEATH(--it, "isBegin");
      }
  
      /**
       * @brief リストに二つ以上の要素がある場合に呼び出した際の挙動
       * @details ID:T114
       *             前の要素を指す
       * @note    リストの末尾から先頭まで呼び出しを行い、期待されている要素が格納されているかを確認
       */
      TEST(DecrementTest,T114){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2,list.size());

        Iterator it = list.end();

        --it;
        ASSERT_TRUE(it != list.begin());
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ("second", (*it).userName);

        --it;
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
        EXPECT_TRUE(it == list.begin());

      }
  
      /**
       * @brief 前置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
       * @details ID:T115
       *             前の要素を指す
       * @note    デクリメント呼び出し時の値と、デクリメント実行後の値の両方を確認
       */
      TEST(DecrementTest,T115){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2,list.size());

        Iterator it = list.end();
        --it;
        ASSERT_TRUE(it != list.end());

        ConstIterator& result = --it;
        EXPECT_EQ(&it, &result);

        ASSERT_TRUE(result != list.end());
        EXPECT_EQ(1, (*result).score);
        EXPECT_EQ("first", (*result).userName);

        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
      }
  
      /**
       * @brief 後置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
       * @details ID:T116
       *             前の要素を指す
       * @note    デクリメント呼び出し時の値と、デクリメント実行後の値の両方を確認
       */
      TEST(DecrementTest,T116){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());

        Iterator it = list.end();
        --it;
        ASSERT_TRUE(it != list.end());

        ConstIterator old = it--;

        ASSERT_TRUE(old != list.end());
        EXPECT_EQ(2,(*old).score);
        EXPECT_EQ("second", (*old).userName);

        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
      }
  
    }
  
    //===================イテレータのコピーを行う======================
    namespace CopyTest{ 
    
      /**
       * @brief ConstIteratorから、Iteratorのコピーが作成されないかをチェック
       * @details ID:T117
       * @note    コンパイルエラーになることをチェック。自動テスト化しなくてよい。
       */
      TEST(CopyTest,T117){
        SUCCEED()<<"手動テスト項目のためスキップします";
      }
  
      /**
       * @brief コピーコンストラクト後の値がコピー元と等しいことをチェック
       * @details ID:T118
       */
      TEST(CopyTest,T118){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2,list.size());

        Iterator it = list.begin();
        Iterator copy = it;

        EXPECT_TRUE(copy == it);
        ASSERT_TRUE(copy != list.end());
        EXPECT_EQ(1, (*copy).score);
        EXPECT_EQ("first", (*copy).userName);

        ++copy;
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(1,(*it).score);
        EXPECT_EQ("first", (*it).userName);

      }
  
    }
    
  
    //===================イテレータの代入を行う======================
    namespace AssignTest{
  
      /**
       * @brief IteratorにConstIteratorを代入できない事をチェック
       * @details ID:T119
       * @note    コンパイルエラーになることをチェック。自動テスト化しなくてよい。
       */
      TEST(AssignTest,T119){
        SUCCEED()<<"手動テスト項目のためスキップします";
      }
    
      /**
       * @brief 代入後の値がコピー元と等しいことをチェック
       * @details ID:T120
       */
      TEST(AssignTest,T120){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());

        Iterator it = list.begin();
        Iterator copy = list.begin();
        ++copy;
        ASSERT_TRUE(copy != it);

        copy = it;

        EXPECT_TRUE(copy == it);
        ASSERT_TRUE(copy != list.end());
        EXPECT_EQ(1, (*copy).score);
        EXPECT_EQ("first",(*copy).userName);

        ++copy;
        ASSERT_TRUE(it != list.end());
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
      }
  
    }
    
  
    //===================2つのイテレータが同一であるか比較を行う======================
    namespace EqualTest{
  
      /**
       * @brief リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
       * @details ID:T121
       *           True:成功, False:失敗
       */
      TEST(EqualTest,T121){
        ScoreList list;
        ASSERT_EQ(0,list.size());

        Iterator it = list.begin();
        EXPECT_TRUE(it == list.end());
      }
  
      /**
       * @brief 同一のイテレータを比較した際の挙動をチェック
       * @details ID:T122
       *           True:成功, False:失敗
       */
      TEST(EqualTest,T122){
        ScoreList list;
        list.pushBack(1, "first");
        ASSERT_EQ(1,list.size());

        Iterator a = list.begin();
        Iterator b = list.begin();
        EXPECT_TRUE(a == b);

      }
  
      /**
       * @brief 異なるイテレータを比較した際の挙動をチェック
       * @details ID:T123
       *           True:失敗, False:成功
       */
      TEST(EqualTest,T123){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());

        Iterator a = list.begin();
        Iterator b = list.begin();
        b++;
        ASSERT_TRUE(b != list.end());

        EXPECT_FALSE(a == b);
      }
  
    }
  
    //===================2つのイテレータが異なるか比較を行う======================
    namespace NotEqualTest{
  
      /**
       * @brief リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
       * @details ID:T124
       *           True:失敗, False:成功
       */
      TEST(NotEqualTest,T124){
        ScoreList list;
        ASSERT_EQ(0, list.size());

        Iterator it = list.begin();
        EXPECT_FALSE(it != list.end());
      }
  
      /**
       * @brief 同一のイテレータを比較した際の挙動をチェック
       * @details ID:T125
       *           True:失敗, False:成功
       */
      TEST(NotEqualTest,T125){
        ScoreList list;
        list.pushBack(1, "first");
        ASSERT_EQ(1, list.size());

        Iterator a = list.begin();
        Iterator b = list.begin();
        EXPECT_FALSE(a != b);
      }
  
      /**
       * @brief 異なるイテレータを比較した際の挙動をチェック
       * @details ID:T126
       *           True:成功, False:失敗
       */
      TEST(NotEqualTest,T126){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        ASSERT_EQ(2, list.size());

        Iterator a = list.begin();
        Iterator b = list.begin();
        ++b;
        ASSERT_FALSE(b == list.end());

        EXPECT_TRUE(a != b);
      }
    }
}
  
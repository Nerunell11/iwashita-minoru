/********************************************************************************
 * @file ListTest.cpp
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

namespace Test_List
{
  //===================データ数の取得==================
  namespace GetDataCountTest{

    /**
     * @brief　リストが空である場合のデータ数の取得テスト
     * @details ID:T000
     * 　　　　　データ数が0であれば成功
     */
    TEST(GetDataCount,T000) {
      ScoreList list;
      EXPECT_EQ(0, list.size());
    }
    
    /**
     * @brief  リスト末尾への挿入を行った際のデータ数の取得テスト
     * @details ID:T001
     *          データ数が1であれば成功
     */
     TEST(GetDataCount,T001) {
      ScoreList list;
      list.pushBack(1, "test");
      EXPECT_EQ(1, list.size());
    }
    
    /**
     * @brief リスト末尾への挿入が失敗した際のデータ数の取得テスト
     * @details ID:T002
     *          データ数が0であれば成功
     */
    TEST(GetDataCount,T002) {
      SUCCEED()<<"末尾への挿入失敗はメモリ確保失敗時の為、スキップ";
    }
    
    /**
     * @brief データの挿入を行った際のデータ数の取得テスト
     * @details ID:T003
     *          データ数が1であれば成功
     */
    TEST(GetDataCount,T003) {
      ScoreList list;
      Iterator it = list.begin();
      list.insert(it,ScoreData{1,"test"});
      EXPECT_EQ(1, list.size());
    }
    
    /**
     * @brief データの挿入に失敗した際のデータ数の取得テスト
     * @details ID:T004
     *          データ数が0であれば成功
     */
    TEST(GetDataCount,T004) {
      ScoreList list;
      Iterator invaild;
      list.insert(invaild, ScoreData{1, "test"});
      EXPECT_EQ(0, list.size());
    }
    
    /**
     * @brief データの削除を行った際のデータ数の取得テスト
     * @details ID:T005
     *          データ数が0であれば成功
     */
    TEST(GetDataCount,T005) {
      ScoreList list;
      list.pushBack(1, "test");
      list.erase(list.begin());
      EXPECT_EQ(0, list.size());
    }
    
    /**
     * @brief データの削除が失敗した際のデータ数の取得テスト
     * @details ID:T006
     *          データ数が1であれば成功
     *@note データを挿入した後、削除した場合
     */
    TEST(GetDataCount,T006) {
      ScoreList list;
      list.pushBack(1, "test");
      Iterator invaild;
      list.erase(invaild);
      EXPECT_EQ(1, list.size());
    }
    
    /**
     * @brief リストが空である場合に、データの取得を行った際のデータ数の取得テスト
     * @details ID:T007
     *          データ数が0であれば成功
     * @note マイナスにならないかどうか
     */
    TEST(GetDataCount,T007) {
      ScoreList list;

      //マイナスにならないこと
      list.erase(list.begin());
      EXPECT_EQ(0, list.size());
    }
    
    /**
     * @brief constのメソッドであるかをテスト
     * @details ID:T008
     * @note constのリストから呼び出して、コンパイルエラーとならないかをチェック
     */
    TEST(GetDataCount,T008) {
      SUCCEED()<<"手動テスト項目のためスキップします";
    }

  }

  //===================データの挿入===================
  namespace PushBackTest{

    /**
     * @brief リストが空である場合に、挿入した際の挙動をテスト
     * @details ID:T009
     *          イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
     * @note    先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックすること
     * @return  True:成功, False:失敗
     */
     TEST(PushBack, T009) {
      ScoreList list;
    
      //先頭イテレータに挿入
      list.insert(list.begin(), ScoreData{1, "test"});
      EXPECT_EQ(1, list.size());
    
      //末尾イテレータに挿入
      list.insert(list.end(), ScoreData{2, "test2"});
      EXPECT_EQ(2, list.size());
    }
    
    /**
     * @brief リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動をテスト
     * @details ID:T010
     *          先頭に要素が挿入され、元々先頭だった要素が２番目になる。
     * @return  True:成功, False:失敗
     */
    TEST(PushBack,T010) {
      ScoreList list;

      //事前準備
      list.pushBack(1, "first");
      list.pushBack(2, "second");
      
      //挿入
      Iterator ret = list.insert(list.begin(), ScoreData{0, "new"});
      ASSERT_EQ(3, list.size());
      Iterator it = list.begin();
      
      EXPECT_TRUE(it == ret);              //挿入した要素が先頭
      EXPECT_EQ(0, (*it).score);
      ++it;
      
      EXPECT_EQ(1, (*it).score);           //元の先頭が2番目にずれている
      EXPECT_EQ("first", (*it).userName);
      ++it;
      
      EXPECT_EQ(2, (*it).score);           //元の2番目も1つ後ろにずれている
      ++it;
      EXPECT_TRUE(it == list.end());
    }
    
    /**
     * @brief リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動をテスト
     * @details ID:T011
     *          イテレータの指す位置に要素が挿入される
     * @return  True:成功, False:失敗
     */
    TEST(PushBack,T011) {
      ScoreList list;

      //事前準備
      list.pushBack(1, "first");
      list.pushBack(2, "second");
      
      //挿入
      list.insert(list.end(), ScoreData{3, "third"});
      ASSERT_EQ(3, list.size());
      
      //末尾に挿入されている
      Iterator it = list.end();
      --it;
      EXPECT_EQ(3, (*it).score);
      EXPECT_EQ("third", (*it).userName);
    }
    
    /**
     * @brief リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動をテスト
     * @details ID:T012
     *          イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
     * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか。要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
     * @return  True:成功, False:失敗
     */
     TEST(Insert, T012) {
        ScoreList list;
      
        //事前準備
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        list.pushBack(3, "third");
      
        //挿入（2番目の位置）
        Iterator it = list.begin();
        ++it;
        Iterator inserted = list.insert(it, ScoreData{ 0, "new" });
        ASSERT_EQ(4, list.size());
      
        Iterator cur = list.begin();
      
        //元の先頭は変わらないこと
        EXPECT_EQ(1, (*cur).score);
        EXPECT_EQ("first", (*cur).userName);
        ++cur;
      
        //挿入した要素が2番目にあること
        EXPECT_EQ(0, (*cur).score);
        EXPECT_EQ("new", (*cur).userName);
        EXPECT_TRUE(cur == inserted);
        ++cur;
      
        //元の2番目が3番目にズレていること
        EXPECT_EQ(2, (*cur).score);
        EXPECT_EQ("second", (*cur).userName);
        ++cur;
      
        //元の3番目が4番目にズレていること
        EXPECT_EQ(3, (*cur).score);
        EXPECT_EQ("third", (*cur).userName);
        ++cur;
      
        //余分な要素がないこと
        EXPECT_TRUE(cur == list.end());
      }
    
    /**
     * @brief ConstIteratorを指定して挿入を行った際の挙動をテスト
     * @details ID:T013
     *          イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
     * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか。要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
     * @return  True:成功, False:失敗
     */
     TEST(Insert, T013) {
      ScoreList list;
    
      //事前準備
      list.pushBack(1, "first");
      list.pushBack(2, "second");
      list.pushBack(3, "third");
    
      //挿入
      const ScoreList& clist = list;
      ConstIterator pos = clist.begin();
      ++pos;
    
      ConstIterator inserted = list.insert(pos, ScoreData{0, "new"});
      ASSERT_EQ(4, list.size());
    
      //元の先頭は変わらないこと
      ConstIterator cur = clist.begin();
      EXPECT_EQ(1, (*cur).score);
      ++cur;

      //挿入した要素が2番目にあること
      EXPECT_EQ(0, (*cur).score);
      EXPECT_EQ("new", (*cur).userName);
      EXPECT_TRUE(cur == inserted);
      ++cur;

      //挿入した要素が2番目にあること
      EXPECT_EQ(2, (*cur).score);
      ++cur;
      
      //元の2番目が3番目にズレていること
      EXPECT_EQ(3, (*cur).score);
      ++cur;
      
      EXPECT_TRUE(cur == clist.end());
    }

    /**
     * @brief 不正なイテレータを渡して挿入を行った際の挙動をテスト
     * @details ID:T014
     *          何も起こらない
     * @note    リストの参照がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動など
     * @return  True:失敗, False:成功
     */
     TEST(Insert, T014) {
      ScoreList list;
      list.pushBack(1, "first");
      list.pushBack(2, "second");
  
      //リストの参照がないイテレータ
      Iterator invalid;
      list.insert(invalid, ScoreData{ 9, "bad" });
      EXPECT_EQ(2, list.size());
  
      //別リストの要素を指すイテレータ
      ScoreList other;
      other.pushBack(100, "other");
      list.insert(other.begin(), ScoreData{ 9, "bad" });
      ASSERT_EQ(2, list.size());
      
      //別リスト側にも挿入されていないこと
      EXPECT_EQ(1, other.size());   
  
      //既存要素が変わっていないこと
      Iterator it = list.begin();
      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      ++it;
      EXPECT_EQ(2, (*it).score);
      EXPECT_EQ("second", (*it).userName);
      ++it;
      EXPECT_TRUE(it == list.end());
      
    }

     /**
      * @brief 非constのメソッドであるか
      * @details ID:T015
      * @note   constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
      */
      TEST(Insert,T015){
        SUCCEED()<<"手動テスト項目のためスキップします";
      }
  }


  //===================データの削除===================
  namespace EraseTest{
  
    /**
     * @brief リストが空である場合に、削除を行った際の挙動をテスト
     * @details ID:T016
     *          何も起こらない
     * @note    先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックすること
     * @return  True:失敗, False:成功
     */
    TEST(Erase,T016){
      ScoreList list;
      list.erase(list.begin());
      EXPECT_EQ(0, list.size());

      list.erase(list.end());
      EXPECT_EQ(0, list.size());
    }

    /**
     * @brief 先頭要素の削除を行った際の挙動をテスト
     * @details ID:T017
     *          先頭要素が削除され、次の要素が先頭になる
     * @return  True:成功, False:失敗
     */
    TEST(Erase,T017){
      ScoreList list;
      list.pushBack(1, "first");
      list.pushBack(2, "second");
      
      //先頭要素の削除
      Iterator next = list.erase(list.begin());

      //要素が減っていることを確認
      ASSERT_EQ(1, list.size());

      //次の要素が先頭になっていることを確認
      EXPECT_TRUE(next == list.begin());
      EXPECT_EQ(2, (*next).score);
      EXPECT_EQ("second", (*next).userName);

    }

    /**
     * @brief リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
     * @details ID:T018
     *          何も起こらない
     * @return  True:失敗, False:成功
     */
     TEST(Erase,T018){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");

        //末尾イテレータを渡して削除
        Iterator next = list.erase(list.end());
        
        //戻り値が末尾イテレータであること
        EXPECT_TRUE(next == list.end());
        
        //要素が減っていないことを確認
        ASSERT_EQ(2, list.size());
        
        //中身と順番が変わっていないこと
        Iterator it = list.begin();
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
        ++it;
        EXPECT_EQ(2, (*it).score);
        EXPECT_EQ("second", (*it).userName);
        ++it;
        EXPECT_TRUE(it == list.end());
      }


    /**
     * @brief リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
     * @details ID:T019
     *          指定要素の削除
     * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか
     * @return  True:成功, False:失敗
     */
     TEST(Erase,T019){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        list.pushBack(3, "third");

        //先頭でも末尾でもないイテレータ
        Iterator pos = list.begin();
        ++pos;
        Iterator next = list.erase(pos);
        
        //戻り値が削除した要素の次（third）を指していること
        EXPECT_EQ(3, (*next).score);
        EXPECT_EQ("third", (*next).userName);
        
        //要素が減っていることを確認
        ASSERT_EQ(2, list.size());
        
        //正しい位置に要素が格納されているか
        Iterator it = list.begin();
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
        ++it;
        
        EXPECT_TRUE(it == next);   //戻り値の位置がリスト上でも正しいこと
        EXPECT_EQ(3, (*it).score);
        EXPECT_EQ("third", (*it).userName);
        ++it;
        EXPECT_TRUE(it == list.end());
      }

    /**
     * @brief ConstIteratorを指定して削除を行った際の挙動をテスト
     * @details ID:T020
     *          指定要素の削除
     * @note    格納済みの要素に影響がないか、期待される位置に要素が格納されているか
     * @return  True:成功, False:失敗
     */
     TEST(Erase,T020){
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        list.pushBack(3, "third");
      
        //ConstIteratorを指定して真ん中を削除
        const ScoreList& clist = list;
        ConstIterator pos = clist.begin();
        ++pos;
        Iterator next = list.erase(pos);
      
        ASSERT_EQ(2, list.size());
      
        //格納済みの要素に影響がないか
        ConstIterator it = clist.begin();
        EXPECT_EQ(1, (*it).score);
        EXPECT_EQ("first", (*it).userName);
        ++it;
        EXPECT_EQ(3, (*it).score);
        EXPECT_EQ("third", (*it).userName);
        ++it;
        EXPECT_TRUE(it == clist.end());
      
        //戻り値が削除した要素の次を指しているか
        EXPECT_EQ(3, (*next).score);
        EXPECT_EQ("third", (*next).userName);
        ++next;
        EXPECT_TRUE(next == clist.end());
      }

    /**
     * @brief 不正なイテレータを渡して、削除した場合の挙動
     * @details ID:T021
     *          何も起こらない
     * @note    リストの参照がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動など
     * @return  True:失敗, False:成功
     */
     TEST(Erase, T021) {
      ScoreList list;
      list.pushBack(1, "first");
      list.pushBack(2, "second");
  
      //リストの参照がないイテレータ
      Iterator invalid;
      Iterator ret = list.erase(invalid);
      EXPECT_TRUE(ret == list.end());
      ASSERT_EQ(2, list.size());
  
      //別リストの要素を指すイテレータ
      ScoreList other;
      other.pushBack(100, "other");
      ret = list.erase(other.begin());
      EXPECT_TRUE(ret == list.end());
      ASSERT_EQ(2, list.size());
  
      //別リスト側の要素も削除されていないこと
      ASSERT_EQ(1, other.size());
      EXPECT_EQ(100, (*other.begin()).score);
      EXPECT_EQ("other", (*other.begin()).userName);
  
      //元のリストの要素が変わっていないこと
      Iterator it = list.begin();
      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      ++it;
      EXPECT_EQ(2, (*it).score);
      EXPECT_EQ("second", (*it).userName);
      ++it;
      EXPECT_TRUE(it == list.end());
    }

    /**
     * @brief 非constのメソッドであるか
     * @details ID:T022
     * @note   constのリストから呼び出して、コンパイルエラーとなるかをチェック。自動テスト化しなくてよい。
     */
     TEST(Erase,T022){
        SUCCEED()<<"手動テスト項目のためスキップします";
      }

  }

  //===================先頭イテレータの取得======================
  namespace BeginTest{

    /**
     * @brief リストが空である場合に、呼び出した際の挙動
     * @details ID:T023
     *          ダミーノードを指すイテレータが返る
     * @return  Iterator
     */
    TEST(BeginTest,T023){
      ScoreList list;
      Iterator it = list.begin();
      EXPECT_TRUE(it == list.end());
      
    }

    /**
     * @brief リストに要素が一つある場合に、呼び出した際の挙動
     * @details ID:T024
     *          先頭要素を指すイテレータが返る
     * @return  Iterator
     */
    TEST(BeginTest,T024){
      ScoreList list;
      list.pushBack(1, "first");
      ASSERT_EQ(1,list.size());

      Iterator it = list.begin();
      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      ++it;
      EXPECT_TRUE(it == list.end());
    }

    /**
     * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
     * @details ID:T025
     *          先頭要素を指すイテレータが返る
     * @return  Iterator
     */
    TEST(BeginTest,T025){
      ScoreList list;
      list.pushBack(1, "first");
      list.pushBack(2, "second");

      Iterator it = list.begin();
      ASSERT_EQ(2,list.size());

      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      ++it;
      EXPECT_EQ(2, (*it).score);
      EXPECT_EQ("second", (*it).userName);
      ++it;
      EXPECT_TRUE(it == list.end());
    }

    /**
     * @brief データの挿入を行った後に、呼び出した際の挙動
     * @details ID:T026
     *          先頭要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
     * @return  Iterator
     */
     TEST(BeginTest, T026) {
        // 先頭に挿入するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.insert(list.begin(), ScoreData{ 0, "zero" });
          ASSERT_EQ(4, list.size());
      
          Iterator it = list.begin();
          EXPECT_EQ(0, (*it).score);
          EXPECT_EQ("zero", (*it).userName);
        }
      
        // 中央に挿入するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          Iterator mid = list.begin();
          ++mid;
          list.insert(mid, ScoreData{ 9, "middle" });
          ASSERT_EQ(4, list.size());
      
          Iterator it = list.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      
        // 末尾に挿入するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.insert(list.end(), ScoreData{ 4, "fourth" });
          ASSERT_EQ(4, list.size());
      
          Iterator it = list.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      }

    /**
     * @brief データの削除を行った後に、呼び出した際の挙動
     * @details ID:T027
     *          先頭要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
     * @return  Iterator
     */
     TEST(BeginTest, T027) {
        // 先頭を削除するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");

          list.erase(list.begin());
          ASSERT_EQ(2, list.size());
      
          Iterator it = list.begin();
          EXPECT_EQ(2, (*it).score);
          EXPECT_EQ("second", (*it).userName);
        }

        // 中央を削除するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");

          Iterator mid = list.begin();
          ++mid;
          list.erase(mid);
          ASSERT_EQ(2, list.size());
      
          Iterator it = list.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }

        // 末尾を削除するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");

          Iterator last = list.begin();
          ++last;
          ++last;
          list.erase(last);
          ASSERT_EQ(2, list.size());
      
          Iterator it = list.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      }

    /**
     * @brief 非constのメソッドであるか
     * @details ID:T028
     * @note   コンパイルエラーになることを確認する。自動テスト化しなくてよい。
     */
    TEST(BeginTest,T028){
      SUCCEED()<<"手動テスト項目のためスキップします";
    }

    

  }

  //===================先頭コンストイテレータの取得======================
  namespace ConstBeginTest{

    /**
     * @brief リストが空である場合に、呼び出した際の挙動
     * @details ID:T029
     *          ダミーノードを指すイテレータが返る
     * @return  ConstIterator
     */
    TEST(ConstBeginTest,T029){
      ScoreList list;
      const ScoreList& clist = list;
      ConstIterator it = clist.begin();
      EXPECT_TRUE(it == clist.end());
    }

    /**
     * @brief リストに要素が一つある場合に、呼び出した際の挙動
     * @details ID:T030
     *          先頭要素を指すイテレータが返る
     * @return  ConstIterator
     */
    TEST(ConstBeginTest,T030){
      ScoreList list;
      const ScoreList& clist = list;

      list.pushBack(1, "first");
      ASSERT_EQ(1,clist.size());

      ConstIterator it = clist.begin();
      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      ++it;
      EXPECT_TRUE(it == clist.end());
    }

    /**
     * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
     * @details ID:T031
     *          先頭要素を指すイテレータが返る
     * @return  ConstIterator
     */
    TEST(ConstBeginTest,T031){
      ScoreList list;
      const ScoreList& clist = list;

      list.pushBack(1, "first");
      list.pushBack(2, "second");
      ASSERT_EQ(2,clist.size());

      ConstIterator it = clist.begin();
      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      
      ++it;
      EXPECT_EQ(2, (*it).score);
      EXPECT_EQ("second", (*it).userName);

    }

    /**
     * @brief データの挿入を行った後に、呼び出した際の挙動
     * @details ID:T032
     *          先頭要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
     * @return  ConstIterator
     */
     TEST(ConstBeginTest, T032) {
        // 先頭に挿入するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.insert(clist.begin(), ScoreData{ 0, "zero" });
          ASSERT_EQ(4,clist.size());
      
          ConstIterator it = clist.begin();
          EXPECT_EQ(0, (*it).score);
          EXPECT_EQ("zero", (*it).userName);
        }
      
        // 中央に挿入するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          ConstIterator mid = clist.begin();
          ++mid;
          list.insert(mid, ScoreData{ 9, "middle" });
          ASSERT_EQ(4, clist.size());
      
          ConstIterator it = clist.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      
        // 末尾に挿入するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.insert(clist.end(), ScoreData{ 4, "fourth" });
          ASSERT_EQ(4, clist.size());
      
          ConstIterator it = clist.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      }

    /**
     * @brief データの削除を行った後に、呼び出した際の挙動
     * @details ID:T033
     *          先頭要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
     * @return  ConstIterator
     */
     TEST(ConstBeginTest, T033) {
        // 先頭の要素を削除するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.erase(clist.begin());
          ASSERT_EQ(2,clist.size());
      
          ConstIterator it = clist.begin();
          EXPECT_EQ(2, (*it).score);
          EXPECT_EQ("second", (*it).userName);
        }
      
        // 中央の要素を削除するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          ConstIterator mid = clist.begin();
          ++mid;
          list.erase(mid);
          ASSERT_EQ(2,clist.size());
      
          ConstIterator it = clist.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      
        // 末尾の要素を削除するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          ConstIterator last = clist.end();
          --last;
          list.erase(last);
          ASSERT_EQ(2,clist.size());
      
          ConstIterator it = clist.begin();
          EXPECT_EQ(1, (*it).score);
          EXPECT_EQ("first", (*it).userName);
        }
      }

    /**
     * @brief constのメソッドであるか
     * @details ID:T034
     * @note   constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
     */
    TEST(ConstBeginTest,T034){
      SUCCEED()<<"手動テスト項目のためスキップします";
    }

  }

  //===================末尾イテレータの取得======================
  namespace EndTest{

    /**
     * @brief リストが空である場合に、呼び出した際の挙動
     * @details ID:T035
     *          ダミーノードを指すイテレータが返る
     * @return  Iterator
     */
    TEST(EndTest,T035){
      ScoreList list;
      Iterator it = list.end();
      EXPECT_TRUE(it == list.end());
    }

    /**
     * @brief リストに要素が一つある場合に、呼び出した際の挙動
     * @details ID:T036
     *          末尾要素を指すイテレータが返る
     * @return  Iterator
     */
    TEST(EndTest,T036){
      ScoreList list;
      list.pushBack(1, "first");
      ASSERT_EQ(1,list.size());

      Iterator it = list.end();
      --it; 
      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);

      ++it;
      EXPECT_TRUE(it == list.end());
    }

    /**
     * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
     * @details ID:T037
     *          末尾要素を指すイテレータが返る
     * @return  Iterator
     */
    TEST(EndTest,T037){
      ScoreList list;
      list.pushBack(1, "first");
      list.pushBack(2, "second");
      ASSERT_EQ(2,list.size());

      Iterator it = list.end();
      --it;
      EXPECT_EQ(2, (*it).score);
      EXPECT_EQ("second", (*it).userName);
      
      ++it;
      EXPECT_TRUE(it == list.end());
    }

    /**
     * @brief データの挿入を行った後に、呼び出した際の挙動
     * @details ID:T038
     *          末尾要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
     * @return  Iterator
     */
    TEST(EndTest, T038) {
    // 先頭に挿入するケース
    {
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        list.pushBack(3, "third");

        list.insert(list.begin(), ScoreData{ 0, "zero" });
        ASSERT_EQ(4,list.size());

        Iterator it = list.end();
        --it;
        EXPECT_EQ(3, (*it).score);
        EXPECT_EQ("third", (*it).userName);
        ++it;
        EXPECT_TRUE(it == list.end());
    }

    // 中央に挿入するケース
    {
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        list.pushBack(3, "third");

        Iterator mid = list.begin();
        ++mid;
        list.insert(mid, ScoreData{ 9, "middle" });
        ASSERT_EQ(4,list.size());

        Iterator it = list.end();
        --it;
        EXPECT_EQ(3, (*it).score);
        EXPECT_EQ("third", (*it).userName);
        ++it;
        EXPECT_TRUE(it == list.end());
    }

    // 末尾に挿入するケース
    {
        ScoreList list;
        list.pushBack(1, "first");
        list.pushBack(2, "second");
        list.pushBack(3, "third");

        list.insert(list.end(), ScoreData{ 4, "fourth" });
        ASSERT_EQ(4,list.size());

        Iterator it = list.end();
        --it;
        EXPECT_EQ(4, (*it).score);
        EXPECT_EQ("fourth", (*it).userName);
        ++it;
        EXPECT_TRUE(it == list.end());
    }
    
}

    /**
     * @brief データの削除を行った後に、呼び出した際の挙動
     * @details ID:T039
     *          末尾要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
     * @return  Iterator
     */
     TEST(EndTest,T039){
        // 末尾の要素を削除するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          // (3, "third")
          Iterator last = list.end();
          --last;                     
          list.erase(last);
          ASSERT_EQ(2, list.size());
      
          Iterator it = list.end();
          --it;
          EXPECT_EQ(2, (*it).score);
          EXPECT_EQ("second", (*it).userName);
          ++it;
          EXPECT_TRUE(it == list.end());
        }
      
        // 中央の要素を削除するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          // (2, "second")
          Iterator mid = list.begin();
          ++mid;
          list.erase(mid);
          ASSERT_EQ(2, list.size());
      
          Iterator it = list.end();
          --it;
          EXPECT_EQ(3, (*it).score);
          EXPECT_EQ("third", (*it).userName);
          ++it;
          EXPECT_TRUE(it == list.end());
        }
      
        // 先頭の要素を削除するケース
        {
          ScoreList list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          // (1, "first")
          list.erase(list.begin());
          ASSERT_EQ(2, list.size());
      
          Iterator it = list.end();
          --it;
          EXPECT_EQ(3, (*it).score);
          EXPECT_EQ("third", (*it).userName);
          ++it;
          EXPECT_TRUE(it == list.end());
        }
      }

    /**
     * @brief constのメソッドであるか
     * @details ID:T040
     * @note   constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
     */
    TEST(EndTest,T040){
      SUCCEED()<<"手動テスト項目のためスキップします";
    }

  }

  //===================末尾コンストイテレータの取得======================
  namespace ConstEndTest{

    /**
     * @brief リストが空である場合に、呼び出した際の挙動
     * @details ID:T041
     *          ダミーノードを指すイテレータが返る
     * @return  ConstIterator
     */
    TEST(ConstEndTest,T041){
      ScoreList list;
      const ScoreList& clist = list;
      ConstIterator it = clist.end();
      EXPECT_TRUE(it == clist.end());
    }

    /**
     * @brief リストに要素が一つある場合に、呼び出した際の挙動
     * @details ID:T042
     *          末尾要素を指すイテレータが返る
     * @return  ConstIterator
     */
    TEST(ConstEndTest,T042){
      ScoreList list;
      const ScoreList& clist = list;
    
      list.pushBack(1, "first");
      ASSERT_EQ(1, clist.size());

      ConstIterator it = clist.end();
      --it;

      EXPECT_EQ(1, (*it).score);
      EXPECT_EQ("first", (*it).userName);
      
      ++it;
      EXPECT_TRUE(it == clist.end());
    }
    
    /**
     * @brief リストに二つ以上の要素がある場合に、呼び出した際の挙動
     * @details ID:T043
     *          末尾要素を指すイテレータが返る
     * @return  ConstIterator
     */
    TEST(ConstEndTest,T043){
      ScoreList list;
      const ScoreList& clist = list;

      list.pushBack(1, "first");
      list.pushBack(2, "second");
      ASSERT_EQ(2, clist.size());

      ConstIterator it = clist.end();
      --it;

      EXPECT_EQ(2, (*it).score);
      EXPECT_EQ("second", (*it).userName);
      
      ++it;
      EXPECT_TRUE(it == clist.end());
    }

    /**
     * @brief データの挿入を行った後に、呼び出した際の挙動
     * @details ID:T044
     *          末尾要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックすること
     * @return  ConstIterator
     */
     TEST(ConstEndTest, T044) {
        // 先頭に挿入するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.insert(clist.begin(), ScoreData{ 0, "zero" });
          ASSERT_EQ(4,clist.size());
      
          ConstIterator it = clist.end();
          --it;
          EXPECT_EQ(3, (*it).score);
          EXPECT_EQ("third", (*it).userName);
          ++it;
          EXPECT_TRUE(it == clist.end());
        }
      
        // 中央に挿入するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          ConstIterator mid = clist.begin();
          ++mid;
          list.insert(mid, ScoreData{ 9, "middle" });
          ASSERT_EQ(4,clist.size());
      
          ConstIterator it = clist.end();
          --it;
          EXPECT_EQ(3, (*it).score);
          EXPECT_EQ("third", (*it).userName);
          ++it;
          EXPECT_TRUE(it == clist.end());
        }
      
        // 末尾に挿入するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
      
          list.insert(clist.end(), ScoreData{ 4, "fourth" });
          ASSERT_EQ(4,clist.size());
      
          ConstIterator it = clist.end();
          --it;
          EXPECT_EQ(4, (*it).score);
          EXPECT_EQ("fourth", (*it).userName);
          ++it;
          EXPECT_TRUE(it == clist.end());
        }
      }

    /**
     * @brief データの削除を行った後に、呼び出した際の挙動
     * @details ID:T045
     *          末尾要素を指すイテレータが返る
     * @note    要素列の先頭、中央、末尾の要素の削除を行った場合の各ケースについてチェックすること
     * @return  ConstIterator
     */
     TEST(ConstEndTest,T045){
        //末尾の要素を削除するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
          ConstIterator last = clist.end();
          --last;                     // (3, "third")

          list.erase(last);
          ASSERT_EQ(2,clist.size());

          ConstIterator it = clist.end();
          --it;
          EXPECT_EQ(2, (*it).score);
          EXPECT_EQ("second", (*it).userName);
          ++it;
          EXPECT_TRUE(it == clist.end());
        }
        // 中央の要素を削除するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");
          ConstIterator mid = clist.begin();
          ++mid;                      // (2, "second")
          
          list.erase(mid);
          ASSERT_EQ(2,clist.size());
          
          ConstIterator it = clist.end();
          --it;
          EXPECT_EQ(3, (*it).score);
          EXPECT_EQ("third", (*it).userName);
          ++it;
          EXPECT_TRUE(it == clist.end());
        }
        // 先頭の要素を削除するケース
        {
          ScoreList list;
          const ScoreList& clist = list;
          list.pushBack(1, "first");
          list.pushBack(2, "second");
          list.pushBack(3, "third");

          list.erase(clist.begin());  // (1, "first")
          ASSERT_EQ(2,clist.size());

          ConstIterator it = clist.end();
          --it;
          EXPECT_EQ(3, (*it).score);
          EXPECT_EQ("third", (*it).userName);
          ++it;
          EXPECT_TRUE(it == clist.end());
        }
      }

    /**
     * @brief constのメソッドであるか
     * @details ID:T046
     * @note   constのリストから呼び出して、コンパイルエラーとならないかをチェック。自動テスト化しなくてよい。
     */
    TEST(ConstEndTest,T046){
      SUCCEED()<<"手動テスト項目のためスキップします";
    }

  }

}

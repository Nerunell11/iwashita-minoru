//2026-10-01 iwashita-minoru
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ScoreData.h"
#include "DoublyLinkedList.h"
#include "QuickSort.h"

using ScoreList = DoublyLinkedList<ScoreData>;

namespace { //mainで使う関数を定義します
    void printList(const ScoreList& list, std::ostream& os){
        for (const ScoreData& data : list ){
            os << data.score << '\t' << data.userName << '\n';
        }
    }

    /**
     * @brief ユーザー名をキーとして取り出す
     * @return const std::string& ユーザー名
     */
    auto getUserName(const ScoreData& data) -> const std::string& {
        return data.userName;
    }

    /**
     * @brief スコアをキーとして取り出す
     * @return int スコア
     */
    auto getScore(const ScoreData& data) -> int {
        return data.score;
    }

    /**
     * @brief ソートしてから見出し付きで出力する
     */
     template <typename KeyFunc>
     void sortAndPrint(ScoreList& list, KeyFunc getKey, SortOrder order, const char* title, std::ostream& os = std::cout){
        quickSort(list, getKey, order);
        os << "---" << title << "---" << '\n';
        printList(list, os);
     }
}


int main()
{
    std::cout << "Scores.txtのスコアとユーザー名を格納します\n"; 

    //直下のScores.txtを開く
    std::ifstream file("Scores.txt");
    if(!file){
        std::cerr <<"Scores.txtが開けません\n";
        return 1;
    }

    //スコアリストを作成
    ScoreList list;
    std::string line;
    int lineNo = 0;
    
    // 1行ずつ、スコアとユーザー名に分解する
    while (std::getline(file, line)){
        ++lineNo;
        if(line.empty()){
            continue;
        }

        //分解
        std::istringstream iss(line);
        int score = 0;
        std::string name;
        std::string extra;
        
        //スコアとユーザー名に分解できない場合はエラー
        if(!(iss >> score >> name ) || (iss >> extra)){
            std::cerr << "Scores.txtの" << lineNo << "行目の形式が不正です\n";
            return 1;
        }

        //スコアリストに追加
        ScoreList::Result result = list.insert(list.end(), ScoreData { score, name});
        if(result != ScoreList::Result::Success) {
            std::cout << lineNo << "行目の追加に失敗しました\n";
            std::cerr << "ScoreList::insert失敗:" << ScoreList::toMessage(result) << '\n';
            return 1;
        }
    }

    std::cout << "--- 読み込み順 ---\n";
    printList(list, std::cout);

    //ユーザー名をキーにソート
    sortAndPrint(list, getUserName, SortOrder::Ascending, "ユーザー名順(昇順)");
    sortAndPrint(list, getUserName, SortOrder::Descending, "ユーザー名順(降順)");
    
    //スコアをキーにソート
    sortAndPrint(list, getScore, SortOrder::Ascending, "スコア順(昇順)");
    sortAndPrint(list, getScore, SortOrder::Descending, "スコア順(降順)");

    //終了
    return 0;
}


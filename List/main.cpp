//2026-10-01 iwashita-minoru
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ScoreData.h"
#include "ScoreList.h"

namespace { //mainで使う関数を定義します
    void printList(const ScoreList& list, std::ostream& os){
        for (const ScoreData& data : list ){
            os << data.score << '\t' << data.userName << '\n';
        }
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
    

    printList(list, std::cout);

    //終了
    return 0;
}


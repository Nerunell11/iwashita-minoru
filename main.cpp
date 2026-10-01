//2026-10-01 iwashita-minoru
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ScoreData.h"
#include "ScoreList.h"

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
        list.pushBack(score,name);
    }
    
    std::ofstream out("result.txt");
    if (!out){
        std::cerr << "result.txtを開けません\n";
        return 1;
    }
    list.print(out);

    //終了
    return 0;
}


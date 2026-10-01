//2026-10-01 iwashita-minoru
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct ScoreData {
    int score;
    std::string userName;
};

struct Node{
    Node* prev;
    Node* next;
    ScoreData data;
};



class ScoreList
{
    private:
        Node* node;

    public:
    ScoreList(){
        node = new Node{ nullptr, nullptr, ScoreData{} };
        node->prev = node;
        node->next = node;
    }
    
    ~ScoreList(){
        Node* p = node->next;
        while(p != node){
            Node* next = p->next;
            delete p;
            p = next;
        }
        delete node;
    }
    
    //複製・移動禁止
    ScoreList(const ScoreList&) = delete;
    ScoreList& operator = (const ScoreList&) = delete;
    ScoreList(ScoreList&&) = delete;
    ScoreList& operator=(ScoreList&&) = delete;

    //スコアリストにデータを追加
    void pushBack(int score,const std::string& name){
        Node* added = new Node { node->prev, node, ScoreData{ score, name } };
        node->prev->next = added;
        node->prev = added;
    }

    //スコアリストを出力
    void print() const {
        for (const Node* p = node->next; p != node; p = p->next){
            std::cout << p->data.score << '\t' << p->data.userName << '\n';
        }
    }
};

int main()
{
    std::cout << "Scores.txtのスコアとユーザー名を格納します\n"; 

    //直下のScores.txtを開く
    std::ifstream file("Scores.txt");
    if(!file){
        std::cerr <<"Scores.txtが開けません\n";
        std::cout << "Enterで終了します\n";
        std::cin.get();
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
            std::cout << "Enterで終了します\n";
            std::cin.get();
            return 1;
        }

        //スコアリストに追加
        list.pushBack(score,name);
    }
    
    std::cout << "Scores.txtの中身を出力します\n";
    list.print();

    //終了処理
    std::cout << "Enterで終了します\n";
    std::cin.get();
    return 0;
}


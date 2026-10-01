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

class ConstIterator{
    protected:
        Node* current;
    
    public:
        explicit ConstIterator(Node* node ) : current(node){}
        
        ConstIterator(const ConstIterator& other) : current(other.current){}

        ConstIterator& operator=(const ConstIterator& other){
            current = other.current;
            return *this;
        }

        ConstIterator& operator++(){
            current = current->next;
            return *this;
        }

        ConstIterator& operator--(){
            current = current->prev;
            return *this;
        }

        const ScoreData& operator*() const {
            return current->data;
        }

        bool operator==(const ConstIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }
};

class Iterator : public ConstIterator{
    public:
        explicit Iterator(Node* node) : ConstIterator(node){}

        ScoreData& operator*(){
            return current->data;
        }
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

    Iterator begin(){
        return Iterator(node->next);
    }

    ConstIterator begin() const {
        return ConstIterator(node->next);
    }

    Iterator end(){
        return Iterator(node);
    }

    ConstIterator end() const {
        return ConstIterator(node);
    }


    //スコアリストを出力
    void print() const {
        for(ConstIterator it = begin(); it != end(); ++it){
            const ScoreData& data = *it;
            std::cout <<data.score << '\t' << data.userName << '\n';
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


#include <iostream>
#include <string>

enum EMovieGenreType {
    ACTION,
    COMEDY,
    SCIFI,
    HORROR,
    DRAMA,
};

class TMovie {
  public:
    TMovie(std::string title, std::string director, int year, float score,
           EMovieGenreType genre)
        : mTitle(title), mDirector(director), mYear(year), mScore(score),
          mGenre(genre) {}

    const std::string &GetTitle() const { return mTitle; }

    const std::string &GetDirector() const { return mDirector; }

    const int GetYear() const { return mYear; }

    const float GetScore() const { return mScore; }

    const EMovieGenreType GetGenre() const { return mGenre; }

  private:
    std::string mTitle;
    std::string mDirector;
    int mYear;
    float mScore;
    EMovieGenreType mGenre;
};

class TMovieNode {
  public:
    TMovieNode(TMovie _data) : data(_data) {}
    ~TMovieNode() { }

    TMovie data;
    TMovieNode *next = nullptr;
};

class TMovieList {
  public:
    TMovieList() { mHead = new TMovieNode(TMovie("", "", 0, 0.0, ::ACTION)); }
    void Append(TMovieNode node) {
        TMovieNode *currentNode = mHead;
        while (true) {
            if (currentNode->next == nullptr) {
                currentNode->next = new TMovieNode(node.data);
                return;
            }
            currentNode = currentNode->next;
        }
    }
    void Prepend(TMovieNode *node) {
        node->next = mHead->next;
        mHead->next = node;
    }

    TMovieNode *GetAtIndex(unsigned int index) { 
        TMovieNode *currentNode = mHead;
        for (unsigned int i = 0; i < index + 1; i++) {
            if (currentNode->next == nullptr)
                return nullptr;
            currentNode = currentNode->next;
        }
        return currentNode;
    }
    void Remove(unsigned int index) {
        TMovieNode *previousNode{}, *currentNode = mHead;
        for (unsigned int i = 0; i < index + 1; i++) {
            if (currentNode->next != nullptr) {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }
        if (previousNode != nullptr && currentNode != nullptr) {
            previousNode->next = currentNode->next;
            delete currentNode;
        }
    }
    void Reverse() {
        TMovieNode *previousNode{nullptr}, *nextNode{nullptr};
        
        for (TMovieNode *currentNode = mHead->next; currentNode != nullptr; currentNode = nextNode) {
            nextNode = currentNode->next;
            currentNode->next = previousNode;
            previousNode = currentNode;
        }
        mHead->next = previousNode;
    }

  private:
    TMovieNode *mHead;
};

void printList(TMovieList &list) {
    TMovieNode *currentNode = list.GetAtIndex(0);
    while (currentNode != nullptr) {
        std::cout << "Title: " << currentNode->data.GetTitle()
                  << ", Director: " << currentNode->data.GetDirector()
                  << ", Year: " << currentNode->data.GetYear()
                  << ", Score: " << currentNode->data.GetScore()
                  << ", Genre: " << currentNode->data.GetGenre() << std::endl;
        currentNode = currentNode->next;
    }
}

int main(int argc, char *argv[]) {

    TMovie m1 =  TMovie("Skogen", "Blend", 2002, 6.7, ::HORROR);
    TMovie m2 = TMovie("Pumpehuset", "Raman", 2003, 9.8, ::DRAMA);
    TMovie m3 = TMovie("Hatten", "Vegard", 2002, 9.1, ::SCIFI);
    TMovie m4 = TMovie("Burn", "Mads", 2002, 7.3, ::COMEDY);

    TMovieNode n1 = TMovieNode(m1);
    TMovieNode n2 = TMovieNode(m2);
    TMovieNode n3 = TMovieNode(m3);
    TMovieNode n4 = TMovieNode(m4);

    TMovieList list = {};
    list.Append(n1);
    list.Append(n2);
    list.Append(n3);
    list.Append(n4);

    printList(list);

    list.Reverse();
    
    printList(list);
    return 0;
}

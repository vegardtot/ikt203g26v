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
    TMovieNode(TMovie *_data) : data(_data) {}
    ~TMovieNode() { delete data; }

    TMovie *data = nullptr;
    TMovieNode *next = nullptr;
};

class TMovieList {
  public:
    void Append(TMovieNode *node) {
        TMovieNode *currentNode = mHead;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = node;
    }
    void Prepend(TMovieNode *node) {}
    TMovieNode *GetAtIndex(unsigned int index) { return mHead; }
    void Remove() {}
    void Reverse() {}

  private:
    TMovieNode *mHead;
};

int main(int argc, char *argv[]) {

    const auto a = EMovieGenreType::ACTION | EMovieGenreType::COMEDY;

    return 0;
}

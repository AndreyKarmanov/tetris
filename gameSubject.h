#ifndef GAMESUBJECT_H
#define GAMESUBJECT_H
#include <vector>
#include <string>
class GameObserver;
class GameBoard;
class Piece;

class GameSubject
{
private:
  std::vector<GameObserver *> observers;

protected:
  GameBoard *board;
  Piece *currentPiece, *nextPiece;
  int score, level, highScore;
  std::string name;

public:
  GameSubject(int level, int rows, int cols, std::string name);
  void attach(GameObserver *o);
  void detach(GameObserver *o);
  void notifyObservers();

  int getScore() const;
  int getLevel() const;
  int getHiScore() const;
  Piece *getPiece() const;
  Piece *getNextPiece() const;
  std::string getName() const;
  GameBoard *getBoard() const;

  virtual ~GameSubject();
};

#endif

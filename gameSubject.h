#ifndef GAMESUBJECT_H
#define GAMESUBJECT_H
#include <vector>

class GameObserver;
class GameBoard;

class GameSubject
{
private:
  std::vector<GameObserver *> observers;
protected:
  GameBoard *board;
  int score, level, highScore;
public:
  GameSubject(int level, int rows, int cols);
  void attach(GameObserver *o);
  void detach(GameObserver *o);
  void notifyObservers();

  int getScore() const;
  int getLevel() const;
  int getHiScore() const;
  GameBoard *getBoard() const;

  // name, active piece, etc. 

  virtual ~GameSubject();
};

#endif

#ifndef GAMESUBJECT_H
#define GAMESUBJECT_H
#include <vector>
#include <string>
class GameObserver;
class GameBoard;

class GameSubject
{
private:
  std::vector<GameObserver *> observers;
protected:
  GameBoard *board;
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
  std::string getName() const;
  GameBoard *getBoard() const;

  // name, active piece, etc. 

  virtual ~GameSubject();
};

#endif

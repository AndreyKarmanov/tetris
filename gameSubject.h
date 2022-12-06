#ifndef GAMESUBJECT_H
#define GAMESUBJECT_H
#include <vector>
#include <string>
class GameObserver;
class GameBoard;
class Piece;

// GameSubject is an abstract class that represents the subject in the observer pattern
class GameSubject
{
private:

  // The observers that are observing this subject
  std::vector<GameObserver *> observers;

protected:

  // The game state
  GameBoard *board;
  Piece *currentPiece, *nextPiece;
  int score, level, highScore;
  std::string name;

public:
// Constructor & Destructor
  GameSubject(int level, int rows, int cols, std::string name);
  virtual ~GameSubject();

  // Attach an observer to the subject
  void attach(GameObserver *o);

  // Detach the observer from the subject
  void detach(GameObserver *o);

  // Notify all observers of a change
  void notifyObservers();

  // Getters
  int getScore() const;
  int getLevel() const;
  int getHiScore() const;
  Piece *getPiece() const;
  Piece *getNextPiece() const;
  std::string getName() const;
  virtual GameBoard *getBoard() const;

};

#endif

#include "gameSubject.h"
#include "gameObserver.h"
#include "gameBoard.h"
#include "piece.h"

#include <string>

GameSubject::GameSubject(int level, int rows, int cols, std::string name) : board{new GameBoard(rows, cols)}, score{0}, level{level}, highScore{0}, name{name} {}

GameSubject::~GameSubject() { delete board; }

// attach an observer to the subject
void GameSubject::attach(GameObserver *o)
{
  observers.emplace_back(o);
}

// detach the observer from the subject
void GameSubject::detach(GameObserver *o)
{
  for (auto it = observers.begin(); it != observers.end(); ++it)
  {
    if (*it == o)
    {
      observers.erase(it);
      break;
    }
  }
}

// notify all observers of a change
void GameSubject::notifyObservers()
{
  for (auto ob : observers)
  {
    ob->notify();
  }
}

// get the score
int GameSubject::getScore() const { return score; }

// get the level
int GameSubject::getLevel() const { return level; }

// get the high score
int GameSubject::getHiScore() const { return highScore; }

Piece *GameSubject::getPiece() const { return currentPiece; }

Piece *GameSubject::getNextPiece() const { return nextPiece; }

std::string GameSubject::getName() const { return name; }

// get the board
GameBoard *GameSubject::getBoard() const { return board; }

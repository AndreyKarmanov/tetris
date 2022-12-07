#include "gameSubject.h"
#include "gameObserver.h"
#include "gameBoard.h"
#include "piece.h"

#include <string>

// Constructor
GameSubject::GameSubject(int level, int rows, int cols, std::string name) : board{new GameBoard(rows, cols)}, score{0}, level{level}, highScore{0}, name{name} {}

// Destructor
GameSubject::~GameSubject()
{
  delete board;
  delete currentPiece;
  delete nextPiece;
  delete heldPiece;
}

// Attach an observer to the subject
void GameSubject::attach(GameObserver *o)
{
  observers.emplace_back(o);
}

// Detach the observer from the subject
void GameSubject::detach(GameObserver *o)
{
  // Find the observer in the vector and remove it
  for (auto it = observers.begin(); it != observers.end(); ++it)
  {
    if (*it == o)
    {
      observers.erase(it);
      break;
    }
  }
}

// Notify all observers of a change
void GameSubject::notifyObservers()
{
  // notify all observers
  for (auto ob : observers)
  {
    ob->notify();
  }
}

// Get the score
int GameSubject::getScore() const { return score; }

// Get the level
int GameSubject::getLevel() const { return level; }

// Get the high score
int GameSubject::getHighScore() const { return highScore; }

// Get the current piece
Piece *GameSubject::getPiece() const { return currentPiece; }

// Get the next piece
Piece *GameSubject::getNextPiece() const { return nextPiece; }

// Get the held piece
Piece *GameSubject::getHeldPiece() const { return heldPiece; }

// Get the name of the player
std::string GameSubject::getName() const { return name; }

// Get the board
GameBoard *GameSubject::getBoard() const { return board; }

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "gameSubject.h"
class PieceFactory;
class Piece;

// Game is a concrete subject that represents the game state
// It is responsible for creating pieces, updating the board, and checking for game over
class Game : public GameSubject
{
private:

    // Player number
    int player;

    // Factory for creating pieces
    PieceFactory *factory;

    // Board Decorator for displaying blind effect
    GameBoard *blindBoard;
    
    // Flags for game state
    bool gameOver;

    // Flags for special actions
    bool heavyAttack, splitting, blind, heavyPieces;
    
    // Stats for checking for effects
    int dropsSinceClear, lastClearCount;

    // Stores sequence to use at level0
    std::string level0Seq;
    
    // Stores all created pieces, for cleaning memory
    std::vector<Piece *> oldPieces;

    // Stores position of current piece
    int row, col;

    // Clears lines on the board and updates the score
    void clearlines();

public:

    // Constructor & Destructor
    Game(std::string name, int level, int rows, int cols, bool random, int seed, std::string sequence);
    ~Game();

    // Returns number of rows cleared from last drop
    int getLastClearCount() const;

    // Returns whether the game is over
    bool getGameOver();

    // Moves the current piece
    void move(int right, int down, bool recurCall = false);
    
    // Drops the current piece
    void drop();

    // Rotates the current piece
    void rotateCW();
    void rotateCCW();

    // Creates a new piece
    void newPiece();

    // Sets the special effects and state
    void setLevel(int level);
    void setPiece(char type);
    void setHeavy(bool heavy);
    void setBlind(bool blind);
    void setRandom();
    void setSequence(std::string sequence);

    // Returns the board
    GameBoard *getBoard() const override;

    // Restarts the game
    void restart();

};

#endif

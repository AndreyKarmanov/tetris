#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "gameSubject.h"
class PieceFactory;
class Piece;

class Game : public GameSubject
{
private:
    int player;

    PieceFactory *factory;
    GameBoard *blindBoard;
    bool gameOver;
    bool heavyAttack, splitting, blind, heavyPieces;
    int dropsSinceClear, lastClearCount;
    std::string level0Seq;
    std::vector<Piece *> oldPieces;

    int row, col;
    void clearlines();

public:
    Game(std::string name, int level, int rows, int cols, bool random, int seed, std::string sequence);
    ~Game();

    int getLastClearCount() const;

    void move(int right, int down, bool recurCall = false);
    void drop();
    void rotateCW();
    void rotateCCW();

    void newPiece();
    void setLevel(int level);
    void setPiece(char type);
    void setHeavy(bool heavy);
    void setBlind(bool blind);
    void setRandom();
    void setSequence(std::string sequence);

    GameBoard *getBoard() const override;

    void restart();
    bool getGameOver();
};

#endif

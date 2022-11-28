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
    std::string name;
    PieceFactory *factory;
    bool gameOver;
    // current piece
    Piece *currentPiece;
    int row, col;

    void clearlines();
public:
    Game(std::string name, PieceFactory *factory, int rows, int cols);
    ~Game();

    void move(int right, int down);
    void drop();
    void rotateCW();
    void rotateCCW();


    void setLevel(int level);
    void setPiece(char type);

    void restart();
    bool getGameOver();
};

#endif

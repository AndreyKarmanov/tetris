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
    int player;
    
    PieceFactory *factory;
    bool gameOver;
    bool heavy, splitting, blind;
    // current piece
    Piece *currentPiece;
    int row, col;
    void clearlines();
public:
    Game(std::string name, int level, int rows, int cols, bool random, int seed, int player);
    ~Game();

    void move(int right, int down);
    void drop();
    void rotateCW();
    void rotateCCW();


    void setLevel(int level);
    void setPiece(char type);
    void setHeavy(bool heavy);
    
    void random(bool random);
    void restart();
    bool getGameOver();
};

#endif

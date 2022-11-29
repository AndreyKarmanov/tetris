#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

class Piece;

class GameBoard
{
private:        
    // all pieces in play
    std::vector<Piece *> pieces;
    
    // board with all piece positions
    int rows, cols;
    std::vector<std::vector<Piece *>> board;
    
public:
    GameBoard(int rows, int cols);
    ~GameBoard();

    int getRows();
    int getCols();
    void setPiece(Piece *piece, int row, int col);
    Piece *getPiece(int row, int col);
};

#endif

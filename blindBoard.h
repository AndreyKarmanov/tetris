#ifndef BLINDBOARD_H
#define BLINDBOARD_H

#include "gameBoard.h"
class Piece;

class BlindBoard : public GameBoard
{
private:
    GameBoard *boardptr;
    Piece* blindPiece;
    int row, col;
    int blindRows, blindCols;
public:
    BlindBoard(GameBoard *board, int row, int col, int blindRows, int blindCols);
    ~BlindBoard();

    Piece *getPiece(int row, int col) override;
};

#endif

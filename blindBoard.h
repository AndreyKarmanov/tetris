#ifndef BLINDBOARD_H
#define BLINDBOARD_H

#include "gameBoard.h"
class Piece;

class BlindBoard : public GameBoard
{
private:
    // Underlying, non-blind board
    GameBoard *boardptr;

    // Blind piece, used to hide the underlying board
    Piece* blindPiece;

    // Blind area coordinates and dimensions
    int row, col;
    int blindRows, blindCols;
public:

    // Constructor & Destructor
    BlindBoard(GameBoard *board, int row, int col, int blindRows, int blindCols);
    ~BlindBoard();

    // Returns the piece at the given coordinates, or a blind piece if the coordinates are within the blind area
    Piece *getPiece(int row, int col) override;
};

#endif

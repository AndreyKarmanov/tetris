#include "blindBoard.h"
#include "piece.h"
#include "window.h"
BlindBoard::BlindBoard(GameBoard *board, int row, int col, int blindRows, int blindCols)
    : GameBoard(0, 0), boardptr{board}, blindPiece{new Piece({{true}}, 0, Xwindow::Brown, '?', false)},
      row{row}, col{col}, blindRows{blindRows}, blindCols{blindCols} {}

BlindBoard::~BlindBoard()
{
    delete blindPiece;
}

Piece *BlindBoard::getPiece(int y, int x)
{
    if ((y >= row && y < row + blindRows) && (x >= col && x < col + blindCols))
    {
        return blindPiece;
    }
    return boardptr->getPiece(row + this->row, col + this->col);
}
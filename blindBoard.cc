#include "blindBoard.h"
#include "piece.h"
#include "window.h"

// Constructor
// Initializes the blind board with the given board, blind area coordinates, and blind area dimensions, as well as a blind piece
BlindBoard::BlindBoard(GameBoard *board, int row, int col, int blindRows, int blindCols)
    : GameBoard(board->getRows(), board->getCols()), boardptr{board}, blindPiece{new Piece({{true}}, 0, Xwindow::Brown, '?', false)},
      row{row}, col{col}, blindRows{blindRows}, blindCols{blindCols} {}

// Destructor
BlindBoard::~BlindBoard()
{
    delete blindPiece;
}

// Returns the piece at the given coordinates, or a blind piece if the coordinates are within the blind area
Piece *BlindBoard::getPiece(int y, int x)
{
    if ((y >= row && y <= row + blindRows) && (x >= col && x <= col + blindCols))
    {
        return blindPiece;
    }
    return boardptr->getPiece(y, x);
}

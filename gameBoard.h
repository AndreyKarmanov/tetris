#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>

class Piece;

// GameBoard is a class that represents a game board
class GameBoard
{
private:
    // The number of rows and columns in the board
    int rows, cols;

    // The board itself
    std::vector<std::vector<Piece *>> board;

public:
    // Constructor & Destructor
    GameBoard(int rows, int cols);
    virtual ~GameBoard();

    // Returns the number of rows and columns in the board
    int getRows();
    int getCols();

    // Returns the piece at the given coordinates
    virtual Piece *getPiece(int row, int col);

    // Sets an individual cell on the board
    void setPiece(Piece *piece, int row, int col);

    // Draws the given piece on the board at the given coordinates
    void drawPiece(Piece *piece, int row, int col);

    // Erases the given piece from the board at the given coordinates
    void erasePiece(Piece *piece, int row, int col);

    // Checks if the given piece intersects with any other piece on the board
    // or if it is out of bounds
    bool intersects(Piece *piece, int row, int col);

    // Clears the board
    void clear();
};

#endif

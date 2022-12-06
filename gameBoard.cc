#include "gameBoard.h"
#include "piece.h"

// Constructor
// Initializes the game board with the given number of rows and columns
GameBoard::GameBoard(int rows, int cols)
    : rows{rows}, cols{cols}, board{std::vector<std::vector<Piece *>>(rows, std::vector<Piece *>(cols, nullptr))} {}

// Destructor
GameBoard::~GameBoard() {}

// Returns the number of rows
int GameBoard::getRows() { return rows; }

// Returns the number of columns
int GameBoard::getCols() { return cols; }

// Returns the piece at the given coordinates
Piece *GameBoard::getPiece(int row, int col) { return board[row][col]; }

// Sets an individual cell on the board
void GameBoard::setPiece(Piece *piece, int row, int col) { board[row][col] = piece; }

// Draws the given piece on the board at the given coordinates
void GameBoard::drawPiece(Piece *piece, int row, int col)
{
    auto grid = piece->getGrid();
    int tempcol = col;
    for (auto vec : grid)
    {
        col = tempcol;
        for (auto cell : vec)
        {
            if (cell)
            {
                board[row][col] = piece;
            }
            col++;
        }
        row++;
    }
}

// Erases the given piece from the board at the given coordinates
void GameBoard::erasePiece(Piece *piece, int row, int col)
{
    auto grid = piece->getGrid();
    int tempcol = col;
    for (auto vec : grid)
    {
        col = tempcol;
        for (auto cell : vec)
        {
            if (cell)
            {
                board[row][col] = nullptr;
            }
            col++;
        }
        row++;
    }
}

// Checks if the given piece intersects with any other piece on the board
bool GameBoard::intersects(Piece *piece, int row, int col)
{
    auto grid = piece->getGrid();
    int tempcol = col;
    for (auto vec : grid)
    {
        col = tempcol;
        for (auto cell : vec)
        {
            if (cell)
            {
                if (row < 0 || row >= rows || col < 0 || col >= cols)
                {
                    return true;
                }
                auto tmp = board[row][col];
                if (tmp != nullptr && tmp != piece)
                {
                    return true;
                }
            }
            ++col;
        }
        ++row;
    }
    return false;
}

// Clears the board
void GameBoard::clear()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            board[i][j] = nullptr;
        }
    }
}

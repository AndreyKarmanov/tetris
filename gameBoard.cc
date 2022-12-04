#include "gameBoard.h"
#include "piece.h"

GameBoard::GameBoard(int rows, int cols) : rows{rows}, cols{cols}, board{std::vector<std::vector<Piece *>>(rows, std::vector<Piece *>(cols, nullptr))} {}

GameBoard::~GameBoard() {}

int GameBoard::getRows() { return rows; }

int GameBoard::getCols() { return cols; }

Piece *GameBoard::getPiece(int row, int col) { return board[row][col]; }

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
void GameBoard::setPiece(Piece *piece, int row, int col) { board[row][col] = piece; }

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

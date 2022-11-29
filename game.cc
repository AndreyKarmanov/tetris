#include "game.h"
#include "gameSubject.h"
#include "piece.h"
#include "pieceFactory.h"
#include "gameBoard.h"

void drawPiece(GameBoard *board, Piece *piece, int row, int col)
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
                board->setPiece(piece, row, col);
            }
            col++;
        }
        row++;
    }
}

void erasePiece(GameBoard *board, Piece *piece, int row, int col)
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
                board->setPiece(nullptr, row, col);
            }
            col++;
        }
        row++;
    }
}

bool intersects(GameBoard *board, Piece *piece, int row, int col)
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
                if (row < 0 || row >= board->getRows() || col < 0 || col >= board->getCols())
                {
                    return true;
                }
                auto tmp = board->getPiece(row, col);
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

Game::Game(std::string name, PieceFactory *factory, int rows, int cols) : GameSubject{rows, cols}, name{name}, factory{factory} {}

Game::~Game() {}

void Game::move(int right, int down)
{
    if (intersects(board, currentPiece, row + down, col + right))
    {
        return;
    }
    erasePiece(board, currentPiece, row, col);
    row += down;
    col += right;
    drawPiece(board, currentPiece, row, col);
}

void Game::rotateCW()
{
    erasePiece(board, currentPiece, row, col);
    currentPiece->rotateCW();
    if (intersects(board, currentPiece, row, col))
    {
        currentPiece->rotateCCW();
    }
    drawPiece(board, currentPiece, row, col);
}

void Game::rotateCCW()
{
    erasePiece(board, currentPiece, row, col);
    currentPiece->rotateCCW();
    if (intersects(board, currentPiece, row, col))
    {
        currentPiece->rotateCW();
    }
    drawPiece(board, currentPiece, row, col);
}
 
void Game::drop()
{
    while (!intersects(board, currentPiece, row + 1, col))
    {
        erasePiece(board, currentPiece, row, col);
        row++;
        drawPiece(board, currentPiece, row, col);
    }
    currentPiece = factory->getPiece(level);
    row = 0;
    col = 0;
    if (intersects(board, currentPiece, row, col))
    {
        gameOver = true;
    }
    clearlines();
    drawPiece(board, currentPiece, row, col);
}

void Game::setLevel(int level)
{
    this->level = level;
}

void Game::setPiece(char type)
{
    currentPiece = factory->getPiece(type, level);
    row = 0;
    col = 0;
    drawPiece(board, currentPiece, row, col);
}

bool Game::getGameOver()
{
    return gameOver;
}

void Game::clearlines()
{
    for (int i = 0; i < board->getRows(); ++i)
    {
        bool full = true;
        for (int j = 0; j < board->getCols(); ++j)
        {
            if (board->getPiece(i, j) == nullptr)
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            for (int j = 0; j < board->getCols(); ++j)
            {
                board->setPiece(nullptr, i, j);
            }
            for (int k = i; k > 0; --k)
            {
                for (int j = 0; j < board->getCols(); ++j)
                {
                    board->setPiece(board->getPiece(k - 1, j), k, j);
                }
            }
        }
    }
}
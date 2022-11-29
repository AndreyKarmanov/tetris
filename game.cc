#include "game.h"
#include "gameSubject.h"
#include "piece.h"
#include "pieceFactory.h"
#include "gameBoard.h"

Game::Game(std::string name, int level, int rows, int cols, bool random, int seed, int player)
    : GameSubject{level, rows, cols}, name{name}, player{player}
{
    factory = new PieceFactory{"STLOZSI", random, seed};
    // if (level == 0)
    // {
    //     factory = new PieceFactory(std::string{"sequence" + std::to_string(player) + ".txt"}, random, seed);
    // }
    // else
    // {
    //     factory = new PieceFactory("level" + std::to_string(level) + ".txt", random, seed);
    // }
}

Game::~Game()
{
    delete factory;
}

void Game::move(int right, int down)
{
    if (board->intersects(currentPiece, row + down, col + right))
    {
        return;
    }
    board->erasePiece(currentPiece, row, col);
    row += down;
    col += right;
    board->drawPiece(currentPiece, row, col);
}

void Game::rotateCW()
{
    board->erasePiece(currentPiece, row, col);
    currentPiece->rotateCW();
    if (board->intersects(currentPiece, row, col))
    {
        currentPiece->rotateCCW();
    }
    board->drawPiece(currentPiece, row, col);
}

void Game::rotateCCW()
{
    board->erasePiece(currentPiece, row, col);
    currentPiece->rotateCCW();
    if (board->intersects(currentPiece, row, col))
    {
        currentPiece->rotateCW();
    }
    board->drawPiece(currentPiece, row, col);
}

void Game::drop()
{
    while (!board->intersects(currentPiece, row + 1, col))
    {
        board->erasePiece(currentPiece, row, col);
        row++;
        board->drawPiece(currentPiece, row, col);
    }
    currentPiece = factory->getPiece(level);
    row = 0;
    col = 0;
    if (board->intersects(currentPiece, row, col))
    {
        gameOver = true;
    }
    clearlines();
    board->drawPiece(currentPiece, row, col);
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
    board->drawPiece(currentPiece, row, col);
}

bool Game::getGameOver()
{
    return gameOver;
}

void Game::clearlines()
{   
    int lines = 0;
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
                Piece *p = board->getPiece(i, j);
                if (p->chSize(p->getSize() - 1) == 0)
                {
                    score += (p->getLevel() + 1) * (p->getLevel() + 1);
                    delete p;
                }
                board->setPiece(nullptr, i, j);
            }
            for (int k = i; k > 0; --k)
            {
                for (int j = 0; j < board->getCols(); ++j)
                {
                    board->setPiece(board->getPiece(k - 1, j), k, j);
                }
            }
            --i;
            ++lines;
        }
    }
    if (lines > 0)
    {
        score += (level + lines) * (level + lines);
    }
    if (score > highScore)
    {
        highScore = score;
    }
}
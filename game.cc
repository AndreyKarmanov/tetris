#include "game.h"
#include "gameSubject.h"
#include "piece.h"
#include "pieceFactory.h"
#include "gameBoard.h"

#include <algorithm>

Game::Game(std::string name, int level, int rows, int cols, bool random, int seed, int player)
    : GameSubject{level, rows, cols, name}, player{player}, factory{new PieceFactory{"STLOZSI", random, seed}}, gameOver{false}, heavyAttack{false}, splitting{false}, blind{false}, heavyPieces{false}, dropsSinceClear{0}, lastClearCount{0}
{
    setLevel(level);
    newPiece();
}

Game::~Game()
{
    for (auto p : oldPieces)
    {
        delete p;
    }
    if (currentPiece)
    {
        delete currentPiece;
    }
    delete factory;
}

void Game::move(int right, int down, bool recurCall)
{

    if (board->intersects(currentPiece, row + down, col + right))
    {
        if (heavyAttack && recurCall)
        {
            drop();
        }
        return;
    }

    board->erasePiece(currentPiece, row, col);
    row += down;
    col += right;
    board->drawPiece(currentPiece, row, col);

    if (currentPiece->isHeavy() && !recurCall)
    {
        move(0, 1, true);
    }

    if (heavyAttack && !recurCall)
    {
        move(0, 1, true);
    }
}

int Game::getLastClearCount() const
{
    return lastClearCount;
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
    if (currentPiece->isHeavy())
    {
        move(0, 1);
    };
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
    if (currentPiece->isHeavy())
    {
        move(0, 1);
    };
}

void Game::drop()
{
    oldPieces.push_back(currentPiece);
    while (!board->intersects(currentPiece, row + 1, col))
    {
        board->erasePiece(currentPiece, row, col);
        ++row;
        board->drawPiece(currentPiece, row, col);
    }
    clearlines();

    if (splitting && ++dropsSinceClear % 5 == 0)
    {
        currentPiece = factory->getPiece('*', level, heavyPieces);
        col = (board->getCols() - currentPiece->getWidth()) / 2;
        row = 0;
        if (board->intersects(currentPiece, row, col))
        {
            gameOver = true;
            return;
        }
        drop();
    }
    else
    {
        newPiece();
    }
}

void Game::newPiece()
{
    if (nextPiece == nullptr)
    {
        nextPiece = factory->getPiece(level, heavyPieces);
    }
    currentPiece = nextPiece;
    nextPiece = factory->getPiece(level, heavyPieces);
    col = (board->getCols() - currentPiece->getWidth()) / 2;
    row = 0;
    if (board->intersects(currentPiece, row, col))
    {
        gameOver = true;
    }
    board->drawPiece(currentPiece, row, col);
}

void Game::setLevel(int level)
{
    level = std::min(4, std::max(0, level));
    this->level = level;
    factory->setRandom(true);
    if (level == 1)
    {
        factory->updatePieces("IJLOTIJLOTSZ");
        heavyPieces = splitting = false;
    }
    else if (level == 2)
    {
        factory->updatePieces("IJLOTSZ");
        heavyPieces = splitting = false;
    }
    else if (level >= 3)
    {
        factory->updatePieces("IJLOTSZSZ");
        heavyPieces = true, splitting = false;
    }
    if (level >= 4)
    {
        splitting = true;
    }
}

void Game::setPiece(char type)
{
    Piece *temp = factory->getPiece(type, level, heavyPieces);
    if (temp != nullptr)
    {
        board->erasePiece(currentPiece, row, col);
        delete currentPiece;
        currentPiece = temp;
        col = (board->getCols() - currentPiece->getWidth()) / 2;
        row = 0;
        board->drawPiece(currentPiece, row, col);
    }
    else
    {
        delete temp;
    }
}

void Game::setHeavy(bool heavy)
{
    this->heavyAttack = heavy;
}

void Game::setRandom()
{
    factory->setRandom(true);
}

void Game::setSequence(std::string sequence)
{
    factory->updatePieces(sequence);
    factory->setRandom(false);
}

void Game::restart()
{
    board->clear();
    for (auto p : oldPieces)
    {
        delete p;
    }
    oldPieces.clear();
    if (currentPiece)
    {
        delete currentPiece;
    }
    currentPiece = nullptr;
    gameOver = false;
    dropsSinceClear = 0;
    lastClearCount = 0;
    newPiece();
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
        dropsSinceClear = 0;
    }
    if (score > highScore)
    {
        highScore = score;
    }

    lastClearCount = lines;
}
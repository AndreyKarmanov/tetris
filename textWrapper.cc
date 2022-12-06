#include "textWrapper.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "piece.h"

#include <vector>
#include <iostream>
#include <sstream>

TextWrapper::TextWrapper(std::vector<GameSubject *> games)
{
    int player = 0;
    for (auto game : games)
    {
        observers.emplace_back(new TextObserver{game});
        game->attach(observers.back());
    }
}

TextWrapper::TextObserver::TextObserver(GameSubject *game) : GameObserver{game} {}

void TextWrapper::TextObserver::notify()
{
    GameBoard *board = game->getBoard();
    std::stringstream ss;
    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;
    ss << "| Level   : " << game->getLevel() << std::endl;
    ss << "| Score   : " << game->getScore() << std::endl;
    ss << "| Hi Score: " << game->getHiScore() << std::endl;

    Piece *np = game->getNextPiece();
    auto grid = np->getGrid();
    for (auto vec : grid)
    {
        for (auto cell : vec)
        {
            if (cell)
            {
                ss << np->getType();
            }
            else
            {
                ss << " ";
            }
        }
        ss << std::endl;
    }

    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;
    for (int rows = 0; rows < board->getRows(); ++rows)
    {
        ss << "|";
        for (int cols = 0; cols < board->getCols(); ++cols)
        {
            Piece *p = board->getPiece(rows, cols);
            if (p != nullptr)
            {
                ss << p->getType();
            }
            else
            {
                ss << " ";
            }
        }
        ss << "|" << std::endl;
    }
    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;
    std::cout << ss.str();
}

TextWrapper::TextObserver::~TextObserver() {}

TextWrapper::~TextWrapper()
{
    for (auto ob : observers)
    {
        delete ob;
    }
}

void TextWrapper::notifyAll()
{
    for (auto ob : observers)
    {
        ob->notify();
    }
}

#include "textWrapper.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "piece.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

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

std::stringstream TextWrapper::TextObserver::generateBoard()
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
    ss << "| Hi Score: " << game->getHighScore() << std::endl;

    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;
    for (int rows = 3; rows < board->getRows(); ++rows)
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

    ss << "Next:" << std::endl;
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
    if (np->getType() == 'O')
    {
        ss << std::endl;
    }
    if (np->getType() != 'I')
    {
        ss << std::endl;
    }

    return ss;
}

void TextWrapper::TextObserver::notify()
{
    std::cout << generateBoard().str();
}

TextWrapper::TextObserver::~TextObserver() {}

TextWrapper::~TextWrapper()
{
    for (auto ob : observers)
    {
        delete ob;
    }
}

void TextWrapper::printLine(std::string curline)
{
    std::cout << curline;
    for (int i = curline.size(); i < 20; ++i) {
        std::cout << " ";
    }
}

void TextWrapper::notifyAll()
{
    std::vector<std::stringstream> boards;
    for (auto ob : observers)
    {
        boards.push_back(ob->generateBoard());
 //       ob->notify();
    }
    int boardNum = boards.size();
    std::string curline;
    while (getline(boards[0], curline))
    {
        printLine(curline);
        for (int i = 1; i < boardNum; ++i) {
            getline(boards[i], curline);
            printLine(curline);
        }
        std::cout << std::endl;
    }
}

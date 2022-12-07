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

void TextWrapper::printLine(std::string curline, int padding)
{
    std::cout << curline;
    for (int i = curline.size(); i < padding; ++i) {
        std::cout << " ";
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

    std::stringstream nexts;
    nexts << "Next:" << std::endl;
    Piece *np = game->getNextPiece();
    auto grid = np->getGrid();
    for (auto vec : grid)
    {
        for (auto cell : vec)
        {
            if (cell)
            {
                nexts << np->getType();
            }
            else
            {
                nexts << " ";
            }
        }
        nexts << std::endl;
    }
    if (np->getType() == 'O')
    {
        nexts << std::endl;
    }
    if (np->getType() != 'I')
    {
        nexts << std::endl;
    }

    if (game->getHeldPiece()) {
        std::stringstream helds;
        helds << "Held:" << std::endl;
        Piece *hp = game->getHeldPiece();
        auto grid = hp->getGrid();
        for (auto vec : grid)
        {
            for (auto cell : vec)
            {
                if (cell)
                {
                    helds << hp->getType();
                }
                else
                {
                    helds << " ";
                }
            }
            helds << std::endl;
        }

        std::string curline;
        while (getline(nexts, curline))
        {
            ss << curline;
            for (int i = curline.size(); i < 8; ++i)
            {
                ss << " ";
            }
            if (getline(helds, curline)) {
                ss << curline;
            }
            ss << std::endl;
        }
    }
    else {
        ss << nexts.str();
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
        printLine(curline, 20);
        for (int i = 1; i < boardNum; ++i) {
            getline(boards[i], curline);
            printLine(curline, 20);
        }
        std::cout << std::endl;
    }
}

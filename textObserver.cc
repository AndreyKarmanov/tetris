#include "textObserver.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "piece.h"

#include <vector>
#include <iostream>
#include <sstream>

TextObserver::TextObserver(GameSubject *game) : GameObserver{game} {}

void TextObserver::notify() {
    GameBoard *board = game->getBoard();
    std::stringstream ss;
    ss << "+" << std::endl;
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "| Level: " << game->getLevel() << std::endl;
    ss << "| Score: " << game->getScore() << std::endl;
    ss << "| Hi Score: " << game->getHiScore() << std::endl;
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

TextObserver::~TextObserver() {}

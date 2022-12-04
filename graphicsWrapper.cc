#include "graphicsWrapper.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "window.h"
#include "piece.h"

GraphicsWrapper::GraphicsWrapper(std::vector<GameSubject *> games) : w{new Xwindow{500, 500}} {
    int player = 0;
    for (auto game : games) {
        observers.emplace_back(new GraphicsObserver{game, player++ * (game->getBoard()->getCols() * 10 + 20), 0, w});
        game->attach(observers.back());
    }
    w->fillRectangle(0, 0, 500, 500, Xwindow::Black);
}

GraphicsWrapper::GraphicsObserver::GraphicsObserver(GameSubject *game, int x, int y, Xwindow *w) : GameObserver{game}, x{x}, y{y}, w{w} {}

void GraphicsWrapper::GraphicsObserver::notify() {
    GameBoard *board = game->getBoard();
    for (int rows = 0; rows < board->getRows(); ++rows)
    {
        for (int cols = 0; cols < board->getCols(); ++cols)
        {
            Piece *p = board->getPiece(rows, cols);
            if (p != nullptr)
            {
                w->fillRectangle(x + cols * 10, y + rows * 10, 10, 10, p->getColour());
            }
            else
            {
                w->fillRectangle(x + cols * 10, y + rows * 10, 10, 10, 0);
            }
        }
    }
}

GraphicsWrapper::GraphicsObserver::~GraphicsObserver() {}

GraphicsWrapper::~GraphicsWrapper() {
    for (auto ob : observers) {
        delete ob;
    }
    delete w;
}

void GraphicsWrapper::notifyAll() {
    for (auto ob : observers) {
        ob->notify();
    }
}
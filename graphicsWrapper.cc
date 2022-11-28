#include "graphicsWrapper.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "window.h"
#include "piece.h"

GraphicsWrapper::GraphicsWrapper(std::vector<GameSubject *> games) : w{new Xwindow{500, games.size() * 5 + 20}} {
    for (auto game : games) {
        observers.emplace_back(new GraphicsObserver{game, 10, game->getBoard()->getCols() * 5 + 20, w});
        game->attach(observers.back());
    }
}

GraphicsWrapper::GraphicsObserver::GraphicsObserver(GameSubject *game, int x, int y, Xwindow *w) : GameObserver{game}, x{x}, y{y}, w{w} {}

void GraphicsWrapper::GraphicsObserver::notify() {
    GameBoard *board = game->getBoard();
    for (int rows = 0; rows < board->getRows(); ++rows)
    {
        for (int cols = 0; cols < board->getCols(); ++cols)
        {
            w->fillRectangle(x + cols * 5, y + rows * 5, 5, 5, board->getPiece(rows, cols)->getType());
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

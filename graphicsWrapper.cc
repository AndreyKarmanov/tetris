#include "graphicsWrapper.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "window.h"
#include "piece.h"

GraphicsWrapper::GraphicsWrapper(std::vector<GameSubject *> games) : w{new Xwindow{500, 500}}
{
    int player = 0;
    for (auto game : games)
    {
        observers.emplace_back(new GraphicsObserver{game, player++ * (game->getBoard()->getCols() * 10 + 20) + 20, 20, w});
        game->attach(observers.back());
    }
    w->fillRectangle(0, 0, 500, 500, Xwindow::Black);
}

GraphicsWrapper::GraphicsObserver::GraphicsObserver(GameSubject *game, int x, int y, Xwindow *w) : GameObserver{game}, x{x}, y{y}, w{w}
{
    for (int rows = 0; rows < game->getBoard()->getRows(); ++rows)
    {
        std::vector<int> row(game->getBoard()->getCols(), Xwindow::Black);
        currBoard.emplace_back(row);
    }
}

void GraphicsWrapper::GraphicsObserver::notify()
{
    GameBoard *board = game->getBoard();
    for (int rows = 0; rows < board->getRows(); ++rows)
    {
        for (int cols = 0; cols < board->getCols(); ++cols)
        {
            Piece *p = board->getPiece(rows, cols);
            if (p != nullptr)
            {
                if (currBoard[rows][cols] != p->getColour())
                {
                    currBoard[rows][cols] = p->getColour();
                    w->fillRectangle(x + cols * 10, y + rows * 10, 10, 10, p->getColour());
                }
            }
            else
            {
                if (currBoard[rows][cols] != Xwindow::White)
                {
                    currBoard[rows][cols] = Xwindow::White;
                    w->fillRectangle(x + cols * 10, y + rows * 10, 10, 10, Xwindow::White);
                }
            }
        }
    }

    // a white rectangle is drawn behind so that the black text is visible
    w->fillRectangle(x, y + 20 + (board->getRows() * 10), board->getCols() * 10, 100, Xwindow::White);
    // each stat is drawn
    w->drawString(x + 10, y + 40 + (board->getRows() * 10), "Score: " + std::to_string(game->getScore()));
    w->drawString(x + 10, y + 55 + (board->getRows() * 10), "HiScore: " + std::to_string(game->getScore()));
    w->drawString(x + 10, y + 70 + (board->getRows() * 10), "Next:");

    std::vector<std::vector<bool>> grid = game->getNextPiece()->getGrid();
    auto curColour = game->getNextPiece()->getColour();

    // a white background is drawn each time behind the next piece
    w->fillRectangle(x + 10, y + 80 + (board->getRows() * 10), 30, 30, Xwindow::White);
    {
        // the next piece is drawn
        // we must loop over each cell in the grid to draw it to the screen
        for (int rows = 0; rows < grid.size(); ++rows)
        {
            for (int cols = 0; cols < grid[0].size(); ++cols)
            {
                if (grid[rows][cols])
                {
                    w->fillRectangle(x + 10 + rows * 10, y + cols * 10 + 80 + (board->getRows() * 10), 10, 10, curColour);
                }
            }
        }
    }
}

GraphicsWrapper::GraphicsObserver::~GraphicsObserver() {}

GraphicsWrapper::~GraphicsWrapper()
{
    for (auto ob : observers)
    {
        delete ob;
    }
    delete w;
}

void GraphicsWrapper::notifyAll()
{
    for (auto ob : observers)
    {
        ob->notify();
    }
}
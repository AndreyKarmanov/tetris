#ifndef GRAPHICSGAMEOBSERVER_H
#define GRAPHICSGAMEOBSERVER_H

#include <vector>
#include "gameObserver.h"
class Xwindow;

class GraphicsWrapper
{
private:
    Xwindow *w;

    class GraphicsObserver : public GameObserver
    {
    private:
        int x, y;
        Xwindow *w;
        std::vector<std::vector<int>> currBoard;

    public:
        GraphicsObserver(GameSubject *game, int x, int y, Xwindow *w);
        virtual void notify();
        ~GraphicsObserver();
    };

    std::vector<GraphicsObserver *> observers;
    
public:
    GraphicsWrapper(std::vector<GameSubject *> games);
    ~GraphicsWrapper();

    void notifyAll();
};

#endif

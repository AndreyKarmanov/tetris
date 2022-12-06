#ifndef GRAPHICSGAMEOBSERVER_H
#define GRAPHICSGAMEOBSERVER_H

#include <vector>
#include "gameObserver.h"
class Xwindow;

// GraphicsObserver is a wrapper for concrete observers
// The observers display the game state using a common Xwindow
class GraphicsWrapper
{
private:
    // The Xwindow that all observers use
    Xwindow *w;

    // GraphicsObserver is a concrete observer that displays the game state using an Xwindow
    class GraphicsObserver : public GameObserver
    {
    private:
        // Relative position of the observer's window
        int x, y;

        // The Xwindow that the observer uses
        Xwindow *w;

        // The current state of the board that is being displayed
        std::vector<std::vector<int>> currBoard;

    public:
        // Constructor & Destructor
        GraphicsObserver(GameSubject *game, int x, int y, Xwindow *w);
        ~GraphicsObserver();

        // Notify the observer of a change
        virtual void notify();
    };

    // The observers that are observing the subject
    std::vector<GraphicsObserver *> observers;

public:
    // Constructor & Destructor/
    GraphicsWrapper(std::vector<GameSubject *> games);
    ~GraphicsWrapper();

    // Notify all observers of a change
    void notifyAll();
};

#endif

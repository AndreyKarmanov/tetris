#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "gameObserver.h"

class GameSubject;

// TextObserver is a concrete observer that prints the game state to the terminal
class TextObserver : public GameObserver
{
public:
    TextObserver(GameSubject *game);
    virtual void notify();
    ~TextObserver();
};
#endif

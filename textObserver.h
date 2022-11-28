#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "gameObserver.h"

class GameSubject;

class TextObserver : public GameObserver
{
public:
    TextObserver(GameSubject *game);
    virtual void notify();
    ~TextObserver();
};
#endif

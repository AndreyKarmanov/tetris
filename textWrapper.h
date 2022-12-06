#ifndef TEXTGAMEOBSERVER_H
#define TEXTGAMEOBSERVER_H

#include <vector>
#include "gameObserver.h"

class GameSubject;

class TextWrapper
{
private:
    class TextObserver : public GameObserver
    {
    public:
        TextObserver(GameSubject *game);
        virtual void notify();
        ~TextObserver();
    };

    std::vector<TextObserver *> observers;
    
public:
    TextWrapper(std::vector<GameSubject *> games);
    ~TextWrapper();

    void notifyAll();
};

#endif

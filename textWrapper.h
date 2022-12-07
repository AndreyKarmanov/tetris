#ifndef TEXTGAMEOBSERVER_H
#define TEXTGAMEOBSERVER_H

#include <vector>
#include <sstream>
#include <string>
#include "gameObserver.h"

class GameSubject;

class TextWrapper
{
private:
    class TextObserver : public GameObserver
    {
    public:
        TextObserver(GameSubject *game);
        std::stringstream generateBoard();
        virtual void notify();
        ~TextObserver();
    };

    std::vector<TextObserver *> observers;

    void printLine(std::string curline);
    
public:
    TextWrapper(std::vector<GameSubject *> games);
    ~TextWrapper();

    void notifyAll();
};

#endif

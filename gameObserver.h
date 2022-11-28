#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

class GameSubject;

class GameObserver
{
protected:
  GameSubject *game;
public:
  GameObserver(GameSubject *game);
  virtual void notify() = 0;
  virtual ~GameObserver();
};
#endif

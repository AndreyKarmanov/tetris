#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

class GameSubject;

// GameObserver is an abstract class that represents an observer of a GameSubject
class GameObserver
{
protected:
  // The subject that this observer is observing
  GameSubject *game;

public:
  // Constructor & Destructor
  GameObserver(GameSubject *game);
  virtual ~GameObserver();

  // Notifies the observer that the subject has changed
  virtual void notify() = 0;
};
#endif

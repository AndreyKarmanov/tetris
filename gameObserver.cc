#include "gameObserver.h"
#include "gameSubject.h"

GameObserver::GameObserver(GameSubject *game) : game{game} {}

GameObserver::~GameObserver() {}

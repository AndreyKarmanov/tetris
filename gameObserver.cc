#include "gameObserver.h"
#include "gameSubject.h"

// Constructor
GameObserver::GameObserver(GameSubject *game) : game{game} {}

// Destructor
GameObserver::~GameObserver() {}

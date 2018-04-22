#pragma once
#include <allegro5\allegro5.h>
#include <queue>
#include <vector>
#include <iostream>

#include "eventType.h"
#include "keyboardEvent.h"
#include "timerEvent.h"

#include "gameData.h" //borrar despues

using namespace std;

typedef enum { KEY_PRESSED, SAME_KEY, NOT_SAME_KEY, TIMEOUT100, TIMEOUT900 } keyReadingEvent;
typedef enum { STANDBY, WAIT100, WAIT900 } keyReadingState;


class eventGenerator
{
private:
	queue<eventType*> returnEvent;

	bool quit = false;
public:
	eventGenerator();
	~eventGenerator();

	bool newEvent(void * userData);
	eventType* getEvent(void * userData);
	bool isQuit();

};


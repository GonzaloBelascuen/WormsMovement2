#pragma once
#include "worm.h"
#include "world.h"

struct gameData
{
	ALLEGRO_EVENT_QUEUE *allegro_event_queue;
	ALLEGRO_TIMER *frameTimer;
	ALLEGRO_TIMER *keyboardTimer;

	wormEvent myWormEvent;
	int wormID;
	world * myWorld;
};
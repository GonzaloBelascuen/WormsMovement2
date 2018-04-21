#pragma once

#include "position.h"

#include <allegro5/allegro.h> 

typedef enum { PRESSED_LEFT, HOLDED_LEFT, PRESSED_RIGHT, HOLDED_RIGHT, JUMP, END_OF_ACTION , NO_WORM_EVENT} wormEvent;
typedef enum { WALKING_RIGHT, WALKING_LEFT, STILL_LEFT, STILL_RIGHT, JUMPING_LEFT, JUMPING_RIGHT } worm_state;

class worm
{
private:
	position pos;
	worm_state state;
	ALLEGRO_BITMAP ** walkImgs; //en el futuro esto lo vamos  hacer con listas
	ALLEGRO_BITMAP ** jumpImgs;
	unsigned int tickCount; //se incrementa en los refresh
public:
	worm();
	~worm();

	void init(int _xCoord, int _yCoord, worm_state _state, ALLEGRO_BITMAP ** _walkImgs, ALLEGRO_BITMAP ** _jumpImgs);

	void refresh();
	void event(wormEvent myWormEvent);
};

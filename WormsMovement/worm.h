#pragma once

#include "position.h"
#include "iostream" //FOR DEBUGGING

#include <allegro5/allegro.h> 

using namespace std;

typedef enum { PRESSED_LEFT, HOLDED_LEFT, PRESSED_RIGHT, HOLDED_RIGHT, JUMP, END_OF_ACTION, NO_WORM_EVENT, END_OF_TABLE } wormEvent;
typedef struct _wormState wormState;
typedef enum { JUMPING, FLYING, LANDING } jumpingSubState;

class worm
{
private:
	position pos;
	wormState * state;
	ALLEGRO_BITMAP ** walkImgs; //en el futuro esto lo vamos  hacer con listas
	ALLEGRO_BITMAP ** jumpImgs;
	unsigned int tickCount; //se incrementa en los refresh
	//unsigned int subTick;
	jumpingSubState subState = JUMPING;
public:
	worm(int _xCoord, int _yCoord, wormState * _state, ALLEGRO_BITMAP ** _walkImgs, ALLEGRO_BITMAP ** _jumpImgs);
	~worm();

	void refresh();
	void event(wormEvent myWormEvent);
	void resetTickCount();
};

struct _wormState
{
	wormEvent ev;
	wormState * nextState;
	void(*action)(worm *);
};

/*STATE DECLARATIONS*/
wormState WALKING_RIGHT[];
wormState WALKING_LEFT[];
wormState STILL_LEFT[];
wormState STILL_RIGHT[];
wormState JUMPING_LEFT[];
wormState JUMPING_RIGHT[];

/*STATE TRANSITION ACTION DECLARATION*/
void noAction(worm * _worm);
void resetWormTickCount(worm * _worm);

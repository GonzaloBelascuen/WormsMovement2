#include "worm.h"
#include <iostream>

void worm::init(int _xCoord, int _yCoord, wormState * _state, ALLEGRO_BITMAP ** _walkImgs, ALLEGRO_BITMAP ** _jumpImgs)
{
	pos.setX(_xCoord);
	pos.setY(_yCoord);

	state = _state;

	walkImgs = _walkImgs;
	jumpImgs = _jumpImgs;
}

void worm::refresh()
{
	int walkSequence[50] = { 1,1,1,1, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 1 };

	if (state == WALKING_LEFT)
	{
		if (tickCount == 19 || tickCount == 34 || tickCount == 49)
		{
			pos.setX(pos.getX() - 9);
		}

		al_draw_bitmap(walkImgs[walkSequence[tickCount]], pos.getX(), pos.getY(), 0);
		tickCount++;
		if (tickCount == 50)
		{
			this->event(END_OF_ACTION);
		}
	}
	else if (state == STILL_LEFT)
	{
		al_draw_bitmap(walkImgs[1], pos.getX(), pos.getY(), 0);
	}
	else if (state == WALKING_RIGHT)
	{
		if (tickCount == 19 || tickCount == 34 || tickCount == 49)
		{
			pos.setX(pos.getX() + 9);
		}

		al_draw_bitmap(walkImgs[walkSequence[tickCount]], pos.getX(), pos.getY(), ALLEGRO_FLIP_HORIZONTAL);
		tickCount++;
		if (tickCount == 50)
		{
			this->event(END_OF_ACTION);
		}
	}
	else if (state == STILL_RIGHT)
	{
		al_draw_bitmap(walkImgs[1], pos.getX(), pos.getY(), ALLEGRO_FLIP_HORIZONTAL);
	}
}

void worm::event(wormEvent myWormEvent)
{
	int i = 0;

	for (i = 0; (state[i].ev != END_OF_TABLE) && (state[i].ev != myWormEvent); i++) {}

	state[i].action(this);
	state = state[i].nextState;
}

void worm::resetTickCount()
{
	tickCount = 0;
}


worm::worm()
{
	pos.setX(0);
	pos.setY(0);

	state = STILL_LEFT;
}

worm::~worm()
{
}


/*STATE TRANSITION DEFINITION*/
wormState WALKING_LEFT[] =
{
	{ END_OF_ACTION , STILL_LEFT , noAction },
{ END_OF_TABLE, WALKING_LEFT , noAction }
};
wormState WALKING_RIGHT[] =
{
	{ END_OF_ACTION , STILL_RIGHT , noAction },
{ END_OF_TABLE, WALKING_RIGHT , noAction }
};

wormState STILL_LEFT[] =
{
	{ HOLDED_LEFT , WALKING_LEFT , resetWormTickCount },
	{ JUMP , JUMPING_LEFT , resetWormTickCount },
	{ PRESSED_RIGHT , STILL_RIGHT , noAction },
{ END_OF_TABLE, STILL_LEFT , noAction }
};

wormState STILL_RIGHT[] =
{
	{ HOLDED_RIGHT , WALKING_RIGHT , resetWormTickCount },
	{ JUMP , JUMPING_RIGHT , resetWormTickCount },
	{ PRESSED_LEFT , STILL_LEFT , noAction },
{ END_OF_TABLE, STILL_RIGHT , noAction }
};

wormState JUMPING_LEFT[] =
{
	{ END_OF_ACTION , STILL_LEFT , noAction },
{ END_OF_TABLE, JUMPING_LEFT , noAction }
};

wormState JUMPING_RIGHT[] =
{
	{ END_OF_ACTION , STILL_RIGHT , noAction },
{ END_OF_TABLE, JUMPING_RIGHT , noAction }
};

/*STATE TRANSITION ACTIONS DEFINITION*/
void noAction(worm * _worm)
{

}

void resetWormTickCount(worm * _worm)
{
	_worm->resetTickCount();
}
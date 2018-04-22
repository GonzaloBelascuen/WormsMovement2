#include "worm.h"
#include <iostream>

void worm::init(int _xCoord, int _yCoord, wormState * _state, ALLEGRO_BITMAP ** _walkImgs, ALLEGRO_BITMAP ** _jumpImgs)
{
	pos.x = _xCoord;
	pos.y = _yCoord;

	state = _state;

	walkImgs = _walkImgs;
	jumpImgs = _jumpImgs;
}

void worm::refresh()
{
	int walkSequence[45] = { 5,6,7,8,9,10,11,12,13,14,15, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 1,2,3,4 };
	
	int jumpSequence[4] = { 1,2,3,4};
	int landingSequence[9] = {5,6,7,8,9,10,9,8,7};

	if (state == WALKING_LEFT)
	{
		if (tickCount == 11 || tickCount == 26 || tickCount == 41)
		{
			pos.x -= 9;
		}

		al_draw_bitmap(walkImgs[walkSequence[tickCount]], pos.x, pos.y, 0);
		tickCount++;
		if (tickCount == 45)
		{
			this->event(END_OF_ACTION);
		}
	}
	else if (state == JUMPING_LEFT)
	{
		switch (subState)
		{
		case JUMPING:
			al_draw_bitmap(jumpImgs[jumpSequence[tickCount]], pos.x, pos.y, 0);
			if (tickCount == 3)
			{
				subState = FLYING;
				tickCount = 0;
			}
			break;
		case FLYING:
			pos.y = pos.y - 3.89711 + 0.24*tickCount;
			pos.x -= 2.25;
			if (pos.y > 616)
			{
				pos.y = 616;
				subState = LANDING;
				tickCount = 0;
			}
			al_draw_bitmap(jumpImgs[4], pos.x, pos.y, 0);
			break;
		case LANDING:
			al_draw_bitmap(jumpImgs[landingSequence[tickCount]], pos.x, pos.y, 0);
			if (tickCount == 8)
			{
				this->event(END_OF_ACTION);
				subState = JUMPING;
				tickCount = 0;
			}
			break;
		}		
		tickCount++;
	}
	else if (state == STILL_LEFT)
	{
		al_draw_bitmap(walkImgs[4], pos.x, pos.y, 0);
	}
	else if (state == WALKING_RIGHT)
	{
		if (tickCount == 11 || tickCount == 26 || tickCount == 41)
		{
			pos.x += 9;
		}

		al_draw_bitmap(walkImgs[walkSequence[tickCount]], pos.x, pos.y, ALLEGRO_FLIP_HORIZONTAL);
		tickCount++;
		if (tickCount == 45)
		{
			this->event(END_OF_ACTION);
		}
	}
	else if (state == JUMPING_RIGHT)
	{
		
	}
	else if (state == STILL_RIGHT)
	{
		al_draw_bitmap(walkImgs[4], pos.x, pos.y, ALLEGRO_FLIP_HORIZONTAL);
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
	pos.x = 0;
	pos.y = 0;

	state = STILL_LEFT;
}

worm::~worm()
{
}


/*STATE TRANSITION DEFINITION*/
wormState WALKING_LEFT[] =
{
	{ END_OF_ACTION , STILL_LEFT , resetWormTickCount },
{ END_OF_TABLE, WALKING_LEFT , noAction }
};
wormState WALKING_RIGHT[] =
{
	{ END_OF_ACTION , STILL_RIGHT , resetWormTickCount },
{ END_OF_TABLE, WALKING_RIGHT , noAction }
};

wormState STILL_LEFT[] =
{
	{ HOLDED_LEFT , WALKING_LEFT , resetWormTickCount },
	{ JUMP , JUMPING_LEFT , resetWormTickCount },
	{ PRESSED_RIGHT , STILL_RIGHT , noAction },
	{ HOLDED_RIGHT , STILL_RIGHT , noAction },
{ END_OF_TABLE, STILL_LEFT , noAction }
};

wormState STILL_RIGHT[] =
{
	{ HOLDED_RIGHT , WALKING_RIGHT , resetWormTickCount },
	{ JUMP , JUMPING_RIGHT , resetWormTickCount },
	{ PRESSED_LEFT , STILL_LEFT , noAction },
	{ HOLDED_LEFT , STILL_LEFT , noAction },
{ END_OF_TABLE, STILL_RIGHT , noAction }
};

wormState JUMPING_LEFT[] =
{
	{ END_OF_ACTION , STILL_LEFT , resetWormTickCount },
{ END_OF_TABLE, JUMPING_LEFT , noAction }
};

wormState JUMPING_RIGHT[] =
{
	{ END_OF_ACTION , STILL_RIGHT , resetWormTickCount },
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
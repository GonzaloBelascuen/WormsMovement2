#include "worm.h"
#include <iostream>


void worm::init(int _xCoord, int _yCoord, worm_state _state, ALLEGRO_BITMAP ** _walkImgs, ALLEGRO_BITMAP ** _jumpImgs)
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

	switch (state)
	{
	case WALKING_LEFT:

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
		break;
	case STILL_LEFT:
		al_draw_bitmap(walkImgs[1], pos.getX(), pos.getY(), 0);
		break;
	case WALKING_RIGHT:

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
		break;
	case STILL_RIGHT:
		al_draw_bitmap(walkImgs[1], pos.getX(), pos.getY(), ALLEGRO_FLIP_HORIZONTAL);
		break;
	}

}

void worm::event(wormEvent myWormEvent)
{
	switch (state)
	{
	case WALKING_LEFT:
		if (myWormEvent == END_OF_ACTION)
		{
			tickCount = 0;
			state = STILL_LEFT;
		}
		break;
	case WALKING_RIGHT:
		if (myWormEvent == END_OF_ACTION)
		{
			tickCount = 0;
			state = STILL_RIGHT;
		}
		break;
	case STILL_LEFT:
		if (myWormEvent == HOLDED_LEFT)
		{
			tickCount = 0;
			state = WALKING_LEFT;
		}
		else if (myWormEvent == PRESSED_RIGHT)
		{
			state = STILL_RIGHT;
		}
		else if (myWormEvent == JUMP)
		{
			state = JUMPING_LEFT;
		}
		break;
	case STILL_RIGHT:
		if (myWormEvent == HOLDED_RIGHT)
		{
			tickCount = 0;
			state = WALKING_RIGHT;
		}
		else if (myWormEvent == PRESSED_LEFT)
		{
			state = STILL_LEFT;
		}
		else if (myWormEvent == JUMP)
		{
			state = JUMPING_RIGHT;
		}
		break;
	case JUMPING_LEFT:
		if (myWormEvent == END_OF_ACTION)
		{
			tickCount = 0;
			state = STILL_LEFT;
		}
		break;
	case JUMPING_RIGHT:
		if (myWormEvent == END_OF_ACTION)
		{
			tickCount = 0;
			state = STILL_RIGHT;
		}
		break;
	}
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

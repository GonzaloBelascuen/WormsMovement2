#include "keyHandler.h"

keyHandler::~keyHandler()
{
}

void keyHandler::cycle(keyReadingState event)
{
	switch (state)
	{
	case STANDBY:
		if (event == KEY_PRESSED)
		{
			tickCount = 0;
			state = WAIT100;
		}
		break;
	case WAIT100:
		if (event == KEY_PRESSED)
		{
			tickCount = 0;
			state = WAIT100;
		}
		break;
	}

}

void keyHandler::tick()
{
	tickCount++;
}

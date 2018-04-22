#pragma once
#include "eventType.h"

class timerEvent: public eventType
{
public:
	eventID getEventID() { return TIMER_EVENT; }

	timerEvent();
	~timerEvent();
};


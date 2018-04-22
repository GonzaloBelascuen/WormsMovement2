#pragma once
typedef enum { KEYBOARD_EVENT, TIMER_EVENT, QUIT } eventID;

class eventType
{
public:
	virtual eventID getEventID() = 0;
};


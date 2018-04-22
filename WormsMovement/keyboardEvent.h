#pragma once
#include "eventType.h"

typedef enum {PRESSED, HELD} keyAction; 

class keyboardEvent : public eventType
{
public:
	eventID getEventID() { return KEYBOARD_EVENT; }

	keyAction KeyAction;
	int key;

	keyboardEvent(keyAction _KeyAction, int _key);
	~keyboardEvent();

};


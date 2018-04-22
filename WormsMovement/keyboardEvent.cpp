#include "keyboardEvent.h"


keyboardEvent::keyboardEvent(keyAction _KeyAction, int _key)
{
	KeyAction = _KeyAction;
	key = _key;
}

keyboardEvent::~keyboardEvent()
{
}

#pragma once
typedef enum { KEY_PRESSED, SAME_KEY, NOT_SAME_KEY, TIMEOUT100, TIMEOUT900 } keyReadingEvent;
typedef enum { STANDBY, WAIT100, WAIT900 } keyReadingState;



class keyHandler
{
private:
	keyReadingState state;
	int tickCount;
	
public:
	keyHandler() { state = STANDBY; tickCount = 0; }
	~keyHandler();
	void cycle(keyReadingState event);
	void tick();
};


#include "eventGenerator.h"



eventGenerator::eventGenerator()
{
}


eventGenerator::~eventGenerator()
{
}

bool eventGenerator::newEvent(void * userData)
{
	gameData *eventData = (gameData*)userData;

	ALLEGRO_EVENT allegro_event;

	static keyReadingState state = STANDBY;
	static int keyPressed = 0;
	static int tickCount = 0;

	struct keyTime
	{
		int key;
		int time;
	};
	static vector<keyTime> keyTimeVector;

	if (al_get_next_event(eventData->allegro_event_queue, &allegro_event)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
	{
		if (allegro_event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			keyPressed = allegro_event.keyboard.keycode;

			keyTimeVector.push_back({ keyPressed,0 });

			returnEvent.push(new keyboardEvent(PRESSED, keyPressed));
		}

		if (allegro_event.type == ALLEGRO_EVENT_TIMER)
		{
			if (allegro_event.timer.source == eventData->keyboardTimer)
			{
				ALLEGRO_KEYBOARD_STATE keyState;
				al_get_keyboard_state(&keyState);

				auto it = keyTimeVector.begin();
				while (it != keyTimeVector.end())
				{
					if (al_key_down(&keyState, it->key))
					{
						it->time++;
						//cout << "key: " << it->key << " time: " << it->time << endl; DEBUG
						if (it->time == 5)
						{
							returnEvent.push(new keyboardEvent(HELD, it->key));
							it->time = 0;
						}
						it++;
					}
					else
					{
						it = keyTimeVector.erase(it);
					}
				}
				
			}

			if (allegro_event.timer.source == eventData->frameTimer)
			{
				returnEvent.push(new timerEvent());
			}
		}

		if (allegro_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			quit = true;
		}
	}

	return !returnEvent.empty();
}

eventType* eventGenerator::getEvent(void * userData)
{
	eventType* temp = returnEvent.front();
	returnEvent.pop();
	return temp;
}

bool eventGenerator::isQuit()
{
	return quit;
}

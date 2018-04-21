
#include <iostream>

#include "worm.h"
#include "world.h"
//#include "keyHandler.h"

#include <stdio.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5\allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5\allegro_image.h>

typedef enum { WORM_EVENT , REFRESH_SCREEN, NO_EVENT, QUIT } gameEvent;

struct gameData
{
	ALLEGRO_EVENT_QUEUE *allegro_event_queue;
	ALLEGRO_TIMER *frameTimer;
	ALLEGRO_TIMER *keyboardTimer;

	wormEvent myWormEvent;
	int wormID;
	world * myWorld;
};

gameEvent getEvent(void *userData);
void dispatch(gameEvent event, void *userData);

#define FPS			50.0
#define keyboardFPS	50.0
#define D_WIDTH		1920
#define D_HEIGHT	696

int main(void)
{
	// INITIALIZATION
	int hola = 4;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *allegro_event_queue;
	ALLEGRO_TIMER *frameTimer = NULL;
	ALLEGRO_TIMER *keyboardTimer = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}
	display = al_create_display(D_WIDTH, D_HEIGHT);
	if (!display) {
		al_shutdown_primitives_addon();
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	if (!al_init_image_addon()) { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
		al_shutdown_primitives_addon();
		al_destroy_display(display);
		fprintf(stderr, "failed to initialize image addon !\n");
		return -1;
	}
	frameTimer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
	if (!frameTimer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	keyboardTimer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
	if (!keyboardTimer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
	
	allegro_event_queue = al_create_event_queue();
	if (!allegro_event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_timer(frameTimer);
		return -1;
	}

	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(allegro_event_queue, al_get_keyboard_event_source());
	al_register_event_source(allegro_event_queue, al_get_display_event_source(display));
	al_register_event_source(allegro_event_queue, al_get_mouse_event_source());
	al_register_event_source(allegro_event_queue, al_get_timer_event_source(frameTimer));
	al_register_event_source(allegro_event_queue, al_get_timer_event_source(keyboardTimer));

	//INITIALIZE GAME DATA
	gameData myGameData;
	myGameData.allegro_event_queue = allegro_event_queue;
	myGameData.frameTimer = frameTimer;
	myGameData.keyboardTimer = keyboardTimer;
	myGameData.myWorld = new world();
	myGameData.myWormEvent = NO_WORM_EVENT;

	//RUN LOOP
	gameEvent event = NO_EVENT;

	al_start_timer(frameTimer);
	al_start_timer(keyboardTimer);
	while (event != QUIT) {

		event = getEvent(&myGameData);

		if (event != NO_EVENT)
		{
			dispatch(event, &myGameData);
		}
	}

	//Memory Cleaning
	delete myGameData.myWorld;
	al_destroy_display(display);
	al_destroy_event_queue(allegro_event_queue);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();
	return 0;
}

typedef enum { KEY_PRESSED, SAME_KEY, NOT_SAME_KEY, TIMEOUT100, TIMEOUT900 } keyReadingEvent;
typedef enum { STANDBY, WAIT100, WAIT900 } keyReadingState;

gameEvent getEvent(void * userData)
{
	gameData *eventData = (gameData*) userData;

	ALLEGRO_EVENT allegro_event;

	static keyReadingState state = STANDBY;
	static int keyPressed = 0;
	static int tickCount = 0;

	if (al_get_next_event(eventData->allegro_event_queue, &allegro_event)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
	{
		if (allegro_event.type == ALLEGRO_EVENT_TIMER)
		{
			if (allegro_event.timer.source == eventData->keyboardTimer)
			{
				ALLEGRO_KEYBOARD_STATE keyState;
				al_get_keyboard_state(&keyState);
				
				switch (state)
				{
				case STANDBY:
					if (!al_key_down(&keyState, keyPressed))
					{
						if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
							keyPressed = ALLEGRO_KEY_LEFT;
						}
						else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
							keyPressed = ALLEGRO_KEY_RIGHT;
						}
						else
						{
							keyPressed = 0;
						}
					}

					if (keyPressed)
					{
						switch (keyPressed)
						{
						case ALLEGRO_KEY_LEFT: eventData->myWormEvent = PRESSED_LEFT; break;
						case ALLEGRO_KEY_RIGHT: eventData->myWormEvent = PRESSED_RIGHT; break;
						}
						eventData->wormID = 0;
						state = WAIT100;
						return WORM_EVENT;
					}
					break;
				case WAIT100:
					if (tickCount <= 5) {
						tickCount++;
						if (!al_key_down(&keyState, keyPressed)) {
							state = STANDBY;
							tickCount = 0;
						}
					}
					else
					{
						if (al_key_down(&keyState, keyPressed))
						{
							state = WAIT900;
							eventData->wormID = 0;
							switch (keyPressed)
							{
							case ALLEGRO_KEY_LEFT: eventData->myWormEvent = HOLDED_LEFT; break;
							case ALLEGRO_KEY_RIGHT: eventData->myWormEvent = HOLDED_RIGHT; break;
							}
							return WORM_EVENT;
						}
						else
						{
							state = STANDBY;
							tickCount = 0;
						}
					}
					break;
				case WAIT900:
					if (tickCount <= 50) { tickCount++; }
					else
					{
						state = STANDBY;
						tickCount = 0;
					}
					break;
				}
				
			}
			if (allegro_event.timer.source == eventData->frameTimer)
			{
				return REFRESH_SCREEN;
			}
		}

		if (allegro_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			return QUIT;
		}
	}

	return NO_EVENT;
}

void dispatch(gameEvent event, void * userData)
{
	gameData *eventData = (gameData*)userData;

	if (event == REFRESH_SCREEN)
	{
		eventData->myWorld->refresh(eventData);
		eventData->myWorld->worms[0].refresh();
		eventData->myWorld->worms[1].refresh();
		al_flip_display();
	}

	if (event == WORM_EVENT)
	{
		eventData->myWorld->worms[eventData->wormID].event(eventData->myWormEvent);
	}
}

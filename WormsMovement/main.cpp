
#include <iostream>

#include "worm.h"
#include "world.h"
#include "eventGenerator.h"
#include "gameData.h"

#include <stdio.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5\allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5\allegro_image.h>


void dispatch(eventType* event, world& myWorld);

#define FPS			50.0
#define keyboardFPS	50.0
#define D_WIDTH		1920
#define D_HEIGHT	696

int main(void)
{
	// ALLEGRO INITIALIZATION
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

	world myWorld;

	//RUN LOOP
	eventGenerator evGen;

	al_start_timer(frameTimer);
	al_start_timer(keyboardTimer);
	bool quit = false;
	while (!quit) {
		if (evGen.newEvent(&myGameData))
		{
			if (!evGen.isQuit())
			{
				dispatch(evGen.getEvent(&myGameData), myWorld);
			}
			else
				quit = true;
		}
	}

	//Memory Cleaning
	al_destroy_display(display);
	al_destroy_event_queue(allegro_event_queue);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();
	return 0;
}


void dispatch(eventType* event, world& myWorld)
{

	switch (event->getEventID())
	{
	case TIMER_EVENT:
		myWorld.refresh();
		myWorld.worms[0].refresh();
		myWorld.worms[1].refresh();
		al_flip_display();
		break;
	case KEYBOARD_EVENT:

		int wormID;
		wormEvent myWormEvent;
		keyboardEvent * KeyEvent = ((keyboardEvent *)event);

		bool validKeyPressed = false;

		switch (KeyEvent->key)
		{
		case ALLEGRO_KEY_LEFT:
			wormID = 0;
			validKeyPressed = true;
			if (KeyEvent->KeyAction == PRESSED)
				myWormEvent = PRESSED_LEFT;
			else if (KeyEvent->KeyAction == HELD)
				myWormEvent = HOLDED_LEFT;
			break;

		case ALLEGRO_KEY_RIGHT:
			wormID = 0;
			validKeyPressed = true;
			if (KeyEvent->KeyAction == PRESSED)
				myWormEvent = PRESSED_RIGHT;
			else if (KeyEvent->KeyAction == HELD)
				myWormEvent = HOLDED_RIGHT;
			break;
		case ALLEGRO_KEY_UP:
			wormID = 0;
			validKeyPressed = true;
			if (KeyEvent->KeyAction == HELD)
				myWormEvent = JUMP;
			break;

		case ALLEGRO_KEY_A:
			wormID = 1;
			validKeyPressed = true;
			if (KeyEvent->KeyAction == PRESSED)
				myWormEvent = PRESSED_LEFT;
			else if (KeyEvent->KeyAction == HELD)
				myWormEvent = HOLDED_LEFT;
			break;

		case ALLEGRO_KEY_D:
			wormID = 1;
			validKeyPressed = true;
			if (KeyEvent->KeyAction == PRESSED)
				myWormEvent = PRESSED_RIGHT;
			else if (KeyEvent->KeyAction == HELD)
				myWormEvent = HOLDED_RIGHT;
			break;

		case ALLEGRO_KEY_W:
			wormID = 1;
			validKeyPressed = true;
			if (KeyEvent->KeyAction == HELD)
				myWormEvent = JUMP;
			break;
		}

		if (validKeyPressed == true)
		{
			//cout << "worm ID: " << wormID << " wormEvent: " << myWormEvent << endl; DEBUG
			myWorld.worms[wormID].event(myWormEvent);
		}
	
	}

	/*IMPORTANT DELETE EVENT*/
	delete event;
}

#pragma once

#include "worm.h"
#include "world.h"

#include <stdio.h>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5\allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5\allegro_image.h>

typedef enum { KEY_DOWN, KEY_UP, NO_EVENT, QUIT } WormsEvent;

typedef enum { W_KEY, A_KEY, S_KEY, D_KEY, UP_ARROW_KEY, LEFT_ARROW_KEY, DOWN_ARROW_KEY, RIGHT_ARROW_KEY } WormsKeys;

struct gameData
{
	ALLEGRO_EVENT_QUEUE *allegro_event_queue;
	WormsKeys keyPressed;
	world * myWorld;
	ALLEGRO_BITMAP ** walkImgs; //en el futuro esto lo vamos  hacer con listas
	ALLEGRO_BITMAP ** jumpImgs;
};
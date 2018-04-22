#pragma once
#include "observer.h"

#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>

class drawWorld: public observer
{
public:
	void update(void * data);

	drawWorld();
private:
	void drawWorm();

	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * scenario;
	ALLEGRO_BITMAP ** walkImgs;
	ALLEGRO_BITMAP ** jumpImgs;

};


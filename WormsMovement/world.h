#pragma once
#include "worm.h"



class world
{
private:
	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * scenario;
	ALLEGRO_BITMAP ** walkImgs;
	ALLEGRO_BITMAP ** jumpImgs;
	
	unsigned int wormNumber;
public:
	worm * worms;
	void refresh(void * userData);
	world();
	~world();
};


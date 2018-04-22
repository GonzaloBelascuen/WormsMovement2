#pragma once
#include "worm.h"
#include <vector>
#include "observer.h"

using namespace std;

class world: public observer
{
public:
	void refresh();
	world();
	~world();

	vector<worm> worms;

	void spawnWorm();

	void addObserver(observer* obs);

private:
	vector<observer*> obsVector;

	void update(void * data);

	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * scenario;
	ALLEGRO_BITMAP ** walkImgs;
	ALLEGRO_BITMAP ** jumpImgs;
	

	unsigned int wormNumber;
};


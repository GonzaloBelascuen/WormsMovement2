#include "world.h"
#include <iostream>
#include <string>
#include <vector>



using namespace std;

void world::refresh()
{
	al_draw_bitmap(background, 0, 0, 0);//flags(normalmente en cero, ver doc. para rotar etc)
	al_draw_bitmap(scenario, 0, 0, 0);//flags(normalmente en cero, ver doc. para rotar etc)
}

world::world()
{
	background = al_load_bitmap("WormsImages/background.png"); //despues se puee meter todo esto en una funcion de init en dispatch
	if (!background) {
		fprintf(stderr, "failed to load background !\n");
	}

	scenario = al_load_bitmap("WormsImages/Scenario.png"); //despues se puee meter todo esto en una funcion de init en dispatch
	if (!scenario) {
		fprintf(stderr, "failed to load Scenario !\n");
	}

	std::string strnum = std::to_string(1);
	std::string extension(".png");

	walkImgs = (ALLEGRO_BITMAP **)malloc(sizeof(ALLEGRO_BITMAP *)*16);

	std::string dirWalk("WormsImages/wwalking/wwalk-F");
	std::string fullDir;

	fullDir = dirWalk + strnum + extension;
	

	for (int i = 1; i != 16; i++)
	{
		strnum = std::to_string(i);
		fullDir = dirWalk + strnum + extension;
		//std::cout << fullDir << std::endl; DEBUG
		walkImgs[i] = al_load_bitmap(fullDir.c_str()); //despues se puee meter todo esto en una funcion de init en dispatch
		if (!walkImgs[i]) {
			fprintf(stderr, "failed to load worm walk image !\n");
		}
	}

	jumpImgs = (ALLEGRO_BITMAP **)malloc(sizeof(ALLEGRO_BITMAP *) * 11);

	std::string dirJump("WormsImages/wjump/wjump-F");

	fullDir = dirJump + strnum + extension;

	for (int i = 1; i != 11; i++)
	{
		strnum = std::to_string(i);
		fullDir = dirJump + strnum + extension;
		//std::cout << fullDir << std::endl; DEBUG
		jumpImgs[i] = al_load_bitmap(fullDir.c_str()); //despues se puee meter todo esto en una funcion de init en dispatch
		if (!jumpImgs[i]) {
			fprintf(stderr, "failed to load worm jump image !\n");
		}
	}

	worms.push_back(worm(1000, 616, STILL_LEFT, walkImgs, jumpImgs));
	worms.push_back(worm(900, 616, STILL_LEFT, walkImgs, jumpImgs));
}

world::~world()
{
	std::string strnum = std::to_string(1);
	std::string extension(".png");

	std::string dirWalk("WormsImages/wwalking/wwalk-F");
	std::string fullDir;

	for (int i = 1; i != 16; i++)
	{
		strnum = std::to_string(i);
		fullDir = dirWalk + strnum + extension;
		al_destroy_bitmap(walkImgs[i]);
	}

	std::string dirJump("WormsImages/wjump/wjump-F");

	for (int i = 1; i != 11; i++)
	{
		strnum = std::to_string(i);
		fullDir = dirJump + strnum + extension;
		al_destroy_bitmap(jumpImgs[i]);
	}
	
	al_destroy_bitmap(background);
	al_destroy_bitmap(scenario);
	
	free(walkImgs);
	free(jumpImgs);
}

void world::addObserver(observer * obs)
{
	obsVector.push_back(obs);
}

void world::update(void * data)
{
	for (observer* obs : obsVector)
		(*obs).update(this);
}


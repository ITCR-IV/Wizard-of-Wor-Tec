#ifndef WALL_H
#define WALL_H

#include <SDL.h>	//SDL version 2.0
#include <stdbool.h>

typedef struct wall_s {
	int x,y;
	int w,h;
} Wall;

extern Wall* BaseLvlPtr;
static Wall* LabyrinthPtr;



void init_labyrinth(int lvl); 

void terminate_labyrinth();

void reset_labyrinth(int lvl);

void draw_walls(SDL_Surface *screen, int lvl);

bool check_collision_walls(int lvl, SDL_Rect rect);
#endif

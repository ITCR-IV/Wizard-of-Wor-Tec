#ifndef WALL_H
#define WALL_H

typedef struct wall_s {
	int x,y;
	int w,h;
} Wall;

static Wall* BaseLvlPtr;
static Wall* LabyrinthPtr;



void init_labyrinth(int lvl); 

void terminate_labyrinth();

void reset_labyrinth(int lvl);

void draw_walls(); 

#endif

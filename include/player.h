#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "directions.h"

enum PlayerStates{INITIAL, MOVING, STATIC};

typedef struct player_s {
	int x, y;
	enum Direction orientation;
	enum PlayerStates state;
	int cooldown;
	int lives;
} Player;

static Player *PlayerPtr;

void init_player();

void terminate_player();

void reset_player();

void draw_player(SDL_Surface *screen, SDL_Surface *sprite);

void move_player(enum Direction d, int lvl);

#endif

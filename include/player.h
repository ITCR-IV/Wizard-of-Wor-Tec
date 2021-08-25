#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "SDL.h"
#include "directions.h"

enum PlayerStates{INITIAL, MOVING, STATIC};

typedef struct player_s {
	int x, y;
	enum Direction orientation;
	enum PlayerStates state;
	int cooldown;
	int lives;
	int activeBullets;
} Player;

static Player *PlayerPtr;

void init_player();

void terminate_player();

void reset_player();

void hard_reset_player();

void draw_player(SDL_Surface *screen, SDL_Surface *sprite);

void draw_lives(SDL_Surface *screen, SDL_Surface *sprite);

void move_player(enum Direction d, int lvl);

bool check_los(int x, int y, int lvl);

typedef struct bullet_s {
	int x, y;
	enum Direction orientation;
	bool active;
} Bullet;

static Bullet *BulletPtr;
static int bulletLength = 18;
static int bulletWidth = 5;
 
void player_shoot();

void draw_bullets(SDL_Surface *screen);

void move_bullets(int lvl);

bool check_collision_bullets(SDL_Rect rect);
#endif

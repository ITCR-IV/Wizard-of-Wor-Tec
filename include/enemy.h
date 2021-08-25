#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include "SDL.h"
#include "directions.h"

enum EnemyTypes{GREEN = 0, RED, PURPLE, BLUE};
typedef struct enemy_s {
	int x, y;
	int type; //goes from 0 to 4
	enum Direction orientation;
	bool visible;
	int visibilityTimer;
	bool active;
} Enemy;

static Enemy *EnemyPtr;

static int initialEnemies;
static int enemiesSpawned;
static int spawnTimer;

void init_enemies();

void terminate_enemies();

void reset_enemies();

void spawn_enemy();

void draw_enemies(SDL_Surface *screen, SDL_Surface *spriteSheet);

void draw_radar(SDL_Surface *screen);

void move_enemies(int lvl);

#endif

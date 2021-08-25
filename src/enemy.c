#include <time.h>
#include <stdlib.h>

#include "enemy.h"

#include "SDL_helpers.h"
#include "player.h"
#include "wall.h"

// generate random num in range, bounds are inclusive
int rrand(int lower,  int upper){
	return (rand() %(upper - lower + 1)) + lower;
}

void init_enemies(){
	EnemyPtr = malloc(9*sizeof(Enemy));
	for(int i = 0; i < 9; i++){
		EnemyPtr[i].x = EnemyPtr[i].y = 0;
		EnemyPtr[i].orientation = NOWHERE;
		EnemyPtr[i].visible = true;
		EnemyPtr[i].active = false;
		EnemyPtr[i].visibilityTimer = 0;
	}
	srand(time(0));
	enemiesSpawned = 0;
	initialEnemies = rrand(2,5);
	for( int i = 0; i < initialEnemies; i++ ){
		spawnTimer=0;
		spawn_enemy();
	}
}

void reset_enemies(){
	terminate_enemies();
	init_enemies();
}

void terminate_enemies(){
	free(EnemyPtr);
}

void spawn_enemy(){
	if(enemiesSpawned >=9 )
		return;
	if(spawnTimer > 0){
		spawnTimer--;
		return;
	}

	enum EnemyTypes t;
	if(enemiesSpawned < initialEnemies)
		t = GREEN;
	else
		t = rrand(RED, BLUE);
	
	int randx = rrand(2*72+4, 12*72+4);
	int randy = rrand(1*72+4, 6*72+4);
	EnemyPtr[enemiesSpawned].x = randx-randx%72+4;
	EnemyPtr[enemiesSpawned].y = randy-randy%72+4;
	EnemyPtr[enemiesSpawned].orientation = rrand(UP, LEFT);
	EnemyPtr[enemiesSpawned].type = t;
	EnemyPtr[enemiesSpawned].visible = true;
	EnemyPtr[enemiesSpawned].visibilityTimer = 180;
	EnemyPtr[enemiesSpawned].active = true;
	spawnTimer = rrand(90,500);
	enemiesSpawned++;
}

void draw_enemies(SDL_Surface *screen, SDL_Surface *spriteSheet){
	SDL_Rect e;
	SDL_Rect dest;

	//iterate through enemies array
	for(int i = 0; i<enemiesSpawned; i++){
		if(!EnemyPtr[i].active || !EnemyPtr[i].visible)
			continue;

		dest.x = EnemyPtr[i].x;
		dest.y = EnemyPtr[i].y;
		dest.w = spriteSheet->w/4;
		dest.h = spriteSheet->h/4;

		e.x = EnemyPtr[i].orientation*spriteSheet->w/4;
		e.y = EnemyPtr[i].type*spriteSheet->h/4;
		e.w = spriteSheet->w/4;
		e.h = spriteSheet->h/4;

		SDL_BlitSurface(spriteSheet, &e, screen, &dest);
	}
}

void draw_radar(SDL_Surface *screen){
	SDL_Rect e;

	for(int i = 0; i < enemiesSpawned; i++){
		if(!EnemyPtr[i].active)
			continue;
		if(EnemyPtr[i].x < 2*72+4 || EnemyPtr[i].x > 12*72+4)
			continue;

		e.x = 430+((EnemyPtr[i].x-4)/72-2)*20;
		e.y = 539+((EnemyPtr[i].y-4)/72-1)*20;
		e.w = 20;
		e.h = 20;

		int r;
		switch (EnemyPtr[i].type){
			case GREEN:
				r = SDL_FillRect(screen , &e, SDL_MapRGB(screen->format, 21, 64, 0));
				break;
			case RED:
				r = SDL_FillRect(screen , &e, SDL_MapRGB(screen->format, 114, 0, 0));
				break;
			case PURPLE:
				r = SDL_FillRect(screen , &e, SDL_MapRGB(screen->format, 64, 0, 114));
				break;
			case BLUE:
				r = SDL_FillRect(screen , &e, SDL_MapRGB(screen->format, 0, 76, 94));
				break;
		}

		if (r !=0){
			printf("fill rectangle failed in func draw_bullets in bullet #%d", i);
		}
	}
}

void move_enemies(int lvl){
	for(int i = 0; i < enemiesSpawned; i++){
		if(!EnemyPtr[i].active)
			continue;
		
		// invis timer and stuff
		if(EnemyPtr[i].type > GREEN){
			if(EnemyPtr[i].visible){
				if(EnemyPtr[i].visibilityTimer <= 0){
					EnemyPtr[i].visible = false;
				}else{
					EnemyPtr[i].visibilityTimer--;
				}
			}
			//check Line of Sight with the player
			if(check_los(EnemyPtr[i].x,EnemyPtr[i].y,lvl)){
				EnemyPtr[i].visible = true; // if in line of sight reset the enemy to be visible
				// countdown timer
				EnemyPtr[i].visibilityTimer = 150;
			}
		}
		
		//now that visibility is taken care for, do actual movement
		int speed = (4 + pow(2,EnemyPtr[i].type))/2; // speed must be a factor of 72 (2^3*3^2)

		//random chance to turn when "snapping" to grid
		if(EnemyPtr[i].orientation == UP || EnemyPtr[i].orientation == DOWN){
			if(EnemyPtr[i].y%72 == 4 && rrand(1,4)==1)
				EnemyPtr[i].orientation = rrand(0,3);
		} else {
			if(EnemyPtr[i].x%72 == 4 && rrand(1,4)==1)
				EnemyPtr[i].orientation = rrand(0,3);
		}

		//before actually moving check for being shot
		if(check_collision_bullets(instantiateRect(EnemyPtr[i].x,EnemyPtr[i].y,62,62))){
			EnemyPtr[i].active = false;
			return;
		}
		//move forward
		switch(EnemyPtr[i].orientation) {
			case UP:
				EnemyPtr[i].y -= speed;
				break;
			case DOWN:
				EnemyPtr[i].y += speed;
				break;
			case LEFT:
				EnemyPtr[i].x -= speed;
				break;
			case RIGHT:
				EnemyPtr[i].x += speed;
				break;
		}

		// if against a wall then undo the movement and change direction
		if(check_collision_walls(lvl, instantiateRect(EnemyPtr[i].x,EnemyPtr[i].y,62,62))){
			//printf("colliding while moving in direction %d\n", EnemyPtr[i].orientation);
			//printf("x: %d, y: %d\n",EnemyPtr[i].x,EnemyPtr[i].y);
			switch(EnemyPtr[i].orientation) {
				case UP:
					EnemyPtr[i].y += speed;
					break;
				case DOWN:
					EnemyPtr[i].y -= speed;
					break;
				case LEFT:
					EnemyPtr[i].x += speed;
					break;
				case RIGHT:
					EnemyPtr[i].x -= speed;
					break;
			}
			enum Direction ogOrientation = EnemyPtr[i].orientation;
			while(EnemyPtr[i].orientation == ogOrientation){
				EnemyPtr[i].orientation = rrand(0,3);
			}
		}

		//also make sure they don't get into the player's spawn box
		if(EnemyPtr[i].y > 6*72+4){
			EnemyPtr[i].y = 6*72+4;
			enum Direction ogOrientation = EnemyPtr[i].orientation;
			while(EnemyPtr[i].orientation == ogOrientation){
				EnemyPtr[i].orientation = rrand(0,3);
			}
		}

		// finally if "out of bounds" (meaning if they go through the warping doors) warp them over the other side
		if(EnemyPtr[i].x > 13*72+4)
			EnemyPtr[i].x = 72+4;
		else if(EnemyPtr[i].x < 72+4)
			EnemyPtr[i].x = 13*72+4;

	}
	return; //end :)
}

bool check_collision_enemies(SDL_Rect rect){
	SDL_Rect enemyr;

	//iterate through enemies array
	for(int i = 0; i<enemiesSpawned; i++){
		if(!EnemyPtr[i].active || !EnemyPtr[i].visible)
			continue;

		enemyr.x = EnemyPtr[i].x;
		enemyr.y = EnemyPtr[i].y;
		enemyr.w = 62;
		enemyr.h = 62;

		if(checkSDLCollision(enemyr, rect)){
			return true;
		}
	}
	
	return false;
}

int get_kills(){
	int k = 0;
	for(int i=0; i<enemiesSpawned; i++){
		if(!EnemyPtr[i].active)
			k++;
	}
	return k;
}

void draw_kills(SDL_Surface *screen, SDL_Surface *numbermap){

	SDL_Rect src = instantiateRect(0, 0, 64, 64);
	src.x += 64*get_kills();

	SDL_Rect dest = instantiateRect(720, 570, 64, 64);

	int r = SDL_BlitSurface(numbermap, &src, screen, &dest);
	if(r != 0)
		printf("Error drawing kills counter");
}

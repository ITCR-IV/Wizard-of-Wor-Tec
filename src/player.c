#include "wall.h"

void init_player(){
	PlayerPtr = malloc(sizeof(Player));
	PlayerPtr->x = 12*72 + 5;
	PlayerPtr->y = 7*72 + 5;
	PlayerPtr->orientation = RIGHT;
	PlayerPtr->state = INITIAL;
	PlayerPtr->cooldown = 0;
	PlayerPtr->lives = 4;
}

void terminate_player(){
	free(PlayerPtr);
}

void reset_player(){
	terminate_player();
	init_player();
}

void draw_player(SDL_Surface *screen, SDL_Surface *sprite){

	SDL_Rect p;
	SDL_Rect dest;
	
	// draw base walls
	p.x = 0;
	p.y = 0;
	p.w = sprite->w;
	p.h = sprite->h;
	
	dest.x = PlayerPtr->x;
	dest.y = PlayerPtr->y;
	dest.w = sprite->w;
	dest.h = sprite->h;

	SDL_BlitSurface(sprite, &p, screen, &dest);
}

void move_player(enum Direction d){ //d is the direction the player is pressing currently
	//first check if player already moving in a direction
	//then check if he's in the range to clip into a square or if he should just keep going
	//if he can clip into a square and change direction the check the execute the folloing
	//the clipping requirement is not necessary for simply turning around
	if (d == UP) {
	}
	if (d == DOWN) {
	}
	if (d == RIGHT) {
	}
	if (d == LEFT) {
	}

}


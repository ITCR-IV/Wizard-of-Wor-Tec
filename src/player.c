#include "wall.h"
#include <stdbool.h>

void init_player(){
	PlayerPtr = malloc(sizeof(Player));
	PlayerPtr->x = 12*72 + 5;
	PlayerPtr->y = 7*72 + 5;
	PlayerPtr->orientation = RIGHT;
	PlayerPtr->state = INITIAL;
	PlayerPtr->cooldown = 0;
	PlayerPtr->lives = 4;
	BaseLvlPtr[12].w = 10*72; //open wall so player can leave
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

void move_player(enum Direction d, int lvl){ //d is the direction the player is pressing currently
	int speed = 4;
	//first check if player is just starting the game
	if(PlayerPtr->state == INITIAL){
		if (d!=UP)
			return;
		PlayerPtr->x = PlayerPtr->x - 72;
		BaseLvlPtr[12].w = 11*72; // close the gate
		PlayerPtr->state = MOVING;
		PlayerPtr->orientation = UP;
		return;
	}
	//then check if player already moving in a direction
	if(PlayerPtr->state == MOVING){
		if(PlayerPtr->orientation == UP || PlayerPtr->orientation == DOWN){
			//the clipping requirement is not necessary for simply turning around
			if (d == UP || d == DOWN) {
				PlayerPtr->orientation = d;
			}else{
				//then check if he's in the range to clip into a square or if he should just keep going
				if(PlayerPtr->y%72 <= 11 || PlayerPtr->y%72 >=68){ //if within 10 pixels of tile border nd wanting to go in diff direction then clip the player to align with grid
					if(PlayerPtr->y%72<=11)
						PlayerPtr->y += (6 - PlayerPtr->y%72);
					else
						PlayerPtr->y += (72 - PlayerPtr->y%72 + 6);
					PlayerPtr->state = STATIC;
					move_player(d);
					return;
				}
			}
		}
		if(PlayerPtr->orientation == LEFT || PlayerPtr->orientation == RIGHT){
			if (d == RIGHT || d == LEFT) {
				PlayerPtr->orientation = d;
			}else{
				if(PlayerPtr->x%72 <= 11 || PlayerPtr->x%72 >=68){ 
					if(PlayerPtr->x%72<=11)
						PlayerPtr->x += (6 - PlayerPtr->x%72);
					else
						PlayerPtr->x += (72 - PlayerPtr->x%72 + 6);
					PlayerPtr->state = STATIC;
					move_player(d);
					return;
				}
			}
		}
	}

	//he is either static in a tile and can move anywhere or he was just forced into this state from clipping and this was called again
	if(PlayerPtr->state == STATIC){
		if(d == NOWHERE) // in case the player doesn't wish to move this returns so the move at the end isn't executed
			return;

		PlayerPtr->orientation = d;
	}

	// finally move the player forward
	switch(PlayerPtr->orientation) {
		case UP:
			PlayerPtr->y -= speed;
			break;
		case DOWN:
			PlayerPtr->y += speed;
			break;
		case LEFT:
			PlayerPtr->x -= speed;
			break;
		case RIGHT:
			PlayerPtr->x += speed;
			break;
	}

	// if against a wall then undo the movement
	if(check_collision_walls(lvl, instantiateRect(PlayerPtr->x,PlayerPtr->y,62,62))){
		switch(PlayerPtr->orientation) {
			case UP:
				PlayerPtr->y += speed;
				break;
			case DOWN:
				PlayerPtr->y -= speed;
				break;
			case LEFT:
				PlayerPtr->x += speed;
				break;
			case RIGHT:
				PlayerPtr->x -= speed;
				break;
		}
	}

	// finally if "out of bounds" (meaning if they go through the warping doors) warp them over the other side
	if(PlayerPtr->x > 13*72+6)
		PlayerPtr->x = 72+6;
	else if(PlayerPtr->x < 72+6)
		PlayerPtr->x = 13*72+6;

	return; //end :)
}


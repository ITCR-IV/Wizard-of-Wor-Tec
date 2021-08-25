#include "player.h"

#include "SDL_helpers.h"
#include "wall.h"
#include "enemy.h"

void init_player(){
	// MUST BE CALLED AFTER INSTANTIATING LVL BECAUSE OF THE CHANGE OF WALL WIDTH
	PlayerPtr = malloc(sizeof(Player));
	PlayerPtr->x = 12*72 + 4;
	PlayerPtr->y = 7*72 + 4;
	PlayerPtr->orientation = LEFT;
	PlayerPtr->state = INITIAL;
	PlayerPtr->cooldown = 30; //start with cooldown so shot doesn't get fired the moment the lvl starts
	PlayerPtr->lives = 4;
	BaseLvlPtr[12].w = 10*72; //open wall so player can leave
	PlayerPtr->activeBullets = 0;
	BulletPtr = malloc(20*sizeof(Bullet));
	for(int i = 0; i < 20; i++){
		BulletPtr[i].x = BulletPtr[i].y = 0;
		BulletPtr[i].orientation = NOWHERE;
		BulletPtr[i].active = false;
	}
}

void terminate_player(){
	free(PlayerPtr);
	free(BulletPtr);
}

void reset_player(){
	// MUST BE CALLED AFTER INSTANTIATING LVL BECAUSE OF THE CHANGE OF WALL WIDTH
	PlayerPtr->x = 12*72 + 4;
	PlayerPtr->y = 7*72 + 4;
	PlayerPtr->orientation = LEFT;
	PlayerPtr->state = INITIAL;
	PlayerPtr->cooldown = 30; //start with cooldown so shot doesn't get fired the moment the lvl starts
	BaseLvlPtr[12].w = 10*72; //open wall so player can leave
	PlayerPtr->activeBullets = 0;
	for(int i = 0; i < 20; i++){
		BulletPtr[i].x = BulletPtr[i].y = 0;
		BulletPtr[i].orientation = NOWHERE;
		BulletPtr[i].active = false;
	}
}

void draw_player(SDL_Surface *screen, SDL_Surface *sprite){

	SDL_Rect p;
	SDL_Rect dest;
	
	p.x = PlayerPtr->orientation*sprite->w/4;
	p.y = 0;
	p.w = sprite->w/4;
	p.h = sprite->h;
	
	dest.x = PlayerPtr->x;
	dest.y = PlayerPtr->y;
	dest.w = sprite->w/4;
	dest.h = sprite->h;

	SDL_BlitSurface(sprite, &p, screen, &dest);
}

void draw_lives(SDL_Surface *screen, SDL_Surface *sprite){
	SDL_Rect p;
	SDL_Rect dest;
	
	p.x = LEFT*sprite->w/4;
	p.y = 0;
	p.w = sprite->w/4;
	p.h = sprite->h;

	if(PlayerPtr->lives > 1){
		// This if else makes it so that when player is in initial state all lives are on right
		// but when it gets out of the initial space one life takes it up
		if(PlayerPtr->state != INITIAL){
			dest.x = 12*72 + 4;
			dest.y = 7*72 + 4;
		}
		else{ // The first life is painted above the other ones on the right while player is in INITIAL state
			dest.x = 13*72 + 4;
			dest.y = 7*72 + 4 - (PlayerPtr->lives-2)*72;
		}
		dest.w = sprite->w/4;
		dest.h = sprite->h;

		SDL_BlitSurface(sprite, &p, screen, &dest);
	}

	if(PlayerPtr->lives > 2){
		for(int i = 0; i < PlayerPtr->lives-2; i++){
			dest.x = 13*72 + 4;
			dest.y = 7*72 + 4 - i*72;
			dest.w = sprite->w/4;
			dest.h = sprite->h;

			SDL_BlitSurface(sprite, &p, screen, &dest);
		}
	}
}

void move_player(enum Direction d, int lvl){ //d is the direction the player is pressing currently
	int speed = 4;
	//first check if player is just starting the game
	if(PlayerPtr->state == INITIAL){
		if (d!=UP)
			return;
		PlayerPtr->y -= speed*2;
		if(PlayerPtr->y <= 6*72+4){
			BaseLvlPtr[12].w = 11*72; // close the gate
			PlayerPtr->state = MOVING;
			PlayerPtr->orientation = UP;}
		return;
	}
	
	// check collision with enemies
	if(check_collision_enemies(instantiateRect(PlayerPtr->x,PlayerPtr->y,62,62))){
		PlayerPtr->lives--;
		reset_player();
		return;
	}

	//then check if player already moving in a direction
	if(PlayerPtr->state == MOVING){
		//printf("moving in direction: %d, while holding %d\n",PlayerPtr->orientation,d);
		if(PlayerPtr->orientation == UP || PlayerPtr->orientation == DOWN){
			//the clipping requirement is not necessary for simply turning around
			if (d == UP || d == DOWN) {
				PlayerPtr->orientation = d;
				//then check if he's in the range to clip into a square or if he should just keep going
			}else if(PlayerPtr->y%72 <= 23 || PlayerPtr->y%72 >=62){ //if within 10 pixels of tile border nd wanting to go in diff direction then clip the player to align with grid
					if(PlayerPtr->y%72<=23)
						PlayerPtr->y += (4 - PlayerPtr->y%72);
					else
						PlayerPtr->y += (72 - PlayerPtr->y%72 + 4);
					PlayerPtr->state = STATIC;
					move_player(d, lvl);
					return;
				
			}
		}
		if(PlayerPtr->orientation == LEFT || PlayerPtr->orientation == RIGHT){
			if (d == RIGHT || d == LEFT) {
				PlayerPtr->orientation = d;
			}else if(PlayerPtr->x%72 <= 23 || PlayerPtr->x%72 >=62){ 
					if(PlayerPtr->x%72<=23)
						PlayerPtr->x += (4 - PlayerPtr->x%72);
					else
						PlayerPtr->x += (72 - PlayerPtr->x%72 + 4);
					PlayerPtr->state = STATIC;
					move_player(d, lvl);
					return;
				
			}
		}
	}
	

	//he is either static in a tile and can move anywhere or he was just forced into this state from clipping and this was called again
	if(PlayerPtr->state == STATIC){
		if(d == NOWHERE) // in case the player doesn't wish to move this returns so the move at the end isn't executed
			return;

		PlayerPtr->orientation = d;
		PlayerPtr->state = MOVING;
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
		//printf("colliding while moving in direction %d\n", PlayerPtr->orientation);
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
	if(PlayerPtr->x > 13*72+3)
		PlayerPtr->x = 72+3;
	else if(PlayerPtr->x < 72+4)
		PlayerPtr->x = 13*72+3;

	return; //end :)
}

bool check_los(int x, int y, int lvl){
	SDL_Rect p;
	int x2;
	int y2;
	int w;
	int h;
	if(x > PlayerPtr->x){
		x2 = PlayerPtr->x+31;
		w = x+31-(PlayerPtr->x+31);}
	else{
		x2 = x+31;
		w = PlayerPtr->x+31-(x+31);}

	if(y > PlayerPtr->y){
		y2 = PlayerPtr->y+31;
		h = y+31-(PlayerPtr->y+31);}
	else{
		y2 = y+31;
		h = PlayerPtr->y+31-(y+31);}

	return !check_collision_walls(lvl, instantiateRect(x2,y2,w,h));
}

void player_shoot(){
	if(PlayerPtr->cooldown>0)
		return;
	if(PlayerPtr->activeBullets>=20){
		printf("Max bullet limit reached, can't shoot any more bullets");
		return;
	}
	for(int i=0; i<20; i++){
		if(!BulletPtr[i].active){
			BulletPtr[i].active = true;
			BulletPtr[i].orientation = PlayerPtr->orientation;
			// bullet length is going to be 25
			
			switch(PlayerPtr->orientation) {
			case UP:
				BulletPtr[i].x = PlayerPtr->x+27;
				BulletPtr[i].y = PlayerPtr->y-bulletLength+4;
				break;
 			case DOWN:
				BulletPtr[i].x = PlayerPtr->x+27;
				BulletPtr[i].y = PlayerPtr->y+62-4;
				break;
 			case LEFT:
				BulletPtr[i].x = PlayerPtr->x-bulletLength+4;
				BulletPtr[i].y = PlayerPtr->y+27;
				break;
 			case RIGHT:
				BulletPtr[i].x = PlayerPtr->x+62-4;
				BulletPtr[i].y = PlayerPtr->y+27;
				break;
			}
			PlayerPtr->activeBullets++;
			PlayerPtr->cooldown = 22;
			return;
		}
	}
	printf("Max limit of bullets reached (in the wrong place ?? )");
}

void draw_bullets(SDL_Surface *screen){
	SDL_Rect b;
	
	int n=0; //to not go over the active bullets amount for optimization
	//iterate through bullets array
	for(int i = 0; i<20; i++){
		if(n == PlayerPtr->activeBullets)
			break;
		if(!BulletPtr[i].active)
			continue;
		n++;
		b.x = BulletPtr[i].x;
		b.y = BulletPtr[i].y;
		if(BulletPtr[i].orientation == UP || BulletPtr[i].orientation == DOWN){
			b.w = bulletWidth;
			b.h = bulletLength;
		}else{
			b.w = bulletLength;
			b.h = bulletWidth;
		}
		
		int r = SDL_FillRect(screen , &b, SDL_MapRGB(screen->format, 202, 0, 6));

		if (r !=0){
			printf("fill rectangle failed in func draw_bullets in bullet #%d", i);
		}
	}
}

void move_bullets(int lvl){
	//remove 1 cd from player
	if(PlayerPtr->cooldown > 0)
		PlayerPtr->cooldown--;
	int speed = 15;

	int n = 0;
	for(int i = 0; i < 20; i++){
		if(n == PlayerPtr->activeBullets)
			break;
		if(!BulletPtr[i].active)
			continue;
		n++;
				
		// if against a wall then yeet bullet out of existence
		if(BulletPtr[i].orientation == UP || BulletPtr[i].orientation == DOWN){
			if(check_collision_walls(lvl, instantiateRect(BulletPtr[i].x, BulletPtr[i].y, bulletWidth, bulletLength))){
				BulletPtr[i].active = false;
				PlayerPtr->activeBullets--;
			}
		}else{
			if(check_collision_walls(lvl, instantiateRect(BulletPtr[i].x, BulletPtr[i].y, bulletLength, bulletWidth))){
				BulletPtr[i].active = false;
				PlayerPtr->activeBullets--;
			}
		}

		//if bullet active then move it
		switch(BulletPtr[i].orientation) {
			case UP:
				BulletPtr[i].y -= speed;
				break;
			case DOWN:
				BulletPtr[i].y += speed;
				break;
			case LEFT:
				BulletPtr[i].x -= speed;
				break;
			case RIGHT:
				BulletPtr[i].x += speed;
				break;
		}


		// if "out of bounds" (meaning if they go through the warping doors) warp them over the other side
		if(BulletPtr[i].x > 14*72-bulletWidth)
			BulletPtr[i].x = 72+3;
		else if(BulletPtr[i].x < 72+4)
			BulletPtr[i].x = 13*72+3;
		
	}
	return; //end :)
}

bool check_collision_bullets(SDL_Rect rect){
	SDL_Rect bulletr;

	int n=0; //to not go over the active bullets amount for optimization
	//iterate through bullets array
	for(int i = 0; i<20; i++){
		if(n >= PlayerPtr->activeBullets)
			break;
		if(!BulletPtr[i].active)
			continue;
		n++;
		bulletr.x = BulletPtr[i].x;
		bulletr.y = BulletPtr[i].y;

		if(BulletPtr[i].orientation == UP || BulletPtr[i].orientation == DOWN){
		bulletr.w = bulletWidth;
		bulletr.h = bulletLength;
		}
		else{
		bulletr.w = bulletLength;
		bulletr.h = bulletWidth;
		}

		if(checkSDLCollision(bulletr, rect)){
			//printf("Colliding with basic wall #%d\n",i);
			BulletPtr[i].active = false;
			PlayerPtr->activeBullets--;
			return true;
		}
	}
	
	return false;
}

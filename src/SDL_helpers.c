#include "SDL_helpers.h"
#include <SDL_image.h>


SDL_Surface* loadSurface(SDL_Surface *screen, char img[]) {
	//The final adjusted image
	SDL_Surface* adjustedSurface;
	
	char path[strlen("../imgs/")+strlen(img)];

	strcpy(path, "../imgs/");

	SDL_Surface* loadedImg = IMG_Load(strcat(path,img));
	if(!loadedImg) {
		printf("Unable to load image %s!\nSDL_image Error: %s\n", img, IMG_GetError());
		return NULL;
	}
	else {
		// Turn newly loaded image surface to screen surface format to avoid conversions in the future
		adjustedSurface = SDL_ConvertSurface(loadedImg, screen->format, 0);
		if(adjustedSurface == NULL) {
			printf("Unable to adjust image %s! SDL Error: %s\n", img, SDL_GetError());
		}

		//Remember to free the initial surface
		SDL_FreeSurface(loadedImg);
	}

	return adjustedSurface;
}

bool checkSDLCollision(SDL_Rect rect1, SDL_Rect rect2){
	bool collideX;
	bool collideY;
	if(rect1.x <= rect2.x){
		collideX = rect2.x <= rect1.x+rect1.w;
	}
	else{
		collideX = rect1.x <= rect2.x+rect2.w;
	}
	if(rect1.y <= rect2.y){
		collideY = rect2.y <= rect1.y+rect1.w;
	}
	else{
		collideY = rect1.y <= rect2.y+rect2.w;
	}
	return collideX&&collideY;
}

SDL_Rect instantiateRect(int x, int y, int w, int h){
	SDL_Rect rect;
	rect.x=x;
	rect.y=y;
	rect.w=w;
	rect.h=h;
	return rect;
}

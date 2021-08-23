#ifndef SDLHELPERS_H
#define SDLHELPERS_H

#include <SDL.h>	//SDL version 2.0
#include <stdbool.h>

SDL_Surface* loadSurface(SDL_Surface *screen, char img[]);

bool checkSDLCollision(SDL_Rect rect1, SDL_Rect rect2);

#endif

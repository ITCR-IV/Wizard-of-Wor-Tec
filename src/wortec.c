//Using libs SDL, glibc
#include <SDL.h>	//SDL version 2.0
#include <SDL_image.h>
#include "SDL_helpers.h" //my own code
#include <stdlib.h>
#include <stdio.h>

//Game elements
#include "wall.h"
#include "player.h"
#include "enemy.h"
#include "directions.h"


#define SCREEN_WIDTH 1080	//window height
#define SCREEN_HEIGHT 720	//window width

//function prototypes
//initilise SDL
int init(int w, int h, int argc, char *args[]);

// Program globals
int width, height;		//used if fullscreen

SDL_Window* window = NULL;	//The window we'll be rendering to
SDL_Renderer *renderer;		//The renderer SDL will use to draw to the screen

//surfaces
static SDL_Surface *screen;
static SDL_Surface *spacebg;
static SDL_Surface *playerSprite;
static SDL_Surface *monstersSheet;
static SDL_Surface *title;
static SDL_Surface *numbermap;
static SDL_Surface *end;

//textures
SDL_Texture *screen_texture;

int check_game_status(){
	int l = get_lives();
	int k = get_kills();
	
	if(k>=9)
		return 1;
	if(l<=0)
		return -1;
	return 0;
}

void draw_game_over(){
	SDL_Rect src = instantiateRect(0, 0, end->w, end->h);
	SDL_Rect dest = instantiateRect(0, 0, screen->w, screen-> h);

	SDL_BlitSurface(end, &src, screen, &dest);
}

void draw_bg(){
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0; src.y = 0; src.w = spacebg->w; src.h = spacebg->h;
	dest.x = 0; dest.y = 0; dest.w = screen->w; dest.h = screen->h;

	SDL_BlitSurface(spacebg, &src, screen, &dest);
}

static void draw_menu(int lvl) {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = title->w;
	src.h = title->h;

	dest.x = (screen->w / 2) - (src.w / 2);
	dest.y = (screen->h / 2) - (src.h / 2);
	dest.w = title->w;
	dest.h = title->h;

	SDL_BlitSurface(title, &src, screen, &dest);

	// Draw levels

	int spacing = 130;

	src.x = 64;
	src.y = 0;
	src.w = 64;
	src.h = 64;

	dest.x = (screen->w / 2) - src.w/2 - spacing;
	dest.y = 375;
	dest.w = 64;
	dest.h = 64;

	SDL_BlitSurface(numbermap, &src, screen, &dest);

	dest.x+=spacing;
	src.x += src.w;
	SDL_BlitSurface(numbermap, &src, screen, &dest);

	dest.x+=spacing;
	src.x += src.w;
	SDL_BlitSurface(numbermap, &src, screen, &dest);

	SDL_Rect lvlBox[4];

	if(lvl==1)
		spacing -= 10;
	lvlBox[0].x = (screen->w/2) - src.w/2 - spacing - 15 + (lvl-1)*spacing; lvlBox[0].y = 373; lvlBox[0].w = 68; lvlBox[0].h = 2;
	lvlBox[1].x = (screen->w/2) - src.w/2 - spacing - 15 + (lvl-1)*spacing; lvlBox[1].y = 373; lvlBox[1].w = 2; lvlBox[1].h = 68;
	lvlBox[2].x = (screen->w/2) - src.w/2 - spacing - 15 + 66 + (lvl-1)*spacing; lvlBox[2].y = 373; lvlBox[2].w = 2; lvlBox[2].h = 68;
	lvlBox[3].x = (screen->w/2) - src.w/2 - spacing - 15 + (lvl-1)*spacing; lvlBox[3].y = 439; lvlBox[3].w = 68; lvlBox[3].h = 2;
	for(int i = 0; i<4; i++){
		int r = SDL_FillRect(screen , &lvlBox[i], SDL_MapRGB(screen->format, 255, 255, 255));

		if (r !=0){
			printf("fill rectangle failed in func draw_menu in first iteration #%d", i);
		}
	}

}

int main (int argc, char *args[]) {
		
	//SDL Window setup
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1) {
		
		return 0;
	}
	
	SDL_GetWindowSize(window, &width, &height);
	
	int sleep = 0;
	int quit = 0;
	int state = 0;
	int r = 0;
	Uint32 next_game_tick = SDL_GetTicks();
	
	// Initialize first level
	init_labyrinth(1);

	// Initialize player character
	init_player();

	// Initializa enemies
	init_enemies();
	
	// This is for the menu
	int lvlSelect = 1;

	//render loop
	while(quit == 0) {
	
		//check for new events every frame
		SDL_PumpEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		
		if (keystate[SDL_SCANCODE_ESCAPE]) 
			quit = 1;

		if (state >= 0){
			//draw background
			SDL_RenderClear(renderer);
			draw_bg();
		}
		
		//display main menu
		if (state == 0 ) {
		
			if (keystate[SDL_SCANCODE_SPACE]) {
				state = lvlSelect;
				//Initialize labyrinth
				reset_labyrinth(state);
				hard_reset_player();
				reset_enemies();
			}
		

			if(keystate[SDL_SCANCODE_1])
				lvlSelect = 1;
			if(keystate[SDL_SCANCODE_2])
				lvlSelect = 2;
			if(keystate[SDL_SCANCODE_3])
				lvlSelect = 3;

			if(keystate[SDL_SCANCODE_RIGHT]){
				lvlSelect++;
				if(lvlSelect > 3)
					lvlSelect = 1;
			}
			if(keystate[SDL_SCANCODE_LEFT]){
				lvlSelect--;
				if(lvlSelect < 1)
					lvlSelect = 3;
			}

			draw_menu(lvlSelect);

			if(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_LEFT])
				SDL_Delay(100);
		
		//display gameover
		} else if (state == -1) {
		
			if (keystate[SDL_SCANCODE_SPACE]) {
				state = 0;
				//delay for a little bit so the space bar press dosnt get triggered twice
				//while the main menu is showing
            			SDL_Delay(500);
			}

		//display the game
		} else if (state >= 1) {
			
			// player movement
			if (keystate[SDL_SCANCODE_DOWN]) 
				move_player(DOWN, state);
			else if (keystate[SDL_SCANCODE_UP]) 
				move_player(UP, state);
			else if (keystate[SDL_SCANCODE_RIGHT]) 
				move_player(RIGHT, state);
			else if (keystate[SDL_SCANCODE_LEFT]) 
				move_player(LEFT, state);
			else
				move_player(NOWHERE, state);

			// player shooting
			if (keystate[SDL_SCANCODE_SPACE])
				player_shoot();

			//enemy movement and spawning
			move_enemies(state);
			spawn_enemy();

			//Move bullets
			move_bullets(state);
			
			//draw level
			draw_walls(screen, state);
			//draw player
			draw_player(screen, playerSprite);
			//draw lives
			draw_lives(screen, playerSprite);
			//draw bullets
			draw_bullets(screen);
			//draw enemies
			draw_enemies(screen, monstersSheet);
			//draw enemy radar
			draw_radar(screen);
			//draw kills
			draw_kills(screen, numbermap);

			r = check_game_status();
			if( r != 0){
				draw_game_over();
				state=-1;}


		}
	
		SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof (Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		//draw to the display
		SDL_RenderPresent(renderer);
				
		//time it takes to render  frame in milliseconds
		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();
	
		if( sleep >= 0 ) {
            				
			SDL_Delay(sleep);
		}
	}

	//free level data
	terminate_labyrinth();

	//free player data
	terminate_player();

	//free enemies data
	terminate_enemies();

	//free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_FreeSurface(numbermap);
	SDL_FreeSurface(end);
	SDL_FreeSurface(spacebg);
	SDL_FreeSurface(playerSprite);
	SDL_FreeSurface(monstersSheet);

	//free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);
	
	//Destroy window 
	SDL_DestroyWindow(window);

	//Quit SDL subsystems 
	SDL_Quit(); 
	 
	return 0;
	
}

int init(int width, int height, int argc, char *args[]) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		
		return 1;
	} 
	
	int i;
	
	for (i = 0; i < argc; i++) {
		//
		//Create window	
		if(strcmp(args[i], "-f")) {
			
			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
		
		} else {
		
			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
		}
	}

	if (window == NULL) { 
		
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		
		return 1;
	}

	//create the screen sruface where all the elemnts will be drawn onto (ball, paddles, net etc)
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
	
	if (screen == NULL) {
		
		printf("Could not create the screen surfce! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//create the screen texture to render the screen surface to the actual display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);

	if (screen_texture == NULL) {
		
		printf("Could not create the screen_texture! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Load the space bg
	spacebg = loadSurface(screen, "space_bg.png");

	//Load the player sprite
	playerSprite = loadSurface(screen, "player.png");

	//Load the enemies spritesheet
	monstersSheet = loadSurface(screen, "monsters.png");

	//Load the title image
	title = loadSurface(screen, "WizardTEC.png");

	//Load the numbermap image
	numbermap = loadSurface(screen, "numbermap.bmp");
	
	//Load the gameover image
	end = loadSurface(screen, "GameOver.png");
	
	// Set the title colourkey. 
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 255);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(numbermap, SDL_TRUE, colorkey);
	
	return 0;
}


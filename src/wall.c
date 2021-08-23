#include <SDL.h>	//SDL version 2.0
#include <stdlib.h>
#include <stdio.h>
#include "wall.h"


void init_labyrinth(int lvl) {
	if( lvl > 3 || lvl < 1){
		printf("Level given out of bounds");
		return;}
	int width = 10;
	if( lvl==1){
		LabyrinthPtr =malloc(18*sizeof(Wall));
		LabyrinthPtr[0].x =3*72-width/2; LabyrinthPtr[0].y =2*72-width/2; LabyrinthPtr[0].w =72+width; LabyrinthPtr[0].h =width;
		LabyrinthPtr[1].x =4*72-width/2; LabyrinthPtr[1].y =2*72-width/2; LabyrinthPtr[1].w =width; LabyrinthPtr[1].h =2*72+width;
		LabyrinthPtr[2].x =3*72-width/2; LabyrinthPtr[2].y =4*72-width/2; LabyrinthPtr[2].w =72+width; LabyrinthPtr[2].h =width;
		
		LabyrinthPtr[3].x =11*72-width/2; LabyrinthPtr[3].y =2*72-width/2; LabyrinthPtr[3].w =72+width; LabyrinthPtr[3].h =width;
		LabyrinthPtr[4].x =11*72-width/2; LabyrinthPtr[4].y =2*72-width/2; LabyrinthPtr[4].w =width; LabyrinthPtr[4].h =2*72+width;
		LabyrinthPtr[5].x =11*72-width/2; LabyrinthPtr[5].y =4*72-width/2; LabyrinthPtr[5].w =72+width; LabyrinthPtr[5].h =width;

		LabyrinthPtr[6].x =5*72-width/2; LabyrinthPtr[6].y =3*72-width/2; LabyrinthPtr[6].w =width; LabyrinthPtr[6].h =72+width;
		LabyrinthPtr[7].x =5*72-width/2; LabyrinthPtr[7].y =3*72-width/2; LabyrinthPtr[7].w =2*72+width; LabyrinthPtr[7].h =width;
		LabyrinthPtr[8].x =7*72-width/2; LabyrinthPtr[8].y =2*72-width/2; LabyrinthPtr[8].w =width; LabyrinthPtr[8].h =72+width;

		LabyrinthPtr[9].x =4*72-width/2; LabyrinthPtr[9].y =5*72-width/2; LabyrinthPtr[9].w =width; LabyrinthPtr[9].h =72+width;
		LabyrinthPtr[10].x =4*72-width/2; LabyrinthPtr[10].y =5*72-width/2; LabyrinthPtr[10].w =2*72+width; LabyrinthPtr[10].h =width;
		LabyrinthPtr[11].x =6*72-width/2; LabyrinthPtr[11].y =4*72-width/2; LabyrinthPtr[11].w =width; LabyrinthPtr[11].h =72+width;

		LabyrinthPtr[12].x =8*72-width/2; LabyrinthPtr[12].y =2*72-width/2; LabyrinthPtr[12].w =width; LabyrinthPtr[12].h =72+width;
		LabyrinthPtr[13].x =8*72-width/2; LabyrinthPtr[13].y =3*72-width/2; LabyrinthPtr[13].w =2*72+width; LabyrinthPtr[13].h =width;
		LabyrinthPtr[14].x =10*72-width/2; LabyrinthPtr[14].y =3*72-width/2; LabyrinthPtr[14].w =width; LabyrinthPtr[14].h =72+width;


		LabyrinthPtr[15].x =9*72-width/2; LabyrinthPtr[15].y =4*72-width/2; LabyrinthPtr[15].w =width; LabyrinthPtr[15].h =72+width;
		LabyrinthPtr[16].x =9*72-width/2; LabyrinthPtr[16].y =5*72-width/2; LabyrinthPtr[16].w =2*72+width; LabyrinthPtr[16].h =width;
		LabyrinthPtr[17].x =11*72-width/2; LabyrinthPtr[17].y =5*72-width/2; LabyrinthPtr[17].w =width; LabyrinthPtr[17].h =72+width;
	}
	if( lvl==2){
		LabyrinthPtr =malloc(14*sizeof(Wall));
		LabyrinthPtr[0].x =3*72-width/2; LabyrinthPtr[0].y =2*72-width/2; LabyrinthPtr[0].w =width; LabyrinthPtr[0].h =2*72+width;
		LabyrinthPtr[1].x =4*72-width/2; LabyrinthPtr[1].y =3*72-width/2; LabyrinthPtr[1].w =width; LabyrinthPtr[1].h =2*72+width;
		LabyrinthPtr[2].x =5*72-width/2; LabyrinthPtr[2].y =4*72-width/2; LabyrinthPtr[2].w =width; LabyrinthPtr[2].h =2*72+width;
		LabyrinthPtr[3].x =5*72-width/2; LabyrinthPtr[3].y =2*72-width/2; LabyrinthPtr[3].w =width; LabyrinthPtr[3].h =72+width;
		LabyrinthPtr[4].x =6*72-width/2; LabyrinthPtr[4].y =2*72-width/2; LabyrinthPtr[4].w =width; LabyrinthPtr[4].h =2*72+width;
		LabyrinthPtr[5].x =6*72-width/2; LabyrinthPtr[5].y =5*72-width/2; LabyrinthPtr[5].w =width; LabyrinthPtr[5].h =72+width;
		LabyrinthPtr[6].x =7*72-width/2; LabyrinthPtr[6].y =3*72-width/2; LabyrinthPtr[6].w =width; LabyrinthPtr[6].h =2*72+width;

		LabyrinthPtr[7].x =8*72-width/2; LabyrinthPtr[7].y =3*72-width/2; LabyrinthPtr[7].w =width; LabyrinthPtr[7].h =2*72+width;
		LabyrinthPtr[8].x =12*72-width/2; LabyrinthPtr[8].y =2*72-width/2; LabyrinthPtr[8].w =width; LabyrinthPtr[8].h =2*72+width;
		LabyrinthPtr[9].x =11*72-width/2; LabyrinthPtr[9].y =3*72-width/2; LabyrinthPtr[9].w =width; LabyrinthPtr[9].h =2*72+width;
		LabyrinthPtr[10].x =10*72-width/2; LabyrinthPtr[10].y =4*72-width/2; LabyrinthPtr[10].w =width; LabyrinthPtr[10].h =2*72+width;
		LabyrinthPtr[11].x =10*72-width/2; LabyrinthPtr[11].y =2*72-width/2; LabyrinthPtr[11].w =width; LabyrinthPtr[11].h =72+width;
		LabyrinthPtr[12].x =9*72-width/2; LabyrinthPtr[12].y =2*72-width/2; LabyrinthPtr[12].w =width; LabyrinthPtr[12].h =2*72+width;
		LabyrinthPtr[13].x =9*72-width/2; LabyrinthPtr[13].y =5*72-width/2; LabyrinthPtr[13].w =width; LabyrinthPtr[13].h =72+width;
	}
	if( lvl==3){
		LabyrinthPtr =malloc(25*sizeof(Wall));

		LabyrinthPtr[0].x =6*72-width/2; LabyrinthPtr[0].y =72; LabyrinthPtr[0].w =width; LabyrinthPtr[0].h =72+width/2;
		LabyrinthPtr[1].x =9*72-width/2; LabyrinthPtr[1].y =72; LabyrinthPtr[1].w =width; LabyrinthPtr[1].h =72+width/2;

		LabyrinthPtr[2].x =3*72-width/2; LabyrinthPtr[2].y =2*72-width/2; LabyrinthPtr[2].w =width; LabyrinthPtr[2].h =72+width;
		LabyrinthPtr[3].x =12*72-width/2; LabyrinthPtr[3].y =2*72-width/2; LabyrinthPtr[3].w =width; LabyrinthPtr[3].h =72+width;
		LabyrinthPtr[4].x =7*72-width/2; LabyrinthPtr[4].y =2*72-width/2; LabyrinthPtr[4].w =width; LabyrinthPtr[4].h =72+width;
		LabyrinthPtr[5].x =8*72-width/2; LabyrinthPtr[5].y =2*72-width/2; LabyrinthPtr[5].w =width; LabyrinthPtr[5].h =72+width;

		LabyrinthPtr[6].x =3*72-width/2; LabyrinthPtr[6].y =2*72-width/2; LabyrinthPtr[6].w =2*72+width; LabyrinthPtr[6].h =width;
		LabyrinthPtr[7].x =10*72-width/2; LabyrinthPtr[7].y =2*72-width/2; LabyrinthPtr[7].w =2*72+width; LabyrinthPtr[7].h =width;

		LabyrinthPtr[8].x =4*72-width/2; LabyrinthPtr[8].y =3*72-width/2; LabyrinthPtr[8].w =2*72+width; LabyrinthPtr[8].h =width;
		LabyrinthPtr[9].x =9*72-width/2; LabyrinthPtr[9].y =3*72-width/2; LabyrinthPtr[9].w =2*72+width; LabyrinthPtr[9].h =width;

		LabyrinthPtr[10].x =4*72-width/2; LabyrinthPtr[10].y =3*72-width/2; LabyrinthPtr[10].w =width; LabyrinthPtr[10].h =2*72+width;
		LabyrinthPtr[11].x =11*72-width/2; LabyrinthPtr[11].y =3*72-width/2; LabyrinthPtr[11].w =width; LabyrinthPtr[11].h =2*72+width;

		LabyrinthPtr[12].x =2*72; LabyrinthPtr[12].y =4*72-width/2; LabyrinthPtr[12].w =72+width/2; LabyrinthPtr[12].h =width;
		LabyrinthPtr[13].x =6*72-width/2; LabyrinthPtr[13].y =4*72-width/2; LabyrinthPtr[13].w =72+width; LabyrinthPtr[13].h =width;
		LabyrinthPtr[14].x =8*72-width/2; LabyrinthPtr[14].y =4*72-width/2; LabyrinthPtr[14].w =72+width; LabyrinthPtr[14].h =width;
		LabyrinthPtr[15].x =12*72-width/2; LabyrinthPtr[15].y =4*72-width/2; LabyrinthPtr[15].w =72+width/2; LabyrinthPtr[15].h =width;

		LabyrinthPtr[16].x =6*72-width/2; LabyrinthPtr[16].y =5*72-width/2; LabyrinthPtr[16].w =3*72+width; LabyrinthPtr[16].h =width;

		LabyrinthPtr[17].x =5*72-width/2; LabyrinthPtr[17].y =4*72-width/2; LabyrinthPtr[17].w =width; LabyrinthPtr[17].h =72+width;
		LabyrinthPtr[18].x =10*72-width/2; LabyrinthPtr[18].y =4*72-width/2; LabyrinthPtr[18].w =width; LabyrinthPtr[18].h =72+width;

		LabyrinthPtr[19].x =3*72-width/2; LabyrinthPtr[19].y =5*72-width/2; LabyrinthPtr[19].w =width; LabyrinthPtr[19].h =72+width;
		LabyrinthPtr[20].x =12*72-width/2; LabyrinthPtr[20].y =5*72-width/2; LabyrinthPtr[20].w =width; LabyrinthPtr[20].h =72+width;

		LabyrinthPtr[21].x =6*72-width/2; LabyrinthPtr[21].y =6*72-width/2; LabyrinthPtr[21].w =72+width; LabyrinthPtr[21].h =width;
		LabyrinthPtr[22].x =8*72-width/2; LabyrinthPtr[22].y =6*72-width/2; LabyrinthPtr[22].w =72+width; LabyrinthPtr[22].h =width;

		LabyrinthPtr[23].x =5*72-width/2; LabyrinthPtr[23].y =4*72-width/2; LabyrinthPtr[23].w =width; LabyrinthPtr[23].h =72+width/2;
		LabyrinthPtr[24].x =10*72-width/2; LabyrinthPtr[24].y =4*72-width/2; LabyrinthPtr[24].w =width; LabyrinthPtr[24].h =72+width/2;
	}

	//now instantiate the BaseLvlPtr
	BaseLvlPtr = malloc(17*sizeof(Wall));
	//top wall
	BaseLvlPtr[0].x = 2*72; BaseLvlPtr[0].y = 72; BaseLvlPtr[0].w = 11*72; BaseLvlPtr[0].h = width/2;
	//side top walls
	BaseLvlPtr[1].x = 2*72; BaseLvlPtr[1].y = 72; BaseLvlPtr[1].w = width/2; BaseLvlPtr[1].h = 2*72+width/2;
	BaseLvlPtr[2].x = 13*72-width/2; BaseLvlPtr[2].y = 72; BaseLvlPtr[2].w = width/2; BaseLvlPtr[2].h = 2*72+width/2;
	
	//top gate walls
	BaseLvlPtr[3].x = 72; BaseLvlPtr[3].y = 3*72-width/2; BaseLvlPtr[3].w = 72; BaseLvlPtr[3].h = width;
	BaseLvlPtr[4].x = 13*72; BaseLvlPtr[4].y = 3*72-width/2; BaseLvlPtr[4].w = 72; BaseLvlPtr[4].h = width;
	//bottom gate walls
	BaseLvlPtr[5].x = 72; BaseLvlPtr[5].y = 4*72-width/2; BaseLvlPtr[5].w = 72; BaseLvlPtr[5].h = width;
	BaseLvlPtr[6].x = 13*72; BaseLvlPtr[6].y = 4*72-width/2; BaseLvlPtr[6].w = 72; BaseLvlPtr[6].h = width;

	//side bottom walls
	BaseLvlPtr[7].x = 2*72; BaseLvlPtr[7].y = 4*72-width/2; BaseLvlPtr[7].w = width/2; BaseLvlPtr[7].h = 3*72+width/2;
	BaseLvlPtr[8].x = 13*72-width/2; BaseLvlPtr[8].y = 4*72-width/2; BaseLvlPtr[8].w = width/2; BaseLvlPtr[8].h = 3*72+width/2;

	// Player starting walls
	BaseLvlPtr[9].x = 12*72; BaseLvlPtr[9].y = 7*72; BaseLvlPtr[9].w = width/2; BaseLvlPtr[9].h = 72;
	BaseLvlPtr[10].x = 13*72-width/2; BaseLvlPtr[10].y = 7*72; BaseLvlPtr[10].w = width/2; BaseLvlPtr[10].h = 72;
	BaseLvlPtr[11].x = 12*72; BaseLvlPtr[11].y = 8*72-width/2; BaseLvlPtr[11].w = 72; BaseLvlPtr[11].h = width/2;

	// Bottom wall
	BaseLvlPtr[12].x = 2*72; BaseLvlPtr[12].y = 7*72-width/2; BaseLvlPtr[12].w = 11*72; BaseLvlPtr[12].h = width/2;

	// Radar walls
	BaseLvlPtr[13].x = 428; BaseLvlPtr[13].y = 8*72-72/2-2; BaseLvlPtr[13].w = 224; BaseLvlPtr[13].h = 2;
	BaseLvlPtr[14].x = 428; BaseLvlPtr[14].y = 660; BaseLvlPtr[14].w = 224; BaseLvlPtr[14].h = 2;
	BaseLvlPtr[15].x = 428; BaseLvlPtr[15].y = 8*72-72/2-2; BaseLvlPtr[15].w = 2; BaseLvlPtr[15].h = 124;
	BaseLvlPtr[16].x = 650; BaseLvlPtr[16].y = 8*72-72/2-2; BaseLvlPtr[16].w = 2; BaseLvlPtr[16].h = 124;

}


void terminate_labyrinth(){
	free(BaseLvlPtr);
	free(LabyrinthPtr);
}

void reset_labyrinth(int lvl){
	terminate_labyrinth();
	init_labyrinth(lvl);
}

void draw_walls(SDL_Surface *screen, int lvl) {
	
	SDL_Rect src;
	
	// draw base walls
	for(int i = 0; i<17; i++){
	src.x = BaseLvlPtr[i].x;
	src.y = BaseLvlPtr[i].y;
	src.w = BaseLvlPtr[i].w;
	src.h = BaseLvlPtr[i].h;
	
	int r = SDL_FillRect(screen , &src, 0xffffffff);

	if (r !=0){
		printf("fill rectangle faliled in func draw_walls() in first iteration #%d", i);
	}}
	
	if( lvl > 3 || lvl < 1){
		printf("Level given out of bounds");
		return;}

	int n;
	if( lvl==1){
		n = 18;
	}
	if( lvl==2){
		n = 14;
	}
	if( lvl==3){
		n = 25;
	}
	// draw labyrinth walls
	for(int i = 0; i<n; i++){
	src.x = LabyrinthPtr[i].x;
	src.y = LabyrinthPtr[i].y;
	src.w = LabyrinthPtr[i].w;
	src.h = LabyrinthPtr[i].h;
	
	int r = SDL_FillRect(screen , &src, 0xffffffff);

	if (r !=0){
		printf("fill rectangle faliled in func draw_walls() in second iteration #%s", i);
	}}
}

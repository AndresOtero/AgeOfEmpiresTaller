/*
 * Vista.cpp
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include "../VistaSrc/Vista.h"

#include "stdlib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../VistaSrc/LTexture.h"
#include <math.h>

//Screen dimension constants
const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 1024;

Vista::Vista() {
	// TODO Auto-generated constructor stub

}

bool Vista::init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n",
					SDL_GetError());
			success = false;
		} else {
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n",
						SDL_GetError());
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf(
							"SDL_image could not initialize! SDL_image Error: %s\n",
							IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}
bool Vista::loadMedia() {
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("img/foo.png", gRenderer)) {
		printf("Failed to load walking animation texture!\n");
		success = false;
	} else {
		//Set sprite clips
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 64;
		gSpriteClips[0].h = 205;

		gSpriteClips[1].x = 64;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 64;
		gSpriteClips[1].h = 205;

		gSpriteClips[2].x = 128;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 64;
		gSpriteClips[2].h = 205;

		gSpriteClips[3].x = 196;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 64;
		gSpriteClips[3].h = 205;
	}

	return success;
}
Vista::~Vista() {
	// TODO Auto-generated destructor stub

	//Free loaded images
	gSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int Vista::run() { //Main loop flag
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Current animation frame
	int frame = 0;
	int x = 200, y = 200;
	int img_x = x, img_y = y;
	double a, b;
	double des_x = 0, des_y = 0, distancia = 1, velocidad, delta_x = 0,
			delta_y = 0;
	velocidad = 5;
	//While application is running
	while (!quit) {

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				//Get mouse position
				SDL_GetMouseState(&x, &y);/**
				 a = ((float) (y - img_y)) / ((float) (x - img_x));//pendiente
				 b = img_y - a * img_x;//ordenada al origen
				 **/
			}
		}

		printf("X: %d\n", x);
		printf("img_x: %d\n", img_x);
		delta_x = (double) (x - img_x);
		printf("Delta x: %f\n", delta_x);
		printf("Y: %d\n", y);
		printf("img_y: %d\n", img_y);
		delta_y = (double) (y - img_y);
		printf("Delta y: %f\n", delta_y);
		distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
		if (distancia != 0) {
			if (distancia < velocidad) {
				distancia = velocidad;
			}
			printf("Distancia: %f\n", distancia);
			des_x = (velocidad * delta_x) / distancia;
			printf("desplazamiento x: %f\n", des_x);
			des_y = (velocidad * delta_y) / distancia;
			printf("desplazamiento y: %f\n", des_y);
			if ((sqrt(des_x * des_x) > distancia)
					&& (sqrt(des_y * des_y) < distancia)) {
				img_x = x;
			}
			if ((sqrt(des_y * des_y) > distancia)
					&& ((sqrt(des_x * des_x) < distancia))) {
				img_y = y;
			}
			img_x += des_x;
			img_y += des_y;
		}
		//Move
		/**
		 if ((x != img_x) || (y != img_y)) {
		 if (x == img_x) {//Si esta en el mismo eje x
		 if (y > img_y) {
		 img_y++;
		 } else {
		 img_y--;
		 }
		 } else if (y == img_y) {//Si esta en el mismo eje y
		 if (x > img_x) {
		 img_x++;
		 } else {
		 img_x--;
		 }
		 } else {
		 if (x > img_x){//Si esta en el mismo eje x
		 img_x++;
		 }else{
		 img_x--;
		 }
		 img_y=(a*img_x+b);
		 }
		 }**/

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render current frame
		SDL_Rect* currentClip = &gSpriteClips[frame / 4];
		//gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2,	(SCREEN_HEIGHT - currentClip->h) / 2, currentClip, gRenderer);
		gSpriteSheetTexture.render(img_x - (currentClip->w / 2),
				img_y - (currentClip->h / 2), currentClip, gRenderer);

		//Update screen
		SDL_RenderPresent(gRenderer);

		//Go to next frame
		if ((delta_x != 0.0) || (delta_y != 0.0)) {
			++frame;
		}
		int WALKING_ANIMATION_FRAMES = 4;
		//Cycle animation
		if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
			frame = 0;
		}

	}
}


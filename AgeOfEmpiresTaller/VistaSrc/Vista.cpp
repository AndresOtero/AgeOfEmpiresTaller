/*
 * Vista.cpp
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include "Vista.h"

#include "stdlib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"
#include <math.h>

//Screen dimension constants
const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 1024;

Vista::Vista() {
	// TODO Auto-generated constructor stub

}
int Vista::altura_por_celda(){

	//devuelve alto de imagen

}

int Vista::ancho_por_celda(){

	//devuelve ancho de imagen
}

void Vista::transformar_cartesiana_isometrica(int cart_x,int cart_y,int& iso_x,int& iso_y){
	iso_x= ( cart_x/ this->ancho_por_celda() + cart_y/ this->altura_por_celda() )/2  ;
	iso_y = ( cart_y/ this->altura_por_celda() - cart_x/ this->ancho_por_celda() )/2;
}

void Vista::transformar_isometrica_cartesiana(int iso_x,int iso_y,int& cart_x,int& cart_y){

	cart_x = ( iso_x - iso_y ) * this->ancho_por_celda();
	cart_y = ( iso_x + iso_y)* this->altura_por_celda();
}

bool Vista::init() {
	//Initialization flag
	bool success = true;
	this -> gRenderer = NULL;
	this -> gWindow = NULL;
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
		gWindow = SDL_CreateWindow("Age of empires", SDL_WINDOWPOS_UNDEFINED,
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
		//creo dibujo
		this->personaje=new Dibujo;
		this->pasto=new Dibujo;
	}

	return success;
}
bool Vista::loadMedia() {
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!this->personaje->cargar_archivo("img/foo.png", gRenderer)) {
		printf("Failed to load walking animation texture!\n");
		success = false;
	} else {
		//Set sprite clips
		this->personaje->set_cantidad_de_imagenes(4);
		for (int i = 0; i < 4; i++) {
			this->personaje->set_imagen(i,i*64,0,64,205);
		}
	}
	//Load sprite sheet texture
		if (!this->pasto->cargar_archivo("img/Sprites/crops.png", gRenderer)) {
			printf("Failed to load walking animation texture!\n");
			success = false;
		} else {
			//Set sprite clips
			this->pasto->set_cantidad_de_imagenes(4);
			for (int i = 0; i < 4; i++) {
				this->pasto->set_imagen(0,0,0,128,90);
			}
		}

	return success;
}
Vista::~Vista() {
	// TODO Auto-generated destructor stub

	//Free loaded images
	delete personaje;

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

	this->personaje->set_posicion_default(200,200);
	this->pasto->set_posicion_default(200,200);
	int x=200, y=200 ;

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
				SDL_GetMouseState(&x, &y);
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0, 0,0xFF, 0);
		SDL_RenderClear(gRenderer);

		//Render current frame

		for(int i=0;i<SCREEN_WIDTH+128;i+=128){
			for(int j=0;j<SCREEN_HEIGHT+90;j+=90){
				this->pasto->set_posicion_default(i,j);
				this->pasto->render(gRenderer);
			}
			for(int j=45;j<SCREEN_HEIGHT;j+=90){
				this->pasto->set_posicion_default(i+64,j);
				this->pasto->render(gRenderer);
			}
		}
		this->personaje->render(gRenderer);
		this->personaje->set_velocidad(10);
		this->personaje->mover(x, y);


		//Update screen
		SDL_RenderPresent(gRenderer);


	}
	return 0;
}


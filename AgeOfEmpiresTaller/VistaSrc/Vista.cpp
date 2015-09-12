/*
 * Vista.cpp
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include "Vista.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <cstdio>

#include "../ModeloSrc/Modelo.h"
#include "Dibujo.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

Vista::Vista(Modelo* modelo) {
	this -> modelo = modelo;
}

int Vista::altura_por_celda(){
	return 90;
	//devuelve alto de imagen111111111111111

}

int Vista::ancho_por_celda(){
	return 128;
	//devuelve ancho de imagen

}


void Vista::transformar_cartesiana_isometrica(int cart_x,int cart_y,int& iso_x,int& iso_y){
	iso_x = ( cart_x - cart_y ) * this->ancho_por_celda()/2;
	iso_y = ( cart_x + cart_y)* this->altura_por_celda()/2;
	printf("Iso_x: %d\n", iso_x);
	printf("Iso_y: %d\n", iso_y);
	}

void Vista::transformar_isometrica_cartesiana(int iso_x,int iso_y,int& cart_x,int& cart_y){
	cart_x= ( iso_x/ this->ancho_por_celda() + iso_y/ this->altura_por_celda() )  ;
	cart_y = ( iso_y/ this->altura_por_celda() - iso_x/ this->ancho_por_celda() );
	printf("Cart_x: %d\n", cart_x);
	printf("Cart_y: %d\n", cart_y);

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
	delete modelo;
	delete pasto;

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
void Vista::detectar_mouse_borde(){
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		int mov_pantalla_x = 100, mov_pantalla_y = 100;
		if ((mouse_x < mov_pantalla_x)){
			//printf("izquierda \n");
		}
		if(mouse_x > (SCREEN_WIDTH - mov_pantalla_x)){
			//printf("derecha\n");
		}
		if(mouse_y < mov_pantalla_y){
			//printf("alto\n");
		}
		if(mouse_y > (SCREEN_HEIGHT - mov_pantalla_y) ){
			//printf("abajo\n");
		} else {
			//printf("in\n");
		}
}

int Vista::run() { //Main loop flag
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	this->personaje->set_posicion_default(200,200);
	this->pasto->set_posicion_default(200,200);
	int mov_x=200, mov_y=200 ;

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
				SDL_GetMouseState(&mov_x, &mov_y);


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
		this->personaje->mover(mov_x, mov_y);



		//Update screen
		SDL_RenderPresent(gRenderer);


	}
	return 0;
}


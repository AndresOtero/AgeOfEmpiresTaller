/*
 * Vista.cpp
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include "Vista.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <memory>

#include "../ModeloSrc/Modelo.h"
#include "Dibujo.h"
#include "DibujoPersonaje.h"



//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 700;

Vista::Vista(shared_ptr<Modelo>  modelo) {
	this -> modelo = modelo;
	this->referencia_mapa_x=0;
	this->referencia_mapa_y=0;
	this->velocidad_de_scroll=0.001;
	this->sensibilidad_de_scroll=100;
}

int Vista::altura_por_celda(){
	return 124;
	//devuelve alto de imagen
}

int Vista::ancho_por_celda(){
	return 249;
	//devuelve ancho de imagen

}


void Vista::transformar_isometrica_pantalla(int iso_x,int iso_y,int& pant_x,int& pant_y){
	pant_x = (( iso_x - iso_y ) * this->ancho_por_celda())/2;
	pant_y =(( iso_x + iso_y)*  this->altura_por_celda()) /2;
}

void Vista::transformar_pantalla_isometrica(int pant_x,int pant_y,int& iso_x,int& iso_y){
	float termino_x=  ( (float)pant_x/ (this->ancho_por_celda()/2)) ;
	float termino_y= ( (float)pant_y/ (this->altura_por_celda()/2) );
	iso_x= (termino_x+ termino_y-1)/2;//MAGIA NEGRA
	iso_y = (termino_y - termino_x+1)/2;//En serio no se porque funciona
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
			gRenderer = SDL_CreateRenderer(&(*gWindow), -1,
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
	this -> factory=shared_ptr<FactoryDibujo> ( new FactoryDibujo(gRenderer));
	return success;
}
bool Vista::loadMedia() {

	/**Creo el dibujo del pasto**/
	vector<int> v1d={0,0,249,124};/**(X,Y,Ancho,Alto)**/
	this->factory->crear_dibujo("img/isometric_tile_1.png",v1d);
	dibujo_t pasto_id=this->factory->ultimo_dibujo();

	/**Creo el dibujo del castillo**/
	v1d={0,0,368,345};
	this->factory->crear_dibujo("img/Sprites/castle.png",v1d);
	dibujo_t castillo=this->factory->ultimo_dibujo();

	/**Dibujo el mapa**/
	int largo=this->modelo->get_alto_mapa();
	int ancho=this->modelo->get_ancho_mapa();
	vector<dibujo_t> filas(ancho,pasto_id);
	vector<vector<dibujo_t>> dibujos (largo,filas);
	dibujos[2][2]=castillo;
	this->modelo->setDibujoMapa(dibujos);
	shared_ptr<Dibujo> pasto=this->factory->get_dibujo(pasto_id);


	//creo dibujo
	shared_ptr<DibujoPersonaje> personaje(new DibujoPersonaje());
	this->personaje = personaje;

	//Load sprite sheet texture
	if (!this->personaje->cargar_archivo("img/foo.png", gRenderer)) {
		printf("Failed to load walking animation texture!\n");
	} else {
		//Set sprite clips
		this->personaje->set_cantidad_de_imagenes(4);
		for (int i = 0; i < 4; i++) {
			this->personaje->set_imagen(i, i * 64, 0, 64, 205);
		}
	}
	return true;
}
Vista::~Vista() {


	//Destroy window
	 SDL_DestroyWindow( gWindow);
	SDL_DestroyRenderer(gRenderer);


	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
void Vista::detectar_mouse_borde(){
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		int mov_pantalla_x = sensibilidad_de_scroll, mov_pantalla_y = sensibilidad_de_scroll;
		if ((mouse_x < mov_pantalla_x)){
			float vel=this->velocidad_de_scroll*(mov_pantalla_x-mouse_x);
			this->referencia_mapa_x+=vel;
			printf("izquierda \n");
			printf("%g\n",this->referencia_mapa_x);

		}
		if(mouse_x > (SCREEN_WIDTH - mov_pantalla_x)){
			float vel=this->velocidad_de_scroll*(mouse_x-(SCREEN_WIDTH - mov_pantalla_x));
			this->referencia_mapa_x-=vel;
			printf("derecha\n");
			printf("%g\n",this->referencia_mapa_x);

		}
		if(mouse_y < mov_pantalla_y){
			float vel=this->velocidad_de_scroll*(mov_pantalla_y-mouse_y);
			this->referencia_mapa_y+=vel;
			printf("\n alto\n");
			printf("%g\n",this->referencia_mapa_y);
		}
		if(mouse_y > (SCREEN_HEIGHT - mov_pantalla_y) ){
			float vel=this->velocidad_de_scroll*(mouse_y-(SCREEN_HEIGHT - mov_pantalla_y));
			this->referencia_mapa_y-=vel;
			printf("abajo\n");
			printf("%g\n",this->referencia_mapa_y);

		} else {
			printf("in\n");
		}
}

int Vista::run() { //Main loop flag
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	this->personaje->set_posicion_default(200,200);
	int mov_x=200, mov_y=200 ;

	//While application is running
	while (!quit) {
		float tiempo_actual,tiempo_viejo=0;
		tiempo_viejo=SDL_GetTicks();
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
		SDL_SetRenderDrawColor(gRenderer, 0, 0,0, 0);
		SDL_RenderClear(gRenderer);

		//Render current frame

		dibujar_mapa();
		this->personaje->render(gRenderer);
		this->personaje->set_velocidad(10);
		this->personaje->mover(mov_x, mov_y);
		int mouse_x,mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		int x,y;
		this->transformar_pantalla_isometrica(mouse_x,mouse_y,x,y);/**
		printf("iso_x: %d\n",mouse_x);
		printf("iso_y: %d\n",mouse_y);
		printf("Cart_x: %d\n", x);
		printf("Cart_y: %d\n", y);**/
		this->detectar_mouse_borde();
		//Update screen
		SDL_RenderPresent(gRenderer);

		tiempo_actual= SDL_GetTicks();
		//printf("%f",tiempo_actual-tiempo_viejo);
		tiempo_viejo=tiempo_actual;

	}

	return 0;
}

void Vista::dibujar_mapa() {
	int x_imagen,y_imagen;
	int x_mapa=referencia_mapa_x,y_mapa=referencia_mapa_y;
	int imprimir=100;
	vector<vector<dibujo_t>> dibujo_mapa=this->modelo->dibujar(0,0,100,100);
	for (int i=0; i<imprimir; i++) {
		for (	int j=0; j<i+1; j++) {
			int coord_x=x_mapa+j;
			int coord_y=y_mapa+i-j;
			if((coord_x<this->modelo->get_ancho_mapa())&&(coord_y<this->modelo->get_alto_mapa())&&(coord_x>=0)&&(coord_y>=0)){
				size_t n_imagen=dibujo_mapa[coord_x][coord_y];
				shared_ptr<Dibujo> dibujo=this->factory->get_dibujo(n_imagen);
				this->transformar_isometrica_pantalla((coord_x),(coord_y),x_imagen,y_imagen);
				dibujo->set_posicion_default(x_imagen, y_imagen);
				dibujo->render(gRenderer);
			}
		}
	}


}

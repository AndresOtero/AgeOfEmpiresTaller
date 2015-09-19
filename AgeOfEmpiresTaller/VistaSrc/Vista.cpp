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
enum bordes {X_START,Y_START,Y_MIN,X_MAX,Y_MAX};


//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 700;

Vista::Vista(shared_ptr<Modelo>  modelo) {
	this -> modelo = modelo;
	this->referencia_mapa_x=0;
	this->referencia_mapa_y=0;
	this->velocidad_de_scroll=0.001;
	this->sensibilidad_de_scroll=100;
	this->transformador=shared_ptr<CambioDeCoordendas>(new CambioDeCoordendas(ancho_por_celda(),altura_por_celda()));
}

int Vista::altura_por_celda(){
	return 124;
	//devuelve alto de imagen
}

int Vista::ancho_por_celda(){
	return 249;
	//devuelve ancho de imagen

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
	if (!this->personaje->cargar_archivo("img/tipo_moviendose.png", gRenderer)) {
		printf("Failed to load walking animation texture!\n");
	} else {
		//Set sprite clips
		vector<size_t> movimientos={IZQUIERDA,DIAGONAL_IZQUIERDA_ARRIBA,ARRIBA,DIAGONAL_DERECHA_ARRIBA,DERECHA,DIAGONAL_DERECHA_ABAJO,ABAJO,DIAGONAL_IZQUIERDA_ABAJO};
		this->personaje->set_cantidad_de_movimientos(8);
		for(int i=0;i<8;i++){
			this->personaje->set_cantidad_de_imagenes(i,8);
		}
		for (int i = 0; i < 8; i++) {
			for(int j=0;j<8;j++){
				this->personaje->set_imagen(movimientos[i],j, j * 128, i*128, 128, 128);
			}
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
void Vista::detectar_mouse_borde() {
	int mouse_x, mouse_y;
	//int actual_x, actual_y;
	//float mov_x, mov_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);


	//int mov_pantalla_x = sensibilidad_de_scroll, mov_pantalla_y =sensibilidad_de_scroll;
	/**
	if ((mouse_x < mov_pantalla_x)) {
		this->transformar_isometrica_pantalla(iso_x, iso_y, actual_x, actual_y);
		float vel = this->velocidad_de_scroll * (mov_pantalla_x - mouse_x);
		actual_x -= vel;
		referencia_mapa_x = ref_x;
		referencia_mapa_y = ref_y;
		printf("izquierda \n");
		printf("X: %g\n", this->referencia_mapa_x);
		printf("Y: %g\n", this->referencia_mapa_y);

	}
	if ((mouse_x > (SCREEN_WIDTH - mov_pantalla_x))) {
		this->transformar_isometrica_pantalla(iso_x, iso_y, actual_x, actual_y);
		float vel = this->velocidad_de_scroll
				* (mouse_x - (SCREEN_WIDTH - mov_pantalla_x));
		actual_x += vel;
		float ref_x = referencia_mapa_x;
		float ref_y = referencia_mapa_y;
		this->transformar_pantalla_isometrica(actual_x, actual_y, ref_x, ref_y);
		referencia_mapa_x = ref_x;
		referencia_mapa_y = ref_y;
		printf("derecha \n");
		printf("X: %g\n", this->referencia_mapa_x);
		printf("Y: %g\n", this->referencia_mapa_y);

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

		}**/
		/**if((mouse_y < (SCREEN_HEIGHT - mov_pantalla_y))&&(mouse_y > mov_pantalla_y)&&(mouse_x < (SCREEN_WIDTH - mov_pantalla_x)&&(mouse_x > mov_pantalla_x)) ){
			printf("in\n");
		}**/
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
		//float tiempo_actual,tiempo_viejo=0;
		//tiempo_viejo=SDL_GetTicks();
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
		this->transformador->transformar_pantalla_isometrica(mouse_x,mouse_y,x,y);
		printf("iso_x: %d\n",mouse_x);
		printf("iso_y: %d\n",mouse_y);
		x+=referencia_mapa_x;
		y+=referencia_mapa_y;
		printf("Cart_x: %d\n", x);
		printf("Cart_y: %d\n", y);
		this->detectar_mouse_borde();
		//Update screen
		SDL_RenderPresent(gRenderer);

		//tiempo_actual= SDL_GetTicks();
		//printf("%f",tiempo_actual-tiempo_viejo);
		//tiempo_viejo=tiempo_actual;

	}

	return 0;
}
vector<int> Vista::calcular_bordes(){
	/**
	Credit:
	http://www.java-gaming.org/index.php?topic=24922.0
	**/
	int pantalla_refencia_x,pantalla_refencia_y;
	this->transformador->transformar_isometrica_pantalla(referencia_mapa_x,referencia_mapa_y,pantalla_refencia_x,pantalla_refencia_y);
	int x_start,y_start;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x,pantalla_refencia_y,x_start,y_start);
	x_start=x_start-2;
	int x_max,y;
	x_max+=2;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x+SCREEN_WIDTH,pantalla_refencia_y+SCREEN_HEIGHT,x_max,y);
	int x,y_max;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x,pantalla_refencia_y+SCREEN_HEIGHT,x,y_max);
	y_max=y_max+2;
	int y_min;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x+SCREEN_WIDTH,pantalla_refencia_y,x,y_min);
	y_min-=2;
	vector<int> bordes={x_start,y_start,y_min,x_max,y_max};
	return bordes;
}
void Vista::dibujar_mapa() {
	/**Bordes**/
	vector<int> bordes=this->calcular_bordes();
	/****/
	int x_start=bordes[X_START],y_start=bordes[Y_START],y_min=bordes[Y_MIN],x_max=bordes[X_MAX],y_max=bordes[Y_MAX];
	int x_imagen,y_imagen;
	bool llego_min_y=false,llego_max_x=false;
	int y_offset_max=0,y_offset_min=0;
	vector<vector<dibujo_t>> dibujo_mapa=this->modelo->dibujar(0,0,100,100);

	for (int coord_x=x_start; coord_x<x_max; coord_x++) {
		for (	int coord_y=y_start-y_offset_min; coord_y<y_start+y_offset_max;coord_y++) {
			if((coord_x<this->modelo->get_ancho_mapa())&&(coord_y<this->modelo->get_alto_mapa())&&(coord_x>=0)&&(coord_y>=0)){
				size_t n_imagen=dibujo_mapa[coord_x][coord_y];
				shared_ptr<Dibujo> dibujo=this->factory->get_dibujo(n_imagen);
				this->transformador ->transformar_isometrica_pantalla(coord_x-referencia_mapa_x,coord_y-referencia_mapa_y,x_imagen,y_imagen);
				dibujo->set_posicion_default(x_imagen, y_imagen);
				dibujo->render(gRenderer);
			}
		}
		if(!llego_min_y){
			y_offset_min++;
			if(((y_start-y_offset_min)==y_min)){
				llego_min_y=true;
			}
		}else{
			y_offset_min--;
		}
		if (!llego_max_x) {
			y_offset_max++;
			if (((y_start + y_offset_max) == y_max)) {
				llego_min_y = true;
			}
		} else {
			y_offset_max--;
		}
	}


}

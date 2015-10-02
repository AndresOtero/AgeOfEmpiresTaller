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
#include <unistd.h>
#include <plog/Log.h>


#include "../ModeloSrc/Modelo.h"
#include "Dibujo.h"
#include "DibujoPersonaje.h"
enum bordes {X_START,Y_MIN,X_MAX,Y_MAX};
#define DIMENSIONES 2
#define ANIMACIONES 5
#define MOVIMIENTOS 8
#define CANTIDAD_DE_IMAGENES 8
#define ANCHO_BASE  249
#define ALTO_BASE  124
#define ANCHO_ANIMACION 128
#define ANCHO_PERSONAJE 64
#define ALTO_PERSONAJE 64

Vista::Vista(Modelo* modelo) {
	this -> modelo = modelo;
	this->pantalla= modelo->juego->pantalla;
	this->referencia_mapa_x=this->modelo->juego->escenario->protagonista->getReferenciaMapaX()-1;// desde el punto del mapa donde se dibuja
	this->referencia_mapa_y=this->modelo->juego->escenario->protagonista->getReferenciaMapaY()-1;
	this->velocidad_de_scroll=0.25;
	this->margen_scroll=modelo->juego->conf->get_margen_scroll();
	this->transformador=shared_ptr<CambioDeCoordendas>(new CambioDeCoordendas(ancho_por_celda(),altura_por_celda()));
}

int Vista::altura_por_celda(){
	return ALTO_BASE;
	//devuelve alto de imagen
}

int Vista::ancho_por_celda(){
	return ANCHO_BASE;
	//devuelve ancho de imagen

}

bool Vista::init() {
	bool success = true;
	this -> gRenderer = NULL;
	this -> gWindow = NULL;
	plog::init(plog::warning, "Log.txt" );
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		LOG_WARNING << "No pudo inicializarse SDL. SDL Error: %s\n", SDL_GetError();

		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1S")) {
			LOG_WARNING << "Atencion no funciona SDL_HINT_RENDER_SCALE_QUALITY \n";
		}

		//Create window
		gWindow = SDL_CreateWindow("Age of empires", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,  pantalla->getAncho(),pantalla->getAlto(),
				SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			LOG_WARNING << "No se pudo crear la ventana .SDL Error: %s\n",
					SDL_GetError();

			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(&(*gWindow), -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				LOG_WARNING << "No se pudo crear el renderer .SDL Error: %s\n",
									SDL_GetError();
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					LOG_WARNING << "No se pudo crear el cargador de imagenes .SDL Error: %s\n",
										SDL_GetError();
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

	Entidad* entidadPasto = this->modelo->juego->escenario->getTexturaDefault();

	vector<int> v1dPasto={0,0,ANCHO_BASE,ALTO_BASE};
	this->factory->crear_dibujo_estatico(entidadPasto->objetoMapa->imagen,v1dPasto);
	dibujo_t pasto_id=this->factory->ultimo_dibujo();
	delete entidadPasto;
	std::map<std::string, ObjetoMapa*> ::iterator it;
	std::map<std::string, dibujo_t> hashDibujos;

	//***********DIBUJOS (TIPOS EN YAML)*****************
	vector<vector<dibujo_t>>v2d=vector<vector<dibujo_t>>(ANIMACIONES);
	for(int i=0;i<ANIMACIONES;i++){
		v2d[i]={i*ANCHO_ANIMACION,0};
	}
	for ( it = modelo->juego->tipos.begin(); it !=modelo->juego->tipos.end(); it++ )
	{
	     ObjetoMapa* tipo = it->second;
	     vector<int> v1d ={tipo->pixelsReferencia->x,tipo->pixelsReferencia->y};
	     if(tipo->fps == 0){
	    	 this->factory->crear_dibujo_estatico(tipo->imagen,v1d);
	     }else{
	    	 this->factory->crear_dibujo_animado(tipo->imagen,v2d,tipo->fps, tipo->delay);
	     }
	     dibujo_t dibujo_id=this->factory->ultimo_dibujo();
	     hashDibujos[tipo->nombre] = dibujo_id;
	}

	/**Dibujo el mapa**/
	int largo=this->modelo->get_alto_mapa();
	int ancho=this->modelo->get_ancho_mapa();
	vector<dibujo_t> filas(ancho,pasto_id);
	vector<vector<dibujo_t>> tiles (largo,filas);
	vector<dibujo_t> filas_escenario(ancho,0);
	vector<vector<dibujo_t>> escenario (largo,filas_escenario);


	//***********DIBUJOS (ENTIDADES ESTATICAS Y DINAMICAS EN YAML)*****************
	for (unsigned i = 0; i < this->modelo->juego->escenario->entidades.size(); i++){
			Entidad* entidad = this->modelo->juego->escenario->entidades[i];
			escenario[entidad->posicion->getX()][entidad->posicion->getY()]=hashDibujos[entidad->objetoMapa->nombre];
	}
	modelo->setDibujoMapa(escenario,tiles);
	shared_ptr<Dibujo> pasto=this->factory->get_dibujo(pasto_id);

	vector<int> movimientos={IZQUIERDA,DIAGONAL_IZQUIERDA_ARRIBA,ARRIBA,DIAGONAL_DERECHA_ARRIBA,DERECHA,DIAGONAL_DERECHA_ABAJO,ABAJO,DIAGONAL_IZQUIERDA_ABAJO};
	vector<vector<vector<dibujo_t>>> v3d=vector<vector<vector<dibujo_t>>>(8);
	for (int i = 0; i < CANTIDAD_DE_MOVIMIENTOS; i++) {
		v3d[i] = vector<vector<dibujo_t>>(CANTIDAD_DE_MOVIMIENTOS);
		for (int j = 0; j < CANTIDAD_DE_IMAGENES; j++) {
			vector<dibujo_t> v ={ j * ANCHO_PERSONAJE, i * ALTO_PERSONAJE, ANCHO_PERSONAJE, ALTO_PERSONAJE };
			v3d[i][j]=v;
		}
	}
	vector<int> imagenes= vector<int>(CANTIDAD_DE_MOVIMIENTOS,CANTIDAD_DE_IMAGENES);


	//TOMA ENTIDAD ANIMADA SOLO COMO LOS DATOS QUE SACAS DEL YAMLS SINO
	Personaje* protagonista = this->modelo->juego->escenario->protagonista;
	Configuracion* configuracion = this->modelo->juego->conf;

	this->factory->crear_dibujo_personaje(protagonista->objetoMapa->imagen,CANTIDAD_DE_MOVIMIENTOS,imagenes,v3d,protagonista->objetoMapa->fps,configuracion->get_vel_personaje());
	dibujo_t pers=this->factory->ultimo_dibujo();
	protagonista->setDibujo(pers);
	protagonista->setVelocidad(configuracion->get_vel_personaje()/10.0);

	modelo->agregarPersonaje(protagonista);



	return true;
}
void Vista::mover_referencia(double vel_x,double vel_y) {
		double ref_x, ref_y;

		this->transformador->transformar_pantalla_isometrica(vel_x,vel_y,ref_x,ref_y);
		ref_x+=referencia_mapa_x;
		ref_y+=referencia_mapa_y;

		if(adentro_del_mapa(ref_x,ref_y)){
			referencia_mapa_x=ref_x;
			referencia_mapa_y=ref_y;
		}

}

void Vista::detectar_mouse_borde() {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	int mov_pantalla_x = margen_scroll, mov_pantalla_y = margen_scroll;

	if ((mouse_x < mov_pantalla_x)) {
		double vel_x = (-1)*this->velocidad_de_scroll
				* (mov_pantalla_x-mouse_x);
		mover_referencia(vel_x, 0);

	}
	if ((mouse_x > (this->pantalla->getAncho() - mov_pantalla_x))) {
		double vel_x = this->velocidad_de_scroll
				* (mouse_x - (this->pantalla->getAncho() - mov_pantalla_x));
		mover_referencia(vel_x, 0);

	}
	if (mouse_y < mov_pantalla_y) {
		double vel_y = (-1)*this->velocidad_de_scroll * (mov_pantalla_y - mouse_y);

		mover_referencia(0, vel_y);


	}
	if (mouse_y > (this->pantalla->getAlto() - mov_pantalla_y)) {


		double vel_y = this->velocidad_de_scroll
				* (mouse_y - (this->pantalla->getAlto() - mov_pantalla_y));

		mover_referencia(0, vel_y);


	}
}

int Vista::run() {
	bool quit = false;
	SDL_Event e;
	int mov_x=0, mov_y=0;
	Personaje* pers=this->modelo->devolverPersonaje();
	this->transformador->transformar_isometrica_pantalla(pers->getReferenciaMapaX()-referencia_mapa_x,pers->getReferenciaMapaY()-referencia_mapa_y,mov_x,mov_y);

	double personaje_x=pers->getReferenciaMapaX(),personaje_y=pers->getReferenciaMapaY();

	while (!quit) {
		double tiempo_actual,tiempo_viejo=0;
		tiempo_viejo=SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&mov_x, &mov_y);
				this->transformador->transformar_pantalla_isometrica(mov_x,mov_y,personaje_x,personaje_y);
				personaje_x+=referencia_mapa_x;
				personaje_y+=referencia_mapa_y;

			}
			if (e.type == SDL_KEYDOWN) {
	            SDL_Keycode keyPressed = e.key.keysym.sym;

	            switch (keyPressed){
	               case SDLK_ESCAPE:
	                  quit = true;
	                  break;
	               case SDLK_r:
	            	   return true;
	            }
	         }
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0,0, 0);
		SDL_RenderClear(gRenderer);


		dibujar_mapa();
		dibujar_personaje(personaje_x,personaje_y);

		int mouse_x,mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);

		double x,y;
		this->transformador->transformar_pantalla_isometrica(mouse_x,mouse_y,x,y);
		x+=referencia_mapa_x;
		y+=referencia_mapa_y;
		printf("Adonde estoy: x: %g, y: %g \n",x,y);

		this->detectar_mouse_borde();
		SDL_RenderPresent(gRenderer);


		usleep((40 - (tiempo_actual-tiempo_viejo))*1000);
		tiempo_actual= SDL_GetTicks();
		tiempo_viejo=tiempo_actual;
	}

	return false;
}
vector<int> Vista::calcular_bordes(){
	/**
	Fuente:
	http://www.java-gaming.org/index.php?topic=24922.0
	**/
	int pantalla_refencia_x,pantalla_refencia_y;
	this->transformador->transformar_isometrica_pantalla(referencia_mapa_x,referencia_mapa_y,pantalla_refencia_x,pantalla_refencia_y);
	int x_start,y_start;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x,pantalla_refencia_y,x_start,y_start);
	x_start=x_start-2;
	int x_max,y;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x+pantalla->getAncho(),pantalla_refencia_y+pantalla->getAlto(),x_max,y);
	x_max+=2;
	int x,y_max;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x,pantalla_refencia_y+pantalla->getAlto(),x,y_max);
	y_max=y_max+2;
	int y_min;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x+pantalla->getAncho(),pantalla_refencia_y,x,y_min);
	y_min-=2;
	vector<int> bordes={x_start,y_min,x_max,y_max};
	return bordes;
}

bool Vista::adentro_del_mapa(double coord_x,double coord_y){
	return ((coord_x < this->modelo->get_ancho_mapa())
			&& (coord_y < this->modelo->get_alto_mapa())
			&& (coord_x > 0) && (coord_y >0));
}

bool Vista::adentro_del_mapa(int coord_x,int coord_y){
	return ((coord_x < this->modelo->get_ancho_mapa())
			&& (coord_y < this->modelo->get_alto_mapa())
			&& (coord_x >= 0) && (coord_y >= 0));
}

void Vista::dibujar_personaje(double mover_x, double mover_y) {
	Personaje* personaje=this->modelo->devolverPersonaje();
	int img_personaje_x,img_personaje_y ;
	this->transformador->transformar_isometrica_pantalla(
			personaje->getReferenciaMapaX() - referencia_mapa_x,
			personaje->getReferenciaMapaY() - referencia_mapa_y, img_personaje_x,
			img_personaje_y);
	shared_ptr<DibujoPersonaje> dibujo_pers = dynamic_pointer_cast<
			DibujoPersonaje>(this->factory->get_dibujo(personaje->dibujar()));
	dibujo_pers->set_posicion_default(img_personaje_x, img_personaje_y);

	if (!adentro_del_mapa(mover_x - 1.5, mover_y + 0.5)) { //Hardcoding
		mover_x = personaje->getReferenciaMapaX();
		mover_y = personaje->getReferenciaMapaY();
	}
	int adonde_va_x, adonde_va_y;
	this->transformador->transformar_isometrica_pantalla(
			mover_x - referencia_mapa_x, mover_y - referencia_mapa_y,
			adonde_va_x, adonde_va_y);
	dibujo_pers->elegir_frame((adonde_va_x - img_personaje_x),
			(adonde_va_y - img_personaje_y));

	modelo->mover_personaje(mover_x, mover_y);
	dibujo_pers->render(gRenderer);
}

void Vista::dibujar_mapa() {
	/**Bordes**/
	vector<int> bordes = this->calcular_bordes();
	/****/
	int x_start = bordes[X_START], y_min =
			bordes[Y_MIN], x_max = bordes[X_MAX], y_max = bordes[Y_MAX];
	int x_imagen, y_imagen;

	for (int dim = 0; dim < DIMENSIONES; dim++) {
		int max=abs(x_max)+abs(y_max);
		int i=0,j=0;
		for ( i = x_start-1; i<max; i++) {
			for ( j = y_min ;j<i; j++) {
				int coord_x=i-j;
				int coord_y=j;
				if ((adentro_del_mapa(coord_x,coord_y))&&(coord_x<x_max)&&(coord_y<y_max)) {
					size_t n_imagen = this->modelo->dibujar(dim,coord_x,coord_y);
					shared_ptr<Dibujo> dibujo = this->factory->get_dibujo(n_imagen);
					if (dibujo != NULL) {
					/**ATENCION MUY HARDCODEADO**/
					this->transformador->transformar_isometrica_pantalla(
							coord_x - referencia_mapa_x+dim*1.5,
							coord_y - referencia_mapa_y-dim*0.5, x_imagen, y_imagen);
					dibujo->set_posicion_default(x_imagen, y_imagen);
					dibujo->render(gRenderer);
					}
				}
			}
		}
	}
}

Vista::~Vista() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

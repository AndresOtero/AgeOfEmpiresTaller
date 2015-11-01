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
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <memory>
#include <unistd.h>
#include <plog/Log.h>


#include "../ModeloSrc/Modelo.h"
#include "Dibujo.h"
#include "DibujoPersonaje.h"
enum bordes {X_START,Y_MIN,X_MAX,Y_MAX};
#define ESCENARIO 1
#define TILES 0
#define DIMENSIONES 2
#define ANIMACIONES 5
#define MOVIMIENTOS 8
#define CANTIDAD_DE_IMAGENES 8
#define ANCHO_BASE  249
#define ALTO_BASE  124
#define ANCHO_ANIMACION 128
#define ANCHO_PERSONAJE 64
#define ALTO_PERSONAJE 64
#define OFFSET 1


Vista::Vista(Modelo* modelo,GameControllerCliente* gameController) {
	this -> modelo = modelo;
	this->pantalla= modelo->juego->pantalla;
	this->velocidad_de_scroll=0.25;
	this->margen_scroll=modelo->juego->conf->get_margen_scroll();
	this->transformador=shared_ptr<CambioDeCoordendas>(new CambioDeCoordendas(ancho_por_celda(),altura_por_celda()));
	shared_ptr<Barra> barra(new Barra(modelo,&referencia_mapa_x,&referencia_mapa_y));
	this->barra=barra;
	this->gameController = gameController;
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
				else{
					//Initialize SDL_ttf
					if( TTF_Init() == -1 ){
						LOG_WARNING << "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError();
						success = false;
					}
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

	//***********DIBUJOS DINAMICOS *****************
	vector<vector<dibujo_t>>v2d=vector<vector<dibujo_t>>(ANIMACIONES);
	for(int i=0;i<ANIMACIONES;i++){
		v2d[i]={i*ANCHO_ANIMACION,0};
	}
	//***********DIBUJOS PERSONAJES *****************
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
	//**************************************************
		Personaje* protagonista = this->modelo->juego->escenario->protagonista;
		Configuracion* configuracion = this->modelo->juego->conf;
	for ( it = modelo->juego->tipos.begin(); it !=modelo->juego->tipos.end(); it++ )
	{
	     ObjetoMapa* tipo = it->second;
	     vector<int> v1d ={tipo->pixelsReferencia->x,tipo->pixelsReferencia->y};
	     if(tipo->fps == 0){
	    	 this->factory->crear_dibujo_estatico(tipo->imagen,v1d);
	     }else if(tipo->delay!=0){
	    	 this->factory->crear_dibujo_animado(tipo->imagen,v1d,v2d,tipo->fps, tipo->delay);
	     }else{
	    	this->factory->crear_dibujo_personaje(tipo->imagen,CANTIDAD_DE_MOVIMIENTOS,imagenes,v3d,tipo->fps);//el ultimo parametro es velocidad
	    	dibujo_t pers=this->factory->ultimo_dibujo();
	    	protagonista->setDibujo(pers);//OJO
	     }
	     dibujo_t dibujo_id=this->factory->ultimo_dibujo();
	     hashDibujos[tipo->nombre] = dibujo_id;
	}
	this->factory->setHashDibujos(hashDibujos);
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
	modelo->setDibujoMapa(escenario,tiles);//MEZCLA VISTA CON MODELO



	this->barra->load(gRenderer,"font.ttf",this->ancho_por_celda(),this->altura_por_celda());


	return true;
}

dibujo_t Vista::crearPersonaje(string tipo) {
	//***********DIBUJOS PERSONAJES *****************
	vector<int> movimientos = { IZQUIERDA, DIAGONAL_IZQUIERDA_ARRIBA, ARRIBA,
			DIAGONAL_DERECHA_ARRIBA, DERECHA, DIAGONAL_DERECHA_ABAJO, ABAJO,
			DIAGONAL_IZQUIERDA_ABAJO };
	vector<vector<vector<dibujo_t>>> v3d=vector<vector<vector<dibujo_t>>>(8);
	for (int i = 0; i < CANTIDAD_DE_MOVIMIENTOS; i++) {
		v3d[i] = vector<vector<dibujo_t>>(CANTIDAD_DE_MOVIMIENTOS);
		for (int j = 0; j < CANTIDAD_DE_IMAGENES; j++) {
			vector<dibujo_t> v = { j * ANCHO_PERSONAJE, i * ALTO_PERSONAJE,
					ANCHO_PERSONAJE, ALTO_PERSONAJE };
			v3d[i][j] = v;
		}
	}
	vector<int> imagenes = vector<int>(CANTIDAD_DE_MOVIMIENTOS,
			CANTIDAD_DE_IMAGENES);
	/*********************************************************/
	ObjetoMapa* obj=this->modelo->juego->tipos[tipo];
	this->factory->crear_dibujo_personaje(obj->imagen,
			CANTIDAD_DE_MOVIMIENTOS, imagenes, v3d, obj->fps); //el ultimo parametro es velocidad
	dibujo_t pers = this->factory->ultimo_dibujo();
	return pers;
}

void Vista::mover_referencia(double vel_x,double vel_y) {
		double ref_x, ref_y;

		this->transformador->transformar_pantalla_isometrica(vel_x,vel_y,ref_x,ref_y);
		ref_x+=referencia_mapa_x;
		ref_y+=referencia_mapa_y;

		if(adentro_del_mapa(ref_x+1,ref_y+1)){
			referencia_mapa_x=ref_x;
			referencia_mapa_y=ref_y;
		}
}
void Vista::setear_referencia(double ref_x,double ref_y) {
		referencia_mapa_x=ref_x-OFFSET;
		referencia_mapa_y=ref_y-OFFSET;
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

bool Vista::run() {
	bool quit = false;
	SDL_Event e;
	int mov_x=0, mov_y=0;
	//this->transformador->transformar_isometrica_pantalla(pers->getReferenciaMapaX()-referencia_mapa_x,pers->getReferenciaMapaY()-referencia_mapa_y,mov_x,mov_y);
	double personaje_x,personaje_y;

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_RIGHT) {
				SDL_GetMouseState(&mov_x, &mov_y);
				this->transformador->transformar_pantalla_isometrica(mov_x,
						mov_y, personaje_x, personaje_y);
				this->corregir_referencia_coordenadas_pantalla_mapa(personaje_x,
						personaje_y);
				Posicion p=Posicion(personaje_x,personaje_y);
				//le envia al server que cambie el destino
				if(this->modelo->devolverPersonajeSeleccionado()->getNombreJugador()==this->modelo->nombreJugador())
				{

					this->gameController->cambiar_destino_personaje(this->gameController->nombreJugador() ,personaje_x, personaje_y);
				}
				//modelo->cambiar_destino_personaje(personaje_x,personaje_y);
			}
			if (e.button.button == SDL_BUTTON_LEFT) {
				double a, b;
				SDL_GetMouseState(&mov_x, &mov_y);
				this->transformador->transformar_pantalla_isometrica(mov_x,
						mov_y, a, b);
				this->corregir_referencia_coordenadas_pantalla_mapa(a, b);
				//printf("Donde toco : x: %g, y: %g \n",a,b);
				this->barra->setDisplay(modelo->seleccionar(a, b));
				//printf("Selecciono\n");
			}
		}
		if (e.type == SDL_KEYDOWN) {
			SDL_Keycode keyPressed = e.key.keysym.sym;

			switch (keyPressed) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_r:
				return true;
			case SDLK_c:
				if (modelo->devolverPersonajeSeleccionado()) {
					modelo->congelarPersonaje(modelo->nombreJugador());
				}
				break;
			case SDLK_d:
				if (modelo->devolverPersonajeSeleccionado()) {
					modelo->descongelarPersonaje(modelo->nombreJugador());
				}
				break;
			}
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	modelo->actualizarMapa(); //lo tiene que hacer el server
	dibujar_mapa();
	dibujar_barra();
	detectar_mouse_borde();
	SDL_RenderPresent(gRenderer);

	return quit;
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
void Vista::corregir_referencia_coordenadas_pantalla_mapa(double& coord_x, double& coord_y){
	coord_x+=referencia_mapa_x-0.5;
	coord_y+=referencia_mapa_y+0.5;
}
void Vista::corregir_referencia_coordenadas_mapa_pantalla(double& coord_x, double& coord_y){
	coord_x+=(-referencia_mapa_x+0.5);
	coord_y+=(-referencia_mapa_y-0.5);
}


bool Vista::adentro_del_mapa(double coord_x,double coord_y){
	return ((coord_x < this->modelo->get_ancho_mapa())
			&& (coord_y < this->modelo->get_alto_mapa())
			&& (coord_x >= 0) && (coord_y >=0));
}

bool Vista::adentro_del_mapa(int coord_x,int coord_y){
	return ((coord_x < this->modelo->get_ancho_mapa())
			&& (coord_y < this->modelo->get_alto_mapa())
			&& (coord_x >= 0) && (coord_y >= 0));
}

void Vista::dibujar_personaje(Personaje* personaje) {
	int img_personaje_x, img_personaje_y;
	double personaje_x = personaje->getReferenciaMapaX();
	double personaje_y = personaje->getReferenciaMapaY();
	this->corregir_referencia_coordenadas_mapa_pantalla(personaje_x,
			personaje_y);
	this->transformador->transformar_isometrica_pantalla(personaje_x,
			personaje_y, img_personaje_x, img_personaje_y);
	shared_ptr<DibujoPersonaje> dibujo_pers = dynamic_pointer_cast<
			DibujoPersonaje>(this->factory->get_dibujo( this->factory->get_idDibujo(personaje->getNombreTipo())));


	dibujo_pers->set_posicion_default(img_personaje_x, img_personaje_y);
	Posicion destino = personaje->get_camino();
	double mover_x = destino.get_x_exacta();
	double mover_y = destino.get_y_exacta();
	if (!adentro_del_mapa(mover_x, mover_y)) {
		mover_x = personaje->getReferenciaMapaX();
		mover_y = personaje->getReferenciaMapaY();
	}
	if (personaje->estaCongelado()){
		dibujo_pers->congelar();
	}else{

		dibujo_pers->descongelar();
	}
	int adonde_va_x, adonde_va_y;
	Posicion adonde_va = personaje->get_camino();
	mover_x = adonde_va.get_x_exacta();
	mover_y = adonde_va.get_y_exacta();
	this->corregir_referencia_coordenadas_mapa_pantalla(mover_x, mover_y);
	this->transformador->transformar_isometrica_pantalla(mover_x, mover_y,
			adonde_va_x, adonde_va_y);
	dibujo_pers->elegir_frame((adonde_va_x - img_personaje_x),
			(adonde_va_y - img_personaje_y));
	dibujo_pers->render(gRenderer);

}

void Vista::dibujar_mapa() {
	/**Bordes**/
	vector<int> bordes = this->calcular_bordes();
	/****/
	int x_start = bordes[X_START], y_min = bordes[Y_MIN], x_max = bordes[X_MAX],
			y_max = bordes[Y_MAX];
	int x_imagen, y_imagen;

	for (int dim = 0; dim < DIMENSIONES; dim++) {
		int max = abs(x_max) + abs(y_max);
		int i = 0, j = 0;
		for (i = x_start - 1; i < max; i++) {
			for (j = y_min; j < i; j++) {
				int coord_x = i - j - 1;
				int coord_y = j;
				if ((adentro_del_mapa(coord_x, coord_y)) && (coord_x < x_max)
						&& (coord_y < y_max)) {
					//Cambio para dibujar agregados
					size_t n_imagen;
					if (dim==TILES){
						 n_imagen = this->modelo->dibujar(dim, coord_x,
													coord_y);//MEZCLA MODELO CON VISTA para dsps
					}else {
						n_imagen = this->factory->get_idDibujo(this->modelo->mapa->mostrar_entidad(coord_x,coord_y));
					}
					//fin cambio villero
					int oscuro = modelo->oscuridad(dim,coord_x,coord_y);
					shared_ptr<Dibujo> dibujo = this->factory->get_dibujo(
							n_imagen);

					if (this->modelo->devolverPersonaje(coord_x, coord_y)) {
						dibujar_personaje(
								this->modelo->devolverPersonaje(coord_x,
										coord_y));
					}
					if(dim==TILES){
						if(this->modelo->estaSeleccionada(coord_x,coord_y)){
							dibujo->iluminar();
						}
					}
					if (dibujo != NULL) {
						/*HARDCODE*/
						this->transformador->transformar_isometrica_pantalla(
								coord_x - referencia_mapa_x,
								coord_y - referencia_mapa_y, x_imagen,
								y_imagen);
						dibujo->set_posicion_default(x_imagen, y_imagen);

						if(oscuro == 1)
							dibujo->oscurecer();
							dibujo->setAnimar(false);
						if(oscuro != 1 && oscuro < 2){
							dibujo->setAnimar(true);
						}
						if(oscuro < 2){
							dibujo->render(gRenderer);
						}


						dibujo->resetear();
						dibujo->reiniciar(); //pone el color original
					}
				}
			}
		}
	}
}

void Vista::dibujar_barra(){
	//HARCODE deberia ser el personaje/jugador
	this->barra->actualizar(this->modelo->devolverTodosLosPersonajes()[0]);
	this->barra->render(gRenderer);
}

Vista::~Vista() {
	this->barra->closeFont();
	TTF_Quit();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

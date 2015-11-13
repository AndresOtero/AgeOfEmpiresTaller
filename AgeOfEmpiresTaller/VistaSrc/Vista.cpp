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
#define MOVIMIENTOS 8
#define CANTIDAD_DE_IMAGENES 8

#define ANCHO_ANIMACION 128

#define OFFSET 1


Vista::Vista(Modelo* modelo,GameControllerCliente* gameController) {
	this -> modelo = modelo;
	this->pantalla= modelo->juego->pantalla;
	this->velocidad_de_scroll=0.25;
	this->margen_scroll=modelo->juego->conf->get_margen_scroll();
	this->transformador=shared_ptr<CambioDeCoordendas>(new CambioDeCoordendas(ancho_por_celda(),altura_por_celda()));
	shared_ptr<Barra> barra(new Barra(modelo,&referencia_mapa_x,&referencia_mapa_y));
	this->barra=barra;
	shared_ptr<Dibujo> dibujo(new Dibujo());
	this->edificioACrear = dibujo;
	this->entidadACrear=NULL;
	this->gameController = gameController;
	this->esta_eligiendo=false;
}

int Vista::altura_por_celda(){
	return 44;
	//devuelv alto de imagen
}

int Vista::ancho_por_celda(){
	return 92;
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

	this->factory->crear_dibujo_tile(entidadPasto->objetoMapa->imagen);

	dibujo_t pasto_id=this->factory->ultimo_dibujo();
	delete entidadPasto;
	std::map<std::string, ObjetoMapa*> ::iterator it;
	std::map<std::string, dibujo_t> hashDibujos;

	Configuracion* configuracion = this->modelo->juego->conf;
	for ( it = modelo->juego->tipos.begin(); it !=modelo->juego->tipos.end(); it++ )
	{
	     ObjetoMapa* tipo = it->second;
	     vector<int> v1d ={tipo->pixelsReferencia->x,tipo->pixelsReferencia->y};
	     if(tipo->fps == 0){
	    	 this->factory->crear_dibujo_estatico(tipo->imagen,v1d);
	     }else if(tipo->delay!=0){
	    	 this->factory->crear_dibujo_animado(tipo->imagen,v1d,tipo->fps, tipo->delay);
	     }else{
	    	this->factory->crear_dibujo_personaje(tipo->imagen,MOVIMIENTOS,CANTIDAD_DE_IMAGENES,tipo->fps);//el ultimo parametro es velocidad
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

void Vista::crearPersonaje(string tipo,Personaje* personaje) {
	ObjetoMapa* obj=this->modelo->juego->tipos[tipo];
	this->factory->crear_dibujo_personaje(obj->imagen,MOVIMIENTOS,CANTIDAD_DE_IMAGENES,obj->fps);//el ultimo parametro es velocidad
	dibujo_t pers_moviendo = this->factory->ultimo_dibujo();
	this->factory->crear_dibujo_personaje(obj->imagen_quieto,MOVIMIENTOS,CANTIDAD_DE_IMAGENES,obj->fps);//el ultimo parametro es velocidad
	dibujo_t pers_esta_quieto = this->factory->ultimo_dibujo();
	this->factory->crear_dibujo_personaje(obj->imagen_atacando,MOVIMIENTOS,CANTIDAD_DE_IMAGENES,obj->fps);//el ultimo parametro es velocidad
	dibujo_t pers_esta_atacando = this->factory->ultimo_dibujo();
	personaje->setDibujo(pers_esta_atacando,pers_esta_quieto,pers_moviendo);
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
void Vista::cargarEdificioACrear(string tipo){
	//seteo el dibujo a lo q deberia ser
	edificioACrear = this->factory->get_dibujo(this->factory->get_idDibujo(tipo));
	entidadACrear = new Entidad(this->modelo->juego->tipos[tipo]);
}
void Vista::dejarDeDibujarEdificio(){
	if (this->entidadACrear) {
		delete this->entidadACrear;
		this->entidadACrear = NULL;
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
				this->dejarDeDibujarEdificio();
				SDL_GetMouseState(&mov_x, &mov_y);
				this->transformador->transformar_pantalla_isometrica(mov_x,
						mov_y, personaje_x, personaje_y);
				this->corregir_referencia_coordenadas_pantalla_mapa(personaje_x,
						personaje_y);
				Posicion p = Posicion(personaje_x, personaje_y);
				//le envia al server que cambie el destino
				vector<Personaje*> personajes=this->modelo->devolverPersonajeSeleccionado();

				if (!personajes.empty()) {
					vector<Personaje*>::iterator it = personajes.begin();
					for (; it != personajes.end(); it++) {
						Personaje* personaje = (*it);
						if (personaje->getNombreJugador()
								== this->modelo->nombreJugador()) {
							this->gameController->cambiar_destino_personaje(
									personaje->getId(), personaje_x,
									personaje_y);
							this->gameController->interactuar(personaje, p);
						}
					}
				}

			}
			//TODO
			//no dejo que se dibuje el edificio si clique

			if (e.button.button == SDL_BUTTON_LEFT) {
				esta_eligiendo=true;
				double a, b;
				SDL_GetMouseState(&seleccion_x_inicio, &seleccion_y_inicio);
				this->transformador->transformar_pantalla_isometrica(mov_x,
						mov_y, a, b);
				this->corregir_referencia_coordenadas_pantalla_mapa(a, b);

			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				esta_eligiendo=false;
				termino_de_elegir=true;
				this->setear_seleccion();
				SDL_GetMouseState(&seleccion_x_final, &seleccion_y_final);
				double a, b;
				this->transformador->transformar_pantalla_isometrica(
						seleccion_x_final, seleccion_y_final, a, b);
				this->corregir_referencia_coordenadas_pantalla_mapa(a, b);
				//si seleeciono sobre mapa
				if (seleccion_y_final < this->barra->obtenerYDondeSeDibuja()) {
					//si ve donde esta haciendo click
					if (this->modelo->oscuridad(0, a, b) == VISIBLE) {
						if (this->entidadACrear) {
							//no lo puede crear en lugar donde no ve
							if (!this->modelo->tocaSombra(entidadACrear)) {
								//TODO crear con muchos tipitos
								//si puede crear es porque tiene un tipito seleccionado
								this->gameController->crearEdificio(
										this->entidadACrear->mostrar_contenido(),
										this->modelo->devolverPersonajeSeleccionado().front()->getId(),
										floor(a), floor(b));
								//podria moverse a cuando recibe que se creo asi se deja de dibjar
								//en ese momento
							}
							this->dejarDeDibujarEdificio();
						} else {
							//si no creo estoy seleccionando
							this->barra->setDisplay(modelo->seleccionar(a, b));
						}


					}
				}
				else {
					string tipo =this->barra->seleccionar(seleccion_x_final, seleccion_y_final);
					if (tipo!=""){
						this->cargarEdificioACrear(tipo);
					}
				}



			}

		}
		if (e.type == SDL_KEYDOWN) {
			this->dejarDeDibujarEdificio();
			SDL_Keycode keyPressed = e.key.keysym.sym;

			switch (keyPressed) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_r:
				return true;

			}
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gRenderer);

	modelo->actualizarMapa(); //lo tiene que hacer el server
	dibujar_mapa();
	SDL_GetMouseState(&mov_x, &mov_y);
	dibujar_edificio(mov_x,mov_y);
	dibujar_barra();
	detectar_mouse_borde();
	SDL_RenderPresent(gRenderer);
	return quit;
}
void Vista::dibujar_edificio(int mov_x,int mov_y){
	double a,b;
	if (this->entidadACrear){
		//transformacion de posiciones
		this->transformador->transformar_pantalla_isometrica(mov_x, mov_y, a,
				b);
		this->corregir_referencia_coordenadas_pantalla_mapa(a, b);
		this->entidadACrear->set_posicion(floor(a),floor(b));
		if (this->modelo->tocaSombra(this->entidadACrear)){
			this->edificioACrear->ponerAmarillo();
		}else if (!this->modelo->mapa->puedeUbicar(this->entidadACrear))  {
			this->edificioACrear->ponerRojo();
		}else{
			this->edificioACrear->ponerVerde();
		}

		double pant_x,pant_y;
		this->transformador->transformar_isometrica_pantalla(floor(a)-this->referencia_mapa_x,floor(b)-this->referencia_mapa_y,pant_x,pant_y);
		this->corregir_referencia_coordenadas_mapa_pantalla(pant_x,pant_y);
		this->edificioACrear->set_posicion_default(pant_x,pant_y);
		this->edificioACrear->render(gRenderer);
		this->edificioACrear->resetear();
		this->edificioACrear->reiniciar(); //pone el color original
	}
}
vector<int> Vista::calcular_bordes() {
	/**
	 Fuente:
	 http://www.java-gaming.org/index.php?topic=24922.0
	 **/
	int pantalla_refencia_x, pantalla_refencia_y;
	this->transformador->transformar_isometrica_pantalla(referencia_mapa_x,
			referencia_mapa_y, pantalla_refencia_x, pantalla_refencia_y);
	int x_start, y_start;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x,
			pantalla_refencia_y, x_start, y_start);
	x_start = x_start - 2;
	int x_max, y;
	this->transformador->transformar_pantalla_isometrica(
			pantalla_refencia_x + pantalla->getAncho(),
			pantalla_refencia_y + pantalla->getAlto(), x_max, y);
	x_max += 2;
	int x, y_max;
	this->transformador->transformar_pantalla_isometrica(pantalla_refencia_x,
			pantalla_refencia_y + pantalla->getAlto(), x, y_max);
	y_max = y_max + 2;
	int y_min;
	this->transformador->transformar_pantalla_isometrica(
			pantalla_refencia_x + pantalla->getAncho(), pantalla_refencia_y, x,
			y_min);
	y_min -= 2;
	vector<int> bordes = { x_start, y_min, x_max, y_max };
	return bordes;
}


void Vista::corregir_referencia_coordenadas_pantalla_mapa(double& coord_x,
		double& coord_y) {
	coord_x += referencia_mapa_x - 0.5;
	coord_y += referencia_mapa_y + 0.5;
}
void Vista::corregir_referencia_coordenadas_mapa_pantalla(double& coord_x,
		double& coord_y) {
	coord_x += (-referencia_mapa_x + 0.5);
	coord_y += (-referencia_mapa_y - 0.5);
}

bool Vista::adentro_del_mapa(double coord_x, double coord_y) {
	return ((coord_x < this->modelo->get_ancho_mapa())
			&& (coord_y < this->modelo->get_alto_mapa()) && (coord_x >= 0)
			&& (coord_y >= 0));
}

bool Vista::adentro_del_mapa(int coord_x, int coord_y) {
	return ((coord_x < this->modelo->get_ancho_mapa())
			&& (coord_y < this->modelo->get_alto_mapa()) && (coord_x >= 0)
			&& (coord_y >= 0));
}

bool Vista::esta_en_seleccion(int x,int y){
	return ((x<seleccion_x_final)&&(x>seleccion_x_inicio)&&(y<seleccion_y_final)&&(y>seleccion_y_inicio));

}
void Vista::setear_seleccion(){
	if (seleccion_x_final < seleccion_x_inicio) {
		int extra = seleccion_x_final;
		seleccion_x_final = seleccion_x_inicio;
		seleccion_x_inicio = extra;
	}
	if (seleccion_y_final < seleccion_y_inicio) {
		int extra = seleccion_y_final;
		seleccion_y_final = seleccion_y_inicio;
		seleccion_y_inicio = extra;
	}
}
void Vista::dibujar_personaje(Personaje* personaje) {
	int img_personaje_x, img_personaje_y;
	double personaje_x = personaje->getReferenciaMapaX();
	double personaje_y = personaje->getReferenciaMapaY();
	this->corregir_referencia_coordenadas_mapa_pantalla(personaje_x,
			personaje_y);
	this->transformador->transformar_isometrica_pantalla(personaje_x,
			personaje_y, img_personaje_x, img_personaje_y);

	shared_ptr<DibujoPersonaje> dibujo_pers_anterior = dynamic_pointer_cast< DibujoPersonaje> (this->factory->get_dibujo(personaje->getDibujoAnterior()));
	shared_ptr<DibujoPersonaje> dibujo_pers = dynamic_pointer_cast< DibujoPersonaje> (this->factory->get_dibujo(personaje->dibujar()));

	dibujo_pers->setMovimientoActual(dibujo_pers_anterior->getMovimientoActual());
	dibujo_pers->set_posicion_default(img_personaje_x, img_personaje_y);
	if(esta_en_seleccion(img_personaje_x,img_personaje_y)&&termino_de_elegir){
		modelo->seleccionar(personaje->getReferenciaMapaX(),personaje->getReferenciaMapaY());
	}
	Posicion destino = personaje->get_camino();
	double mover_x = destino.get_x_exacta();
	double mover_y = destino.get_y_exacta();
	if (!adentro_del_mapa(mover_x, mover_y)) {
		mover_x = personaje->getReferenciaMapaX();
		mover_y = personaje->getReferenciaMapaY();
	}
	if (personaje->estaCongelado()) {
		dibujo_pers->congelar();
	} else {
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
					if (dim == TILES) {
						n_imagen = this->modelo->dibujar(dim, coord_x, coord_y); //MEZCLA MODELO CON VISTA para dsps
					} else {
						n_imagen = this->factory->get_idDibujo(
								this->modelo->mapa->mostrar_entidad(coord_x,
										coord_y));
					}
					//fin cambio villero
					int oscuro = modelo->oscuridad(dim, coord_x, coord_y);
					shared_ptr<Dibujo> dibujo = this->factory->get_dibujo(
							n_imagen);

					if (this->modelo->devolverPersonaje(coord_x, coord_y)) {
						if (oscuro == 0) {
							dibujar_personaje(
									this->modelo->devolverPersonaje(coord_x,
											coord_y));
						}
					}
					if (dim == TILES) {
						if (this->modelo->estaSeleccionada(coord_x, coord_y)) {
							dibujo->iluminar();
						}
					}
					if (dibujo != NULL && !repito_dibujo(coord_x,coord_y,dim)) {
						/*HARDCODE*/
						this->transformador->transformar_isometrica_pantalla(
								coord_x - referencia_mapa_x,
								coord_y - referencia_mapa_y, x_imagen,
								y_imagen);
						dibujo->set_posicion_default(x_imagen, y_imagen);

						if (oscuro == 1)
							dibujo->oscurecer();
						dibujo->setAnimar(false);
						if (oscuro != 1 && oscuro < 2) {

							dibujo->setAnimar(true);
						}
						if (oscuro < 2) {
							dibujo->render(gRenderer);
						}

						dibujo->resetear();
						dibujo->reiniciar(); //pone el color original
					}
				}
			}
		}
	}
	if (esta_eligiendo) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		SDL_Rect rect;
		rect.x = seleccion_x_inicio;
		rect.y = seleccion_y_inicio;
		rect.w = mouse_x - seleccion_x_inicio;
		rect.h = mouse_y - seleccion_y_inicio;
		SDL_RenderDrawRect(gRenderer,&rect);
	}
	termino_de_elegir=false;
}

void Vista::dibujar_barra() {
	this->barra->actualizar(this->modelo->getJugador(),this->modelo->devolverPersonajeSeleccionado());
	this->barra->render(gRenderer);
}

bool Vista::repito_dibujo(int x, int y,int dimension){
	if (dimension != TILES) {
		Entidad * entidad = this->modelo->mapa->entidad_celda(x, y);
		//si no hay entidad no repito dibujo
		if (entidad == NULL) {
			return false;
		}
		Posicion pos = { x, y };
		//si hay entidad tengo que ver si la que quiero dibujar esta en la celda que estoy viendo
		if (entidad->posicion->distancia(pos) == 0) {
			return false;
		}
		return true;
	}
	return false;
}

Vista::~Vista() {
	this->barra->closeFont();
	TTF_Quit();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

/*
 * Minimapa.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: tobias
 */

#include "Minimapa.h"
#define TAM_ENTIDAD 2
#include <vector>
#include "../ModeloSrc/Personaje.h"

#define AZUL 1
#define ROJO 2
#define VERDE 3
#define NEGRO 4
#define BLANCO 5
#define VERDE_OSCURO 6
#define NARANJA 7



Minimapa::Minimapa(Modelo *modelo,double *x_ref, double *y_ref) {

	this->modelo = modelo;
	this->x = (modelo->juego->pantalla->getAncho()*3)/4;
	this->y = (modelo->juego->pantalla->getAlto()*3)/4;
	this->diagonal = x/3;
	this->lado = int(double(diagonal)/sqrt(2));
	this-> ancho_por_celda = modelo->juego->pantalla->getAncho()/modelo->get_ancho_mapa();
	this-> alto_por_celda = modelo->juego->pantalla->getAlto()/modelo->get_alto_mapa();
	this->x_ref = x_ref;
	this->y_ref = y_ref;
}

int Minimapa::altoMapa(){
	return this->diagonal;
}
int Minimapa::anchoPantalla(){
	return this->modelo->juego->pantalla->getAncho();
}
int Minimapa::anchoPorCelda(){
	//en coordenadas cartesianas
	return this->ancho_por_celda;
}
int Minimapa::altoPorCelda(){
	//coordenadas cartesianas
	return this->alto_por_celda;
}

void Minimapa::dibujarPuntoMapa(int pant_x, int pant_y, SDL_Color color, SDL_Renderer *renderer){
	SDL_Rect fillRect = { pant_x, pant_y, this->ancho_por_celda, this->alto_por_celda };
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
	SDL_RenderFillRect( renderer, &fillRect );
}

bool Minimapa::inicializar(SDL_Renderer * render){
	bool err = this-textura->createBlank(modelo->juego->pantalla->getAncho(),modelo->juego->pantalla->getAncho(),SDL_TEXTUREACCESS_TARGET,render);
	return err;
}

void Minimapa::render(SDL_Renderer* renderer){
	int pos_x,pos_y;
	SDL_Rect dsRect = { x+(x/3-lado)/2, ((7*y)/3-diagonal)/2, lado, lado };
	this->textura->setAsRenderTarget(renderer);
	SDL_Color colorMapa = paleta(VERDE_OSCURO);
    SDL_SetRenderDrawColor( renderer, colorMapa.r, colorMapa.g, colorMapa.b, colorMapa.a );
    SDL_RenderClear( renderer );

	for (int i = 0; i < this->modelo->juego->escenario->entidades.size();i++){
		Entidad* entidad = this->modelo->juego->escenario->entidades[i];
		pos_x = ancho_por_celda*entidad->posicion->getX();
		pos_y= alto_por_celda*entidad->posicion->getY();
		if (entidad->esUnRecurso())
			dibujarPuntoMapa(pos_x,pos_y,paleta(NARANJA),renderer);
		else
			dibujarPuntoMapa(pos_x,pos_y,paleta(AZUL),renderer);
	}
	vector<Personaje*> personajes = this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* personaje = (*it);
		int x = personaje->get_posicion().getX() * ancho_por_celda;
		int y = personaje->get_posicion().getY()
				* alto_por_celda;
		this->dibujarPuntoMapa(x, y, paleta(ROJO), renderer);
	}
	SDL_SetRenderTarget(renderer,NULL);
	this->textura->renderEx(45,NULL,&dsRect,renderer);
}

SDL_Color Minimapa::paleta(int Color){
	SDL_Color c;
	switch (Color){
		case AZUL:
			c = {0x00,0x00,0xFF};
			break;
		case VERDE:
			c = {0x00,0xFF,0x00};
			break;
		case ROJO:
			c = {0xFF,0x00,0x00};
			break;
		case NEGRO:
			c = {0x00,0x00,0x00};
			break;
		case VERDE_OSCURO:
			c = {52,110,43};
			break;
		case NARANJA:
			c = {255,145,0};
			break;
		default:
			c = {0xFF,0xFF,0xFF};
	}
	return c;
}


Minimapa::~Minimapa() {
	// TODO Auto-generated destructor stub
}


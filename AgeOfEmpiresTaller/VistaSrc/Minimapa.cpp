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

SDL_Color make_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
SDL_Color c= { r, g, b, a };
return c;
}

#define AZUL make_color(0x00,0x00,0xFF,0x00)
#define ROJO make_color(0xFF,0x00,0x00,0x00)
#define VERDE make_color(0x00,0xFF,0x00,0x00)



Minimapa::Minimapa(Modelo *modelo) {

	this->modelo = modelo;
	this->x = (modelo->juego->pantalla->getAncho()*3)/4;
	this->y = (modelo->juego->pantalla->getAlto()*3)/4;
	this->diagonal = x/3;
	this->lado = int(double(diagonal)/sqrt(2));
	this-> ancho_por_celda = modelo->juego->pantalla->getAncho()/modelo->get_ancho_mapa();
	this-> alto_por_celda = modelo->juego->pantalla->getAlto()/modelo->get_alto_mapa();
}

int Minimapa::altoMapa(){
	return this->diagonal;
}
int Minimapa::anchoPantalla(){
	return this->modelo->juego->pantalla->getAncho();
}

void Minimapa::dibujarPuntoMapa(int pant_x, int pant_y, SDL_Color color, SDL_Renderer *renderer){
	SDL_Rect fillRect = { pant_x, pant_y, this->ancho_por_celda, this->alto_por_celda };
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
	SDL_RenderFillRect( renderer, &fillRect );
}

bool Minimapa::inicializar(SDL_Renderer * render){
	bool err = this-textura->createBlank(modelo->juego->pantalla->getAncho(),modelo->juego->pantalla->getAncho(),SDL_TEXTUREACCESS_TARGET,render);
	//no estoy chequeando un error
	return err;
}

void Minimapa::render(SDL_Renderer* renderer){
	int pos_x,pos_y;
	SDL_Rect dsRect = { x+(x/3-lado)/2, ((7*y)/3-diagonal)/2, lado, lado };
	this->textura->setAsRenderTarget(renderer);
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0x00 );
    SDL_RenderClear( renderer );

	for (int i = 0; i < this->modelo->juego->escenario->entidades.size();i++){
		Entidad* entidad = this->modelo->juego->escenario->entidades[i];
		pos_x = ancho_por_celda*entidad->posicion->getX();
		pos_y= alto_por_celda*entidad->posicion->getY();
		dibujarPuntoMapa(pos_x,pos_y,AZUL,renderer);
	}
	vector<Personaje*> personajes = this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* personaje = (*it);
		int x = personaje->get_posicion().getX() * ancho_por_celda;
		int y = personaje->get_posicion().getY()
				* alto_por_celda;
		this->dibujarPuntoMapa(x, y, ROJO, renderer);
	}
	SDL_SetRenderTarget(renderer,NULL);
	this->textura->renderEx(45,NULL,&dsRect,renderer);
}


Minimapa::~Minimapa() {
	// TODO Auto-generated destructor stub
}


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
#define AMARILLO 7
#define AMARILLO_OSCURO 8
#define ROJO_OSCURO 9
#define AZUL_OSCURO 10



Minimapa::Minimapa(Modelo *modelo) {

	this->modelo = modelo;
	this->diagonal = modelo->juego->pantalla->getAlto()/3;
	this->x = modelo->juego->pantalla->getAncho()-diagonal/2;
	this->y = modelo->juego->pantalla->getAlto()-diagonal;
	this->lado = int(double(diagonal)/sqrt(2));
	this-> ancho_por_celda = modelo->juego->pantalla->getAncho()/modelo->get_ancho_mapa();
	this-> alto_por_celda = modelo->juego->pantalla->getAlto()/modelo->get_alto_mapa();
	this->invertir = false;
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
	bool err = this-textura->createBlank(modelo->juego->pantalla->getAncho(),modelo->juego->pantalla->getAlto(),SDL_TEXTUREACCESS_TARGET,render);
	this->fondo=this->paleta(NEGRO);
	return err;
}

void Minimapa::render(SDL_Renderer* renderer){
	int pos_x,pos_y;
	SDL_Rect dsRect = { x-lado/2, y+(diagonal-lado)/2, lado, lado };
	this->textura->setAsRenderTarget(renderer);
	SDL_Color colorMapa = fondo;
    SDL_SetRenderDrawColor( renderer, colorMapa.r, colorMapa.g, colorMapa.b, colorMapa.a );
    SDL_RenderClear( renderer );
    //FOG ANDA LENTO
    int count=0;
    for (int i=0; i < this->modelo->get_ancho_mapa();i++){
    	for (int j=0; j < this->modelo->get_alto_mapa();j++){
    		this->dibujarElemento(i,j,renderer,&count);
    	}
    }
    /*
    //marco polo
	this->fondo = this->paleta(VERDE);
	 for (unsigned int i = 0; i < this->modelo->juego->escenario->entidades.size();i++){
		Entidad* entidad = this->modelo->juego->escenario->entidades[i];
		pos_x = ancho_por_celda*entidad->posicion->getX();
		pos_y= alto_por_celda*entidad->posicion->getY();
		if (entidad->esUnRecurso())
			dibujarPuntoMapa(pos_x,pos_y,paleta(AMARILLO),renderer);
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
	}*/
	SDL_SetRenderTarget(renderer,NULL);
	this->textura->renderEx(45,NULL,&dsRect,renderer,NULL);
	if (count > (this->modelo->mapa->getAncho()*this->modelo->mapa->getLargo()/2)){
		//si mas de la mitad esta a la vista
		this->invertir=true;
		this->fondo=paleta(VERDE_OSCURO);
	}
}

void Minimapa::dibujarElemento(int x, int y,SDL_Renderer * renderer,int * count){
	int d = this->modelo->oscuridad(0, x, y);
	Posicion pos={x,y};
	int x_pant = x *ancho_por_celda;
	int y_pant = y *alto_por_celda;
	if (d != 2) {
		int color;
		if (this->modelo->mapa->celdaOcupada(x, y)) {
			if (this->modelo->mapa->hay_personaje(x, y)) {
				if (this->modelo->nombreJugador() != this->modelo->mapa->personaje_celda(x,y)->getNombreJugador()){
					color = BLANCO;
				}else
					color = ROJO;
			} else if (this->modelo->mapa->hayRecursosEn(pos)) {
				color = AMARILLO;
			}else {
				color = AZUL;
			}
		}else{
			color = VERDE;
		}

		if (d==1){
			//si inverti los colores el verde oscuro no lo tengo q dibujar
			if((invertir) && (color==VERDE)){
				return;
			}
			if (this->modelo->mapa->hay_personaje(x, y)){
				color = VERDE;

			}
			color = this->sombra(color);
		}
		*count+=1;
		SDL_Color paleta = this->paleta(color);
		this->dibujarPuntoMapa(x_pant, y_pant, paleta, renderer);
	}else if (invertir){
		//si hay mas ocupado que negro dibujo lo negro y el fondo es verde
		SDL_Color paleta = this->paleta(NEGRO);
		this->dibujarPuntoMapa(x_pant, y_pant, paleta, renderer);
	}
}
int Minimapa::sombra(int color){
	switch (color){
		case AZUL:
			return AZUL_OSCURO;
		case ROJO:
			return ROJO_OSCURO;
		case VERDE:
			return VERDE_OSCURO;
		case AMARILLO:
			return AMARILLO_OSCURO;
	}
}


SDL_Color Minimapa::paleta(int Color){
	SDL_Color c;
	switch (Color){
		case AZUL:
			c = {0x00,0x00,0xFF};
			break;
		case VERDE:
			c = {87,193,101};
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
		case AMARILLO:
			c = {255,255,0};
			break;
		case AZUL_OSCURO:
			c = {7,10,88};
			break;
		case ROJO_OSCURO:
			c = {101,7,23};
			break;
		case AMARILLO_OSCURO:
			c = {255,171,2};
			break;
		default:
			c = {0xFF,0xFF,0xFF};
	}
	return c;
}


Minimapa::~Minimapa() {
	// TODO Auto-generated destructor stub
}


/*
 * Modelo.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Modelo.h"
#include "../ModeloSrc/Mapa.h"
#include "math.h"
#define DIMENSIONES 2 //TILE Y ESCENARIO
enum dimension{TILES,ESCENARIO};
Modelo::Modelo(Juego* juego) {
	this -> juego = juego;
	setMapa(this->juego->escenario->size_x, this->juego->escenario->size_y);
	this->lista_personajes=vector<shared_ptr<Personaje>>(1,NULL);
}
void Modelo::setMapa(int ancho,int largo){
	this->mapa=shared_ptr<Mapa>(new Mapa(ancho,largo));
}
void Modelo::agregarPersonaje(float x,float y,dibujo_t dibujo){
	shared_ptr<Personaje> personaje=shared_ptr<Personaje>(new Personaje(x,y,dibujo));
	lista_personajes.push_back(personaje);
}
shared_ptr<Personaje> Modelo::devolverPersonaje(){
	return lista_personajes[0];
}


void Modelo::setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles){
	int ancho =this->mapa->getAncho();
	int largo =this->mapa->getLargo();
	int i=0,j=0;
	for(i=0;i<ancho;i++){
		for(j=0;j<largo;j++){
			this->mapa->setEscenario(escenario[i][j],i,j);
			this->mapa->setTiles(tiles[i][j],i,j);
		}
	}
}
dibujo_t Modelo::dibujar(int dim,int x,int y){
	if(dim==ESCENARIO){
		return this->mapa->dibujarEscenario(x,y);
	}
	return this->mapa->dibujarTiles(x,y);
}

/**
vector<vector<vector<dibujo_t>>> Modelo::dibujar(int x,int 	y,int ancho,int largo){
		Recibe un posicion x,y de comienzo y un ancho y alto para dibujar.
	 	Dibuja entre (x,y),(x+ancho,y),(x,y+largo),(x+ancho)(y+largo)
	 	Dibuja los tiles y el escenario.

	vector<vector<vector<dibujo_t>> >  dibujos(DIMENSIONES);
	for(int d=0;d<DIMENSIONES;d++){
		dibujos[d]=vector<vector<dibujo_t>>(ancho);
		for (int a = 0; a < ancho;a++) {
			dibujos[d][a]=vector<dibujo_t>(largo);
			for(int l=0;l<largo;l++) {
				if(d==TILES){
					dibujos[TILES][a][l]=this->mapa->dibujarTiles(x+a,y+l);
				}else{
					dibujos[ESCENARIO][a][l]=this->mapa->dibujarEscenario(x+a,y+l);
				}
			}
		}
	}
	return dibujos;
}**/


int Modelo::get_alto_mapa(){
	return mapa->getLargo();
}

int Modelo::get_ancho_mapa(){
	return mapa->getAncho();
}



Modelo::~Modelo() {
	delete this->juego;


}


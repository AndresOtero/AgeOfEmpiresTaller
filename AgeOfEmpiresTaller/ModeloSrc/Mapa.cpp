/*
 * Mapa.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "Mapa.h"
#include "Celda.h"
#include "Posicion.h"
#include <iostream>
#include <queue>
#include "CmpDistanciasTuplas.h"
Mapa::Mapa(int ancho, int largo) {
	this->largo = largo;
	this->ancho = ancho;
	Celda*** celdas = new Celda**[ancho];
	for (int i = 0; i < ancho; ++i) {
		celdas[i] = new Celda*[largo];
	}
	for (int i = 0; i < ancho; ++i) {
		for (int j = 0; j < largo; ++j) {
			celdas[i][j] = new Celda();

		}
	}
	this->celdas=celdas;
}

Celda* Mapa::getCelda(int x,int y){
	return this->celdas[x][y];
}
void Mapa::setTiles(dibujo_t dibujo,int x,int y){
	this->getCelda(x,y)->setTiles(dibujo);
}
void Mapa::setEscenario(dibujo_t dibujo,int x,int y){
	this->getCelda(x,y)->setEscenario(dibujo);
}
string Mapa::mostrar_contenido(int x,int y){
	return this->getCelda(x,y)->mostrar_contenido();
}
string Mapa::mostrar_entidad(int x, int y){
	return this->getCelda(x,y)->mostrar_entidad();
}
Entidad* Mapa::entidad_celda(int x, int y){
	return this->getCelda(x,y)->devolver_entidad();
}
bool Mapa::celdaOcupada(int x, int y) {
	Celda* celda=this->getCelda(x,y);
	if (celda==NULL) {
		return false;
	}
	return (celda->estaOcupada());
}
dibujo_t Mapa::dibujarEscenario(int x, int y) {
	if ((y >= this->largo) || (x >= this->ancho)||(y <0)||(x <0)) {
		return AFUERA;
	}
	return this->getCelda(x,y)->dibujarEscenario();
}
Personaje* Mapa::personaje_celda(int x, int y) {
	return this->getCelda(x,y)->devolver_personaje();
}
bool Mapa::hay_personaje(int x, int y) {
	return (this->getCelda(x,y)->devolver_personaje()!=NULL);
}
dibujo_t Mapa::dibujarTiles(int x, int y) {
	if ((y >= this->largo) || (x >= this->ancho)||(y <0)||(x <0)) {
		return AFUERA;
	}
	return this->getCelda(x,y)->dibujarTiles();
}
void Mapa::actualizar(vector<Personaje*> personajes) {
	for(int i=0;i<ancho;i++){
		for (int j = 0;  j < largo;  j++) {
			this->getCelda(i,j)->actualizar();
		}
	}
	vector<Personaje*>::iterator it =personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p=(*it);
		Posicion pos=p->get_posicion();
		this->getCelda(pos.getX(),pos.getY())->ocuparCeldaPersonaje(p);
	}
}

int Mapa::getAncho(){
	return this->ancho;
}
int Mapa::getLargo(){
	return this->largo;
}
bool Mapa::afueraDelMapa(int x,int y){
	return ((y >= this->largo) || (x >= this->ancho)||(y <0)||(x <0));
}
Posicion Mapa::validar_destino(Posicion adonde_voy, Posicion adonde_estoy) {
	if(afueraDelMapa(adonde_voy.getX(),adonde_voy.getY())){
		return adonde_estoy;
	}
	if((adonde_estoy==adonde_voy)||(!celdaOcupada(adonde_voy.getX(), adonde_voy.getY()))) {
		return adonde_voy;
	}
	return adonde_estoy;
	vector<Posicion> adyacentes = adyacenciasNoOcupadas(adonde_voy);
	vector<Posicion>::iterator it = adyacentes.begin();
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>,
				CompDistancias> pila;
	for (; it != adyacentes.end(); ++it) {
		Posicion ady = (*it);
		pila.push(pair<Posicion, double>(ady, adonde_estoy.distancia_euclidia(ady)));
	}
	return pila.top().first;
}
vector<Posicion> Mapa::adyacenciasNoOcupadas(Posicion posicion) {
	vector<Posicion> adyacentes = vector<Posicion>();
	int x = posicion.getX(), y = posicion.getY();
	/**for (int i = x - 1; i < x + 2; i++) {
		for (int j = y - 1; j < y + 2; j++) {
			if ((!afueraDelMapa(i, j)) && (!celdaOcupada(i, j))
					&& ((i != x) || (j != y))) {
				adyacentes.push_back(Posicion(i+0.5, j+0.5));
			}
		}
	}**/

	for (int i = x - 1; i < x + 2; i+=2) {
		if ((!afueraDelMapa(i, y)) && (!celdaOcupada(i, y))) {
					adyacentes.push_back(Posicion(i,y));
		}
	}
	for (int j = y - 1; j < y + 2; j+=2) {
		if ((!afueraDelMapa(x, j)) && (!celdaOcupada(x, j))) {
			adyacentes.push_back(Posicion(x, j));
		}
	}

	for (int i=x-1,j=y-1; i < x + 2; i += 2,j+=2) {
		if ((!afueraDelMapa(i, j)) && (!celdaOcupada(i, j))
				&&(!celdaOcupada(x, j))&&(!celdaOcupada(i, y))) {
			adyacentes.push_back(Posicion(i, j));
		}
	}
	for (int i=x+1,j=y+1; i > x - 2; i -= 2,j-=2) {
		if ((!afueraDelMapa(i, j)) && (!celdaOcupada(i, j))
						&&(!celdaOcupada(x, j))&&(!celdaOcupada(i, y))) {
			adyacentes.push_back(Posicion(i, j));
		}
	}


		return adyacentes;
}

void Mapa::posicionarEntidad(Entidad* entidad){
	int i,j,x,y,alto,ancho;
	alto = entidad->objetoMapa->baseLogica->alto;
	ancho = entidad->objetoMapa->baseLogica->ancho;
	x = entidad->posicion->getX();
	y = entidad->posicion->getY();
	for (i = x; i < alto+x; i++ ){
		for (j = y; j< ancho+y;j++){
			this->getCelda(i,j)->ocuparCelda(entidad);//guardar referencias en celdas
		}
	}
}
void Mapa::sacarEntidad(Entidad * entidad){
	int i,j,x,y,alto,ancho;
		alto = entidad->objetoMapa->baseLogica->alto;
		ancho = entidad->objetoMapa->baseLogica->ancho;
		x = entidad->posicion->getX();
		y = entidad->posicion->getY();
		for (i = x; i < alto+x; i++ ){
			for (j = y; j< ancho+y;j++){
				this->getCelda(i,j)->liberarCelda();
			}
		}
}

Posicion Mapa::posicionVacia(){
	GeneradorNumeros num;
	int x;
	int y;
	Celda * celda;
	do{
	x = num.numeroRandom(0,this->ancho);
	y = num.numeroRandom(0,this->largo);
	celda = this->getCelda(x,y);
	}while (celda->estaOcupada()||celda->tieneRecurso());
	Posicion pos={x,y};
	return pos;
}
bool Mapa::hayRecursosEn(Posicion posicion){
	return this->getCelda(posicion.getX(),posicion.getY())->tieneRecurso();
}
Mapa::~Mapa() {
	int largo = this->largo;
	int ancho = this->ancho;
	Celda*** celdas = this->celdas;
	for (int i = 0; i < ancho; ++i) {
		for (int j = 0; j < largo; ++j) {
			delete celdas[i][j];
		}
	}
	for (int i = 0; i < ancho; ++i) {
			delete[] celdas[i] ;
	}
	delete[] celdas;

}

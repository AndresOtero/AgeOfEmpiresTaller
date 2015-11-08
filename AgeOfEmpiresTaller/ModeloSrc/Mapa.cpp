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
void Mapa::seleccionar(int x,int y){
	return this->celdas[x][y]->seleccionarEntidad();
}
bool Mapa::estaSeleccionada(int x,int y){
	return (this->celdas[x][y]->estaSeleccionada());
}
void Mapa::deseleccionar(){
	int i,j;
	for(int i=0;i<ancho;i++){
			for (int j = 0;  j < largo;  j++) {
				this->getCelda(i,j)->deseleccionarEntidad();
			}
		}
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
	if(adonde_estoy.distancia_octal(adonde_voy)<=14){
		return adonde_estoy;
	}
	//printf("Voy hacia uno ocupado\n");
	adonde_voy=Posicion(adonde_voy.getX(),adonde_voy.getY());
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>,
				CompDistancias> pila_no_ocupadas;
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>,
					CompDistancias> pila_ocupadas;
	pila_ocupadas.push(pair<Posicion, double>(adonde_voy, adonde_voy.distancia_octal(adonde_estoy)));
	while(pila_no_ocupadas.empty()){
		Posicion ocupado_mas_cercano=pila_ocupadas.top().first;
		//printf("Ocupado: %d,%d\n",ocupado_mas_cercano.getX(),ocupado_mas_cercano.getY());
		vector<Posicion> adyacentes_no_ocupados = adyacenciasNoOcupadas(ocupado_mas_cercano);
		vector<Posicion>::iterator it = adyacentes_no_ocupados.begin();
		for (; it != adyacentes_no_ocupados.end(); ++it) {
			Posicion ady = (*it);
			//printf("No Ocupado: %d,%d\n",ady.getX(),ady.getY());
			pila_no_ocupadas.push(pair<Posicion, double>(ady,adonde_voy.distancia_octal(ady)+adonde_estoy.distancia_octal(ady)));
		}
		if(!pila_no_ocupadas.empty()){
			//printf("No Ocupado Elegido: %d,%d\n",pila_no_ocupadas.top().first.getX(),pila_no_ocupadas.top().first.getY());

			return pila_no_ocupadas.top().first;
		}else{
			vector<Posicion> adyacentes_ocupados = adyacencias(ocupado_mas_cercano);
			vector<Posicion>::iterator it = adyacentes_ocupados.begin();
			for (; it != adyacentes_no_ocupados.end(); ++it) {
				Posicion ady = (*it);
				pila_ocupadas.push(pair<Posicion, double>(ady,adonde_voy.distancia_octal(ady)+adonde_estoy.distancia_octal(ady)));
			}
		}
	}
	return pila_no_ocupadas.top().first;
}
vector<Posicion> Mapa::adyacencias(Posicion posicion) {
	vector<Posicion> adyacentes = vector<Posicion>();
	int x = posicion.getX(), y = posicion.getY();
	for(int i=x-1;i<x+1;i++){
		for(int j=y-1;j<y+1;j++){
			if((i!=x)&&(j!=y)){
				adyacentes.push_back(Posicion(i,j));
			}
		}
	}
		return adyacentes;
}

vector<Posicion> Mapa::adyacenciasNoOcupadas(Posicion posicion) {
	vector<Posicion> adyacentes = vector<Posicion>();
	int x = posicion.getX(), y = posicion.getY();
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
			this->getCelda(i,j)->ocuparCelda(NULL);//guardar referencias en celdas
		}
	}
	this->getCelda(x,y)->ocuparCelda(entidad);//guardar referencias en celdas

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

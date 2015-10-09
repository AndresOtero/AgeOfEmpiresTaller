/*
 * Modelo.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Modelo.h"
#include "../ModeloSrc/Mapa.h"
#include "math.h"
#include "queue"
#include "stack"
#include "iterator"
#include <map>
#include "CmpDistanciasTuplas.h"
#include "unordered_map"
#include "CmpPosicion.h"
using namespace std;


#define DIMENSIONES 2 //TILE Y ESCENARIO
enum dimension{TILES,ESCENARIO};

Modelo::Modelo(Juego* juego) {
	this -> juego = juego;
	setMapa(this->juego->escenario->size_x, this->juego->escenario->size_y);
	this->personajes=vector<Personaje*>();
	personaje_seleccionado=NULL;
	this->insertarEntidades();
}
void Modelo::insertarEntidades(){
	for(int i =0; i < this->juego->escenario->entidades.size(); i++){
			Entidad* entidad=this->juego->escenario->entidades[i];
			this->mapa->posicionarEntidad(entidad);
	}
}
void Modelo::setMapa(int ancho,int largo){
	this->mapa=shared_ptr<Mapa>(new Mapa(ancho,largo));
}
void Modelo::actualizarMapa(){
	mapa->actualizar(personajes);
}
void Modelo::agregarPersonaje(Personaje* personaje){
	personajes.push_back(personaje);
}
Personaje* Modelo::devolverPersonaje(){
	return personaje_seleccionado;
}
vector<Personaje*> Modelo::devolverTodosLosPersonajes(){
	return personajes;
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

bool Modelo::celdaOcupada(Posicion posicion){
	return this->mapa->celdaOcupada(posicion.getX(),posicion.getY());
}
string Modelo::seleccionar(double mov_x,double mov_y){
	Posicion posicion= Posicion(mov_x,mov_y);
	personaje_seleccionado=this->mapa->personaje_celda(posicion.getX(),posicion.getY());
	return this->mapa->mostrar_contenido(posicion.getX(),posicion.getY());

}



double Modelo::heuristica(Posicion adonde_voy,Posicion adonde_estoy){
	return adonde_voy.distancia_octal(adonde_estoy);
}
double Modelo::distancia(Posicion a,Posicion b){
	return a.distancia_octal(b);
}


Posicion Modelo::calcular_camino(Posicion adonde_estoy ,Posicion adonde_voy) {
	/**
	 *http://www.redblobgames.com/pathfinding/a-star/introduction.html
	 **/
	if(adonde_estoy==adonde_voy){
		return adonde_voy;
	}
	adonde_voy=mapa->validar_destino(adonde_voy,adonde_estoy);
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>,
			CompDistancias> pila;
	pair<Posicion, double> primero(adonde_estoy, 0);
	pila.push(primero);
	map<Posicion, Posicion,cmp_posiciones> donde_vengo;
	map<Posicion, double,cmp_posiciones> cuanto_recorri;
	donde_vengo.insert(pair<Posicion, Posicion>(adonde_estoy, adonde_estoy));
	cuanto_recorri.insert(primero);
	while (!pila.empty()) {
		pair<Posicion, double> actual = pila.top();
		Posicion posicion_actual = actual.first;
		pila.pop();
		if (posicion_actual == adonde_voy) {
			break;
		}
		vector<Posicion> adyacentes = mapa->adyacenciasNoOcupadas(actual.first);
		vector<Posicion>::iterator it = adyacentes.begin();
		for (; it != adyacentes.end(); ++it) {
			Posicion ady = (*it);
			double nueva_distancia = cuanto_recorri[posicion_actual]+distancia(ady,posicion_actual);
			if ((!(cuanto_recorri.count(ady)))
					|| (nueva_distancia < cuanto_recorri[ady])) {
				cuanto_recorri[ady] = nueva_distancia;
				double prioridad = nueva_distancia+ heuristica(adonde_voy, ady);
				pila.push(pair<Posicion, double>(ady, prioridad));
				donde_vengo[ady] = posicion_actual;

			}
		}
	}

	stack<Posicion> camino;
	camino.push(adonde_voy);
	Posicion anterior=adonde_voy;
	while(!(adonde_estoy==anterior)){
		camino.push(donde_vengo[anterior]);
		anterior=donde_vengo[anterior];
	}
	camino.pop();
	if(!camino.empty()){
		adonde_voy=camino.top();
	}
	while(!camino.empty()){
		Posicion pos=camino.top();
		camino.pop();
		//printf("Posicion: X:%d,Y:%d\n",pos.getX(),pos.getY());
	}
	printf("Adonde estoy: X:%g, Y:%g\n",adonde_estoy.get_x_exacta(),adonde_estoy.get_y_exacta());
	printf("Adonde  voy: X:%g, Y:%g\n",adonde_voy.get_x_exacta(),adonde_voy.get_y_exacta());
	return adonde_voy;
}
Posicion Modelo::mover_personaje(Personaje* personaje){
	Posicion destino= personaje->get_destino();
	Posicion adonde_estoy= personaje->get_posicion();
	Posicion adonde_voy=calcular_camino(adonde_estoy,destino);
	personaje->set_camino(adonde_voy);
	personaje->mover();
	return adonde_voy;
}
void  Modelo::cambiar_destino_personaje(double mov_x,double mov_y){
	Personaje* personaje= 	this->devolverPersonaje();
	if(personaje!=NULL){
		personaje->set_destino(Posicion(mov_x,mov_y));
	}
}

int Modelo::get_alto_mapa(){
	return mapa->getLargo();
}

int Modelo::get_ancho_mapa(){
	return mapa->getAncho();
}



Modelo::~Modelo() {
 delete this->juego;

}


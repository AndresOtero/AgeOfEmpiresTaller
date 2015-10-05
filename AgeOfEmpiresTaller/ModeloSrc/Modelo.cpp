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
#include "unordered_map"
using namespace std;


#define DIMENSIONES 2 //TILE Y ESCENARIO
enum dimension{TILES,ESCENARIO};

Modelo::Modelo(Juego* juego) {
	this -> juego = juego;
	setMapa(this->juego->escenario->size_x, this->juego->escenario->size_y);
	this->personajes=vector<Personaje*>();
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
void Modelo::agregarPersonaje(Personaje* personaje){
	personajes.push_back(personaje);
}
Personaje* Modelo::devolverPersonaje(){
	return this->personajes[0];
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

class CompDistancias
{
public:
    bool operator()(pair<Posicion,double> p1,pair<Posicion,double> p2) {
        return p1.second>p2.second;
    }
};

double heuristica(Posicion adonde_voy,Posicion adonde_estoy){
	return adonde_voy.distancia_manhattan(adonde_estoy);
}

struct cmp { /**
	Necesita un comparador para funcionar el diccionario (igualar claves), luego de mucho buscar encontre el
	que funciona.
 	 	**/
	bool operator()(Posicion const& a, Posicion const& b) const {
		if (a.getX() < b.getX())
			return true;
		if (a.getX() == b.getX()) {
			if (a.getY() < b.getY())
				return true;
			return false;
		}
		return false;

	}
};
Posicion Modelo::calcular_camino(double x, double y) {
	/**
	 *http://www.redblobgames.com/pathfinding/a-star/introduction.html
	 **/
	Posicion adonde_voy = Posicion(x, y);
	Personaje* personaje = devolverPersonaje();
	Posicion adonde_estoy = personaje->get_posicion();
	vector<Posicion> adyacentes = mapa->adyacenciasNoOcupadas(adonde_estoy);
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>,
			CompDistancias> pila;
	pair<Posicion, double> primero(adonde_estoy, 0);
	pila.push(primero);
	map<Posicion, Posicion,cmp> donde_vengo;
	map<Posicion, double,cmp> cuanto_recorri;
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
			double nueva_distancia = cuanto_recorri[posicion_actual]+ady.distancia_manhattan(posicion_actual);
			bool ya_pase =cuanto_recorri.count(ady);
			if(ya_pase) {
				double distancia_vieja=cuanto_recorri[ady];
			}
			if ((!(cuanto_recorri.count(ady)))
					|| (nueva_distancia < cuanto_recorri[ady])) {
				cuanto_recorri[ady] = nueva_distancia;
				double prioridad = nueva_distancia
						+ heuristica(adonde_voy, ady);
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
void Modelo::mover_personaje(double mov_x,double mov_y){
	Posicion adonde_voy=calcular_camino(mov_x,mov_y);

	Personaje* personaje=devolverPersonaje();
	personaje->mover(adonde_voy.get_x_exacta(),adonde_voy.get_y_exacta());
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


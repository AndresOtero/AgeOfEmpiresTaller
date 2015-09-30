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
#include "iterator"
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
struct cmp
{
    bool operator()( Posicion const& a, Posicion const& b ) const
    {
    	return (a.getX()<b.getY());
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
			if ((!(cuanto_recorri[ady]))
					|| (nueva_distancia < cuanto_recorri[ady])) {
				cuanto_recorri[ady] = nueva_distancia;
				double prioridad = nueva_distancia
						+ heuristica(adonde_voy, ady);
				pila.push(pair<Posicion, double>(ady, prioridad));
				donde_vengo[ady] = posicion_actual;

			}
		}
	}
	//m("Adonde estoy: x: %g, y: %g \n",adonde_voy.get_x_exacta(),adonde_voy.get_y_exacta());
	//printf("Donde estoy: x: %g, y: %g \n",donde_estoy.get_x_exacta(),donde_estoy.get_y_exacta());

	return adonde_voy;
}
void Modelo::mover_personaje(double mov_x,double mov_y){
	//Posicion adonde_voy=calcular_camino(mov_x,mov_y);
	Posicion adonde_voy = Posicion(mov_x, mov_y);

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


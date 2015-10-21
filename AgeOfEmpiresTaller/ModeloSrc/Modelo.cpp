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
#include "Recurso.h"
#include "Oro.h"
#include "Madera.h"
#include "Piedra.h"
#define MAX_RECURSOS 30
#define RITMO 5
using namespace std;

#define CICLOS_MAX 100
#define DIMENSIONES 2 //TILE Y ESCENARIO
enum dimension{TILES,ESCENARIO};

Modelo::Modelo(Juego* juego) {
	this -> juego = juego;
	setMapa(this->juego->escenario->size_x, this->juego->escenario->size_y);
	this->personajes=vector<Personaje*>();
	this->pisadas = vector<vector<int>>();
	personaje_seleccionado=NULL;
	this->insertarEntidades();
	this->totalRecursos=0;
	gettimeofday(&estado,NULL);

	for (int i = 0; i < this->juego->escenario->size_x; i++) {
	    vector<int> row; // Create an empty row
	    for (int j = 0; j < this->juego->escenario->size_y; j++) {
	        row.push_back(0); // Add an element (column) to the row
	    }
	    pisadas.push_back(row); // Add the row to the main vector
	}
	//cambia lo cargado por YAML
	Posicion pos = this->mapa->posicionVacia();
	this->juego->escenario->protagonista->set_posicion(pos);

}
void Modelo::insertarEntidades(){
	for(unsigned int i =0; i < this->juego->escenario->entidades.size(); i++){
			Entidad* entidad=this->juego->escenario->entidades[i];
			this->mapa->posicionarEntidad(entidad);
	}
}
void Modelo::setMapa(int ancho,int largo){
	this->mapa=shared_ptr<Mapa>(new Mapa(ancho,largo));
}
void Modelo::actualizarMapa(){
	mapa->actualizar(personajes);
	if(personaje_seleccionado){
			this->mapa->deseleccionar();
	}
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if(!p->estaCongelado()){
			mover_personaje(p);
		}
	}
	struct timeval actual;
	gettimeofday(&actual,NULL);
	double ti = estado.tv_sec+(estado.tv_usec/1000000.0);
	double tf = actual.tv_sec+(actual.tv_usec/1000000.0);
	double tiempo = tf - ti;
	if (tiempo>RITMO){
		this->generarRecursoRandom();
		gettimeofday(&estado,NULL);
	}
}
void Modelo::agregarPersonaje(Personaje* personaje){
	personajes.push_back(personaje);
}
Personaje* Modelo::devolverPersonajeSeleccionado(){
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

int Modelo::oscuridad(int dim,int x,int y){
	for(size_t i = 0; i < this->personajes.size(); i++){
		Posicion pos = personajes[i]->get_posicion();
		agregarPosicion(pos);
		float d = (pos.getX() - x)*(pos.getX() - x) + (pos.getY() - y)*(pos.getY() - y);
		d = sqrt(d);
		if (d < 5){
			Posicion *pos2 = new Posicion(x,y);
			agregarPosicion(*pos2);
			return 0;
		}
	}
	if(pisado(x,y))
		return 1;
	return 2;
}

bool Modelo::pisado(int x, int y){
	return(pisadas[x][y] == 1);
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


bool Modelo::estaSeleccionada(int x,int y){
	if(personaje_seleccionado){
		Posicion pos_p=this->personaje_seleccionado->get_posicion();
		if((pos_p.getX()==x)&&(pos_p.getY()==y)){
			return true;
		}
	}else{
		return (this->mapa->estaSeleccionada(x,y));
	}
	return false;
}

string Modelo::seleccionar(double mov_x,double mov_y){
	this->mapa->deseleccionar();
	Posicion seleccionada= Posicion(mov_x,mov_y);
	if (this->oscuridad(0,seleccionada.getX(),seleccionada.getY())==2){
			return "";
	}
	this->mapa->seleccionar(seleccionada.getX(),seleccionada.getY());
	personaje_seleccionado=this->mapa->personaje_celda(seleccionada.getX(),seleccionada.getY());
	return this->mapa->mostrar_contenido(seleccionada.getX(),seleccionada.getY());
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
	map<Posicion, Posicion,cmp_posiciones> donde_vengo;
	map<Posicion, double,cmp_posiciones> cuanto_recorri;
	pair<Posicion, double> primero(adonde_estoy, 0);
	pila.push(primero);
	donde_vengo.insert(pair<Posicion, Posicion>(adonde_estoy, adonde_estoy));
	cuanto_recorri.insert(primero);
	int cont=0;
	while ((!pila.empty())&&(cont<CICLOS_MAX)) {
		cont++;
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
	if(cont==CICLOS_MAX){
		return adonde_estoy;
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
	}

	//printf("Adonde estoy: X:%g, Y:%g\n",adonde_estoy.get_x_exacta(),adonde_estoy.get_y_exacta());
	//printf("Adonde  voy: X:%g, Y:%g\n",adonde_voy.get_x_exacta(),adonde_voy.get_y_exacta());
	return adonde_voy;
}

void Modelo::agregarPosicion(Posicion pos){
	pisadas[pos.getX()][pos.getY()] = 1;
}


Posicion Modelo::mover_personaje(Personaje* personaje){
	Posicion destino= personaje->get_destino();
	Posicion adonde_estoy= personaje->get_posicion();
	Posicion adonde_voy=calcular_camino(adonde_estoy,destino);
	personaje->set_camino(adonde_voy);
	personaje->mover();
	//Usar cuando el tipo cambia de posicion
	 if ( this->mapa->hayRecursosEn(personaje->get_posicion())){
		Entidad* entidad = this->mapa->entidad_celda(personaje->get_posicion().getX(),personaje->get_posicion().getY());
		Recurso * recurso =(Recurso*)entidad;
		recurso->recolectar(personaje->recursosJugador());
		this->eliminarEntidad(entidad);
	}
	return adonde_voy;
}

void Modelo::congelarPersonaje(Personaje* personaje){
	personaje->congelar();
}
void Modelo::descongelarPersonaje(Personaje* personaje){
	personaje->descongelar();
}
void Modelo::eliminarEntidad(Entidad * entidad){
	this->mapa->sacarEntidad(entidad);
	vector<Entidad*> *lista = &this->juego->escenario->entidades;
	for (unsigned int i=0; i < lista->size(); i++){
		if (entidad->id == (*lista)[i]->id){
			if (i+1!=lista->size())
				std::swap((*lista)[i], lista->back());
			lista->pop_back();

			break;
		}

	}


	//falta sacarla de memoria
}
void  Modelo::cambiar_destino_personaje(double mov_x,double mov_y){
	Personaje* personaje= 	this->devolverPersonajeSeleccionado();
	if((personaje!=NULL)&&(!personaje->estaCongelado())){
		personaje->set_destino(Posicion(mov_x,mov_y));
	}
}
Personaje* Modelo::devolverPersonaje(int x,int y){
	return mapa->personaje_celda(x,y);
}


int Modelo::get_alto_mapa(){
	return mapa->getLargo();
}

int Modelo::get_ancho_mapa(){
	return mapa->getAncho();
}
void Modelo::generarRecursoRandom(){
	Posicion pos;
	Recurso* recurso;
	ObjetoMapa * objeto;
	GeneradorNumeros num;
	if (this->totalRecursos+1>MAX_RECURSOS){
		return;
	}
	pos = this->mapa->posicionVacia();
	int x = pos.getX();
	int y = pos.getY();
	switch (num.numeroRandom(0,3)){
		case 0:
			objeto = this->juego->tipos["oro"];
			recurso = new Oro(objeto,x,y);
			break;
		case 1:
			objeto = this->juego->tipos["madera"];
			recurso = new Madera(objeto,x,y);
			break;
		default:
			objeto = this->juego->tipos["piedra"];
			recurso = new Piedra(objeto,x,y);
			break;
	}

	this->mapa->posicionarEntidad(recurso);
	int size = this->juego->escenario->entidades.size();
	this->juego->escenario->entidades.resize(size+1);
	this->juego->escenario->entidades[size]=recurso;
	this->totalRecursos++;

}

Modelo::~Modelo() {
 delete this->juego;

}


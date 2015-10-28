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
	this->jugador=juego->escenario->jugador;
	personaje_seleccionado=NULL;
	this->insertarEntidades();
	this->totalRecursos=0;
	gettimeofday(&estado,NULL);
	idServer=0;
	for (int i = 0; i < this->juego->escenario->size_x; i++) {
	    vector<int> row; // Create an empty row
	    for (int j = 0; j < this->juego->escenario->size_y; j++) {
	        row.push_back(0); // Add an element (column) to the row
	    }
	    pisadas.push_back(row); // Add the row to the main vector
	}
	//cambia lo cargado por YAML
	//Posicion pos = this->mapa->posicionVacia();
	//this->juego->escenario->protagonista->set_posicion(pos);

}
string Modelo::nombreJugador(){
	return jugador->getNombre();
}
string Modelo::ipJugador(){
	return jugador->getIp();
}
//llama server al agregar personaje
void Modelo::set_posicionRandomPersonaje(Personaje* personaje){
	Posicion pos = this->mapa->posicionVacia();
	personaje->set_posicion(pos);
	//manda en que posicion ubicarlo
}

void Modelo::agregarPersonajeCliente(Personaje* personaje){
	this->personajes.push_back(personaje);
}


//cliente respuesta a moverse o para ubicarlo en lugar
/**void Modelo::ubicarPersonaje(int idPersonaje,Posicion pos){
	//lo estanca si no vuele a calcular el proximo lugar
	vector<Personaje*>::iterator it = personajes.begin();
		for (; it != personajes.end(); ++it) {
			Personaje* p = (*it);
			if(p->getId()==idPersonaje){
				p->set_posicion(pos);
			}
		}

}***/


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
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		mover_personaje(p);
	}

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

//cliente


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

//server
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

//server
Posicion Modelo::mover_personaje(Personaje* personaje){

	Posicion destino= personaje->get_destino();
	Posicion adonde_estoy= personaje->get_posicion();
	if(personaje->estaCongelado()){
		return adonde_estoy;
	}
	Posicion adonde_voy=calcular_camino(adonde_estoy,destino);
	personaje->set_camino(adonde_voy);
	personaje->mover();
	//Usar cuando el tipo cambia de posicion
	recolectar(personaje);
	return adonde_voy;//mandar adonde_voy a cliente
}

//cliente con la cantidad q recolecto
void Modelo::actualizarRecursos(int oro,int madera,int piedra){

	this->personaje_seleccionado->recursosJugador()->colectarMadera(madera);
	this->personaje_seleccionado->recursosJugador()->colectarOro(oro);
	this->personaje_seleccionado->recursosJugador()->colectarPiedra(piedra);
}
void Modelo::actualizarRecursosServer(int id ,int oro,int madera,int piedra){
	vector<Personaje*>::iterator it = personajes.begin();
			for (; it != personajes.end(); ++it) {
				Personaje* p = (*it);
				if(p->getId()==id){
					p->recursosJugador()->colectarMadera(madera);
					p->recursosJugador()->colectarOro(oro);
					p->recursosJugador()->colectarPiedra(piedra);
				}
			}

}

//server
void Modelo::recolectar(Personaje * personaje){
	if (this->mapa->hayRecursosEn(personaje->get_posicion())) {
		Entidad* entidad = this->mapa->entidad_celda(
				personaje->get_posicion().getX(),
				personaje->get_posicion().getY());
		Recurso * recurso = (Recurso*) entidad;
		recurso->recolectar(personaje->recursosJugador());
		//mandar actualizarcion recursos (cuanto aumento)
		this->eliminarEntidad(entidad);
		//mandar eliminar entidad
	}
}
//server
void Modelo::eliminarEntidad(Entidad * entidad){
	eliminarEntidadPorID(entidad->id);
	//falta sacarla de memoria
}

void Modelo::congelarPersonaje(int id){
	vector<Personaje*>::iterator it = personajes.begin();
		for (; it != personajes.end(); ++it) {
			Personaje* p = (*it);
			if(p->getId()==id){
				p->congelar();			}
		}


}
void Modelo::descongelarPersonaje(int id){
	vector<Personaje*>::iterator it = personajes.begin();
		for (; it != personajes.end(); ++it) {
			Personaje* p = (*it);
			if(p->getId()==id){
				p->descongelar();			}
		}


}
//cliente
//elimino una entidad con un solo parametro
void Modelo::eliminarEntidadPorID(int id){
	vector<Entidad*> *lista = &this->juego->escenario->entidades;
	for (unsigned int i = 0; i < lista->size(); i++) {
		if (id == (*lista)[i]->id) {
			this->mapa->sacarEntidad((*lista)[i]);
			if (i + 1 != lista->size())
				std::swap((*lista)[i], lista->back());
			lista->pop_back();
			break;
		}

	}

}
//cliente
void  Modelo::cambiar_destino_personaje(double mov_x,double mov_y){
	Personaje* personaje= 	this->devolverPersonajeSeleccionado();
	if((personaje!=NULL)){
		//cambia su destino, deberia mandarlo hasta q llegue o camine a otro lado
		personaje->set_destino(Posicion(mov_x,mov_y));
	}
}

void  Modelo::cambiar_destino_personaje(string id ,double mov_x,double mov_y){
	vector<Personaje*>::iterator it = personajes.begin();
		for (; it != personajes.end(); ++it) {
			Personaje* p = (*it);
			if(p->getNombreJugador()==id){
				p->set_destino(Posicion(mov_x,mov_y));
			}
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


//server
recurso_t Modelo::generarRecursoRandom(Posicion pos){
	//el tiempo de creacion lo tendria que hacer el server
	//struct timeval actual;
	//gettimeofday(&actual, NULL);
	//double ti = estado.tv_sec + (estado.tv_usec / 1000000.0);
	//double tf = actual.tv_sec + (actual.tv_usec / 1000000.0);
	//double tiempo = tf - ti;
	GeneradorNumeros num;
	recurso_t recurso;
	if ((this->totalRecursos+1>MAX_RECURSOS))/* || (tiempo < RITMO))*/{
		recurso.nombre="";
		recurso.cantidad=0;
		return recurso;
	}
	int x = pos.getX();
	int y = pos.getY();
	string nombre;
	int numero = num.numeroRandom(0,3);
	switch (numero){
		case 0:
			nombre="oro";
			break;
		case 1:
			nombre="madera";
			break;
		default:
			nombre="piedra";
			break;
	}

	int cantidad = this->agregarEntidad(nombre,x,y,0);
	recurso.cantidad = cantidad;
	recurso.nombre = nombre;
	this->totalRecursos++;
	//gettimeofday(&estado,NULL);
	return recurso;

}

//cliente
int Modelo::agregarEntidad(string nombre,int x, int y,int cantidad){
	Entidad* entidad;
	ObjetoMapa * objeto = this->juego->tipos[nombre];
	if (objeto->nombre.compare("oro") == 0)
		entidad = new Oro(objeto, x, y);
	else if (objeto->nombre.compare("piedra") == 0)
		entidad = new Piedra(objeto, x, y);
	else if (objeto->nombre.compare("madera") == 0)
		entidad = new Madera(objeto, x, y);
	else
		entidad = new Entidad(objeto, x, y);
	//para poder agregar con el dato exacto
	this->mapa->posicionarEntidad(entidad);
	int size = this->juego->escenario->entidades.size();
	this->juego->escenario->entidades.resize(size+1);
	this->juego->escenario->entidades[size]=entidad;
	if (cantidad!=0){
			((Recurso *)entidad)->setRecurso(cantidad);
			return ((Recurso *)entidad)->obtenerRecurso();
	}
	return 0;
}
//	Personaje* persona = new Personaje(objeto,pos.get_x_exacta(),pos.get_y_exacta());
void Modelo::crearPersonajeCliente(Personaje* personaje){
	this->personaje_seleccionado=personaje;
	personajes.push_back(personaje);
}



void Modelo::setearPersonajeCliente(int id,Posicion pos){
	this->setIdCliente(id);
	this->personaje_seleccionado->setId(id);
	this->personaje_seleccionado->set_posicion(pos);
}
int Modelo::crearPersonajeServer(Personaje* personaje){
	this->set_posicionRandomPersonaje(personaje);
	personajes.push_back(personaje);
	personaje->setId(idServer);
	idServer++;
	return (idServer-1);
}

int Modelo::getIdCliente()  {
	return idCliente;
}

void Modelo::setIdCliente(int idCliente) {
	this->idCliente = idCliente;
}

int Modelo::cantidad_de_jugadores()  {
	return idServer;
}

Modelo::~Modelo() {
 delete this->juego;

}

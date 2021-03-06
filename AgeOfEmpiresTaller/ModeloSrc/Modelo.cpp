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
#include "Comida.h"
#define RITMO 5
using namespace std;
#define VISIBILIDAD 8
#define VISIBILIDAD_CONSTRUCCIONES 10
#define CICLOS_MAX 500
#define ORO 0
#define PIEDRA 1
#define COMIDA 2
#define DIMENSIONES 2 //TILE Y ESCENARIO
enum dimension {
	TILES, ESCENARIO
};

Modelo::Modelo(Juego* juego) {
	this->acumuladorPiso = 0;
	this->juego = juego;
	//setMapa(this->juego->escenario->size_x, this->juego->escenario->size_y);
	this->personajes = vector<Personaje*>();
	this->pisadas = vector<vector<int>>();
	this->jugador = juego->escenario->jugador;
	if (this->jugador) {
		this->jugador->cargarEdificios(this->juego->tipos);
	}
	this->factory_personaje.cargarPersonajes(this->juego->tipos);
	personajes_seleccionados.clear();
	this->totalRecursos = 0;
	gettimeofday(&estado, NULL);
	idServer = 0;
	entidad_seleccionada = NULL;
}
string Modelo::nombreJugador() {
	return jugador->getNombre();
}
//llama server al agregar personaje
void Modelo::set_posicionRandomPersonaje(Personaje* personaje) {
	//Posicion pos = this->mapa->posicionVacia();
	Posicion pos(8, 8);
	personaje->set_posicion(pos);
	//manda en que posicion ubicarlo
}

Entidad* Modelo::set_CentroCivicoNuevoServer(string raza) {
	Entidad* base = this->juego->centroCivicoDe(raza);
	if (base) {
		vector<Entidad*> centros = this->obtenerCentrosCivicosEnMapa();
		Posicion pos = this->mapa->posicionValidaParaCentroCivico(centros, base);

		base->set_posicion(pos.getX(), pos.getY());
		base->finalizarConstruccion();
		this->insertarEntidad(base);
	} else {
		printf("ERROR no existe centro civico de esa raza\n");
	}
	base->cargarPersonajes(factory_personaje.devolverTipos(base->objetoMapa->nombre));
	return base;
}

vector<Entidad *> Modelo::obtenerCentrosCivicosEnMapa() {
	vector<Entidad*> centrosCivicos;
	vector<Entidad*>::iterator it = this->juego->escenario->entidades.begin();
	for (; it != this->juego->escenario->entidades.end(); ++it) {
		if ((*it)->esUnCentroCivio()) {
			centrosCivicos.push_back(*it);
		}
	}
	return centrosCivicos;
}
bool Modelo::puedoCrearSiEsPuerto(Entidad* entidad) {
	bool es_puerto=false;;
	map<string,ObjetoMapa*> dicc =factory_personaje.devolverTipos(entidad->objetoMapa->nombre);
	if(!dicc.empty()){
		for (std::map<string,ObjetoMapa*>::iterator it=dicc.begin(); it!=dicc.end(); ++it){
			if(it->second->es_bote){
				es_puerto=true;
			}
		}

	}
	if(!es_puerto){
		return true;
	}
	return mapa->puedeUbicarPuerto(entidad);

}

void Modelo::agregarPersonajeCliente(Personaje* personaje) {
	this->personajes.push_back(personaje);
}
vector<msg_t> Modelo::eliminar_personaje_por_Id(Id id) {
	vector<msg_t> terminados;
	Personaje * pers = this->get_Personaje_Por_Id(id);
	if (pers) {
		terminados = this->eliminar_personaje(pers);
	}

	return terminados;
}

void Modelo::insertarEntidades() {
	for (unsigned int i = 0; i < this->juego->escenario->entidades.size(); i++) {
		Entidad* entidad = this->juego->escenario->entidades[i];
		this->mapa->posicionarEntidad(entidad);
	}
}

void Modelo::setMapa(int ancho, int largo) {
	this->mapa = shared_ptr<Mapa>(new Mapa(ancho, largo));
	this->mapa->hacerPileta(3*ancho/8,3*largo/8);
	this->insertarEntidades();
	vector<int> row(ancho, OSCURO);
	for (int i = 0; i < largo; i++) {
		pisadas.push_back(row);
	}
}

void Modelo::actualizarMapa() {
	mapa->actualizar(personajes);
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		mover_personaje(p);
	}

}
void Modelo::finalizarAccion(int id) {
	this->get_Personaje_Por_Id(id)->noInteractua();
}
vector<msg_t> Modelo::eliminar_personaje(Personaje* eliminado) {
	vector<msg_t> terminados;
	vector<Personaje*>::iterator it = personajes.begin();
	printf("Elimina\n");
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->esta_atacando()) {
			if (p->get_atacado_id() == eliminado->getId()) {
				p->terminarAccion();
				msg_t terminar;
				terminar.type = TERMINAR_ACCION;
				terminar.paramInt1 = p->getId();
				terminados.push_back(terminar);
				printf("cargo terminar\n");
			}
		}
	}
	it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p == eliminado) {
			personajes.erase(it);
			break;

		}

	}
	it = personajes_seleccionados.begin();
	for (; it != personajes_seleccionados.end(); ++it) {
		Personaje* p = (*it);
		printf("Borra seleccionado\n");
		if (p == eliminado) {
			personajes_seleccionados.erase(it);
			break;

		}

	}
	return terminados;
}
vector<msg_t> Modelo::eliminar(int id) {
	//faltaria poner que si elimino personaje no se meta en eliminar entidad
	vector<msg_t> terminados =	this->eliminar_personaje_por_Id(id);
	if (terminados.empty()){
		terminados = this->eliminarEntidadPorID(id);
	}
	return terminados;
}
vector<Personaje*> Modelo::devolverPersonajeSeleccionado() {
	return personajes_seleccionados;
}
bool Modelo::afueraDelMapa(int x, int y) {
	return this->mapa->afueraDelMapa(x, y);
}
vector<Personaje*> Modelo::devolverTodosLosPersonajes() {
	return personajes;
}

void Modelo::cambiar_personaje(Id id_personaje, string nombre,string raza){
	Personaje* p =this->get_Personaje_Por_Id(id_personaje);
	if(p){
		printf("Nombre: %s Raza : %s \n",nombre.c_str(),raza.c_str());
		p->setNombreJugador(nombre);
		p->set_raza(raza);
	}
}

void Modelo::setDibujoMapa(vector<vector<dibujo_t>> escenario, vector<vector<vector<dibujo_t>>> tiles) {
	int ancho = this->mapa->getAncho();
	int largo = this->mapa->getLargo();
	int i = 0, j = 0;
	for (i = 0; i < ancho; i++) {
		for (j = 0; j < largo; j++) {
			this->mapa->setEscenario(escenario[i][j], i, j);

			vector<dibujo_t> vTiles = tiles[i][j];

			this->mapa->setTiles(vTiles[this->acumuladorPiso],vTiles[this->acumuladorPiso + 4],vTiles[this->acumuladorPiso + 8],vTiles[this->acumuladorPiso + 12],vTiles[this->acumuladorPiso + 16],vTiles[this->acumuladorPiso + 20], i, j);

			if(this->acumuladorPiso == 3) {
				this->acumuladorPiso = 0;
			} else
			this->acumuladorPiso++;
		}
	}
}

int Modelo::oscuridad(int dim, int x, int y) {

	vector<Entidad*> lista = this->juego->escenario->entidades;
	for (unsigned int i = 0; i < lista.size(); i++) {

		Posicion pos = lista[i]->get_posicion();
		float d = (pos.getX() - x) * (pos.getX() - x) + (pos.getY() - y) * (pos.getY() - y);
		d = sqrt(d);
		if (d < VISIBILIDAD_CONSTRUCCIONES) {

			if (lista[i]->get_raza() == "Elfo") {
				Celda* celda = this->mapa->getCelda(x, y);
				celda->mostrarTileElfo();
			}
			if (lista[i]->get_raza() == "Hobbit") {
				Celda* celda = this->mapa->getCelda(x, y);
				celda->mostrarTileHobbit();
			}
			if (lista[i]->get_raza() == "Humano") {
				Celda* celda = this->mapa->getCelda(x, y);
				celda->mostrarTileHumanos();
			}
			if (lista[i]->get_raza() == "Mordor") {
				Celda* celda = this->mapa->getCelda(x, y);
				celda->mostrarTileMordor();
			}
			if (lista[i]->objetoMapa->raza == this->getJugador()->raza) {
				agregarPosicionPisada(x, y);
				return VISIBLE;
			}

		}
	}
	for (size_t i = 0; i < this->personajes.size(); i++) {
		if (personajes[i]->getNombreJugador() == this->nombreJugador()) {
			Posicion pos = personajes[i]->get_posicion();
			//agregarPosicion(x,y);
			float d = (pos.getX() - x) * (pos.getX() - x) + (pos.getY() - y) * (pos.getY() - y);
			d = sqrt(d);
			if (d < VISIBILIDAD) {
				agregarPosicionPisada(x, y);
				return VISIBLE;
			}
		}
	}
	if (pisado(x, y)) {
		return PISADA;
	}
	return OSCURO;
}

bool Modelo::pisado(int x, int y) {
	return (pisadas[x][y] == PISADA);
}

dibujo_t Modelo::dibujar(int dim, int x, int y) {
	if (dim == ESCENARIO) {
		return this->mapa->dibujarEscenario(x, y);
	}
	return this->mapa->dibujarTiles(x, y);
}

bool Modelo::celdaOcupada(Posicion posicion) {
	return this->mapa->celdaOcupada(posicion.getX(), posicion.getY());
}

//cliente

bool Modelo::estaSeleccionada(int x, int y) {
	if (!personajes_seleccionados.empty()) {
		Posicion pos_p = this->personajes_seleccionados[0]->get_posicion();
		if ((pos_p.getX() == x) && (pos_p.getY() == y)) {
			return true;
		}
	} else {
		return (this->mapa->estaSeleccionada(x, y));
	}
	return false;
}
void Modelo::limpiarSeleccion() {
	personajes_seleccionados.clear();
}

DatosSeleccionado Modelo::seleccionar(double mov_x, double mov_y) {
	this->mapa->deseleccionar();
	Posicion seleccionada = Posicion(mov_x, mov_y);
	if (this->oscuridad(TILES, seleccionada.getX(), seleccionada.getY()) == OSCURO) {
		DatosSeleccionado datos;
		return datos;
	}
	this->mapa->seleccionar(seleccionada.getX(), seleccionada.getY());
	entidad_seleccionada = NULL;
	if (this->mapa->personaje_celda(seleccionada.getX(), seleccionada.getY())) {
		if(personajes_seleccionados.size() < SELECCION_MAXIMA){
			personajes_seleccionados.push_back(this->mapa->personaje_celda(seleccionada.getX(), seleccionada.getY()));
		}

	} else {
		if (this->mapa->entidad_celda(seleccionada.getX(), seleccionada.getY()) != NULL) {
			entidad_seleccionada = this->mapa->entidad_celda(seleccionada.getX(), seleccionada.getY());
		}
		this->limpiarSeleccion();
	}
	return this->mapa->mostrar_contenido(seleccionada.getX(), seleccionada.getY());
}

Entidad * Modelo::get_entidad_seleccionada() {
	return entidad_seleccionada;
}

double Modelo::heuristica(Posicion adonde_voy, Posicion adonde_estoy) {
	return adonde_voy.distancia_octal(adonde_estoy);
}
double Modelo::distancia(Posicion a, Posicion b) {
	return a.distancia_octal(b);
}

//server
Posicion Modelo::calcular_camino(Posicion adonde_estoy, Posicion adonde_voy,bool es_bote) {
	/**
	 *http://www.redblobgames.com/pathfinding/a-star/introduction.html
	 **/
	if (adonde_estoy == adonde_voy) {
		return adonde_voy;
	}
	adonde_voy = mapa->validar_destino(adonde_voy, adonde_estoy,es_bote);
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>, CompDistancias> pila;
	map<Posicion, Posicion, cmp_posiciones> donde_vengo;
	map<Posicion, double, cmp_posiciones> cuanto_recorri;
	pair<Posicion, double> primero(adonde_estoy, 0);
	pila.push(primero);
	donde_vengo.insert(pair<Posicion, Posicion>(adonde_estoy, adonde_estoy));
	cuanto_recorri.insert(primero);
	int cont = 0;
	while ((!pila.empty()) && (cont < CICLOS_MAX)) {
		cont++;
		pair<Posicion, double> actual = pila.top();
		Posicion posicion_actual = actual.first;
		pila.pop();
		if (posicion_actual == adonde_voy) {
			break;
		}
		vector<Posicion> adyacentes = mapa->adyacenciasNoOcupadas(actual.first,es_bote);
		vector<Posicion>::iterator it = adyacentes.begin();
		for (; it != adyacentes.end(); ++it) {
			Posicion ady = (*it);
			double nueva_distancia = cuanto_recorri[posicion_actual] + distancia(ady, posicion_actual);
			if ((!(cuanto_recorri.count(ady))) || (nueva_distancia < cuanto_recorri[ady])) {
				cuanto_recorri[ady] = nueva_distancia;
				double prioridad = nueva_distancia + heuristica(adonde_voy, ady);
				pila.push(pair<Posicion, double>(ady, prioridad));
				donde_vengo[ady] = posicion_actual;

			}
		}
	}
	if ((cont == CICLOS_MAX) || (donde_vengo.count(adonde_voy) == 0)) {
		return adonde_estoy;
	}

	stack<Posicion> camino;
	camino.push(adonde_voy);
	Posicion anterior = adonde_voy;
	while (!(adonde_estoy == anterior)) {
		camino.push(donde_vengo[anterior]);
		anterior = donde_vengo[anterior];
	}
	camino.pop();
	if (!camino.empty()) {
		adonde_voy = camino.top();
	}
	while (!camino.empty()) {
		Posicion pos = camino.top();
		camino.pop();
	}

	return adonde_voy;
}

void Modelo::agregarPosicionPisada(int x, int y) {
	pisadas[x][y] = PISADA;
}

//server
Posicion Modelo::mover_personaje(Personaje * personaje) {

	Posicion destino = personaje->get_destino();
	Posicion adonde_estoy = personaje->get_posicion();
	if (personaje->estaCongelado()) {
		return adonde_estoy;
	}
	Posicion adonde_voy = calcular_camino(adonde_estoy, destino,personaje->esUnBote());
	personaje->set_camino(adonde_voy);
	personaje->mover();
	return adonde_voy; //mandar adonde_voy a cliente
}

//cliente con la cantidad q recolecto
void Modelo::actualizarRecursos(string jugador, int id_pers, int cant, int id_rec) {
	Personaje * p = this->get_Personaje_Por_Id(id_pers);
	p->atacandoCliente(true);
	Recurso * recurso = (Recurso *) this->buscarEntidad(id_rec);
	if (this->jugador->getNombre() == jugador) {
		recurso->recolectar(this->jugador->recursosJugador(), cant);
	} else {
		recurso->sacarRecurso(cant);
	}

}

Entidad * Modelo::buscarEntidad(int id) {
	vector<Entidad*> *lista = &this->juego->escenario->entidades;
	for (unsigned int i = 0; i < lista->size(); i++) {
		if ((*lista)[i]->getId() == id) {
			return (*lista)[i];
		}
	}
	return NULL; //cuando no lo encuentra
}

//server
void Modelo::recolectar(Personaje * personaje, Recurso * recurso) {
	//puede enlentecerse con muuuchas entidades pero
	if (recurso != NULL) {
		if (personaje->esAdyacente(recurso)) {
			//recoleccin a los recursos del jugador personaje->getRecoleccion()
			recurso->recolectar(personaje->recursosJugador(), personaje->getRecoleccion());
		}

	} else {
		personaje->terminarAccion();
	}

}
//server
vector<msg_t> Modelo::eliminarEntidad(Entidad * entidad) {
	return eliminarEntidadPorID(entidad->id);
	//falta sacarla de memoria
}

void Modelo::congelarPersonaje(string id) {
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->getNombreJugador() == id) {
			p->congelar();
		}
	}
}

void Modelo::descongelarPersonaje(string id) {
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->getNombreJugador() == id) {
			p->descongelar();
		}
	}
}

vector<Entidad*> Modelo::obtenerEntidadesDeInicializacion() {
	return this->juego->escenario->entidades;
}

//cliente
vector<msg_t> Modelo::eliminarEntidadPorID(int id) {
	vector<msg_t> terminados;
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->esta_recolectando()) {
			if (p->get_objetivo()->getId() == id) {
				p->terminarAccion();
				msg_t terminar;
				terminar.type = TERMINAR_ACCION;
				terminar.paramInt1 = p->getId();
				terminados.push_back(terminar);
				printf("cargo terminar\n");
			}

		}
		if (p->esta_atacando()) {
			if (p->get_atacado()->getId() == id) {
				p->terminarAccion();
				msg_t terminar;
				terminar.type = TERMINAR_ACCION;
				terminar.paramInt1 = p->getId();
				terminados.push_back(terminar);
				printf("cargo terminar\n");
			}

		}
	}
	vector<Entidad*> *lista = &this->juego->escenario->entidades;
	Entidad *entidad;
	for (unsigned int i = 0; i < lista->size(); i++) {
		if (id == (*lista)[i]->id) {
			this->mapa->sacarEntidad((*lista)[i]); //desreferencio del mapa
			if (i + 1 != lista->size()) {
				entidad = (*lista)[i];
				std::swap((*lista)[i], lista->back());
			}
			lista->pop_back();
			entidad = NULL;
			break;
		}

	}
	return terminados;

}

//cliente
/**void  Modelo::cambiar_destino_personaje(double mov_x,double mov_y){
 Personaje* personaje= 	this->devolverPersonajeSeleccionado();
 if((personaje!=NULL)){
 //cambia su destino, deberia mandarlo hasta q llegue o camine a otro lado
 personaje->set_destino(Posicion(mov_x,mov_y));
 }
 }**/

void Modelo::cambiar_destino_personaje(Id id, double mov_x, double mov_y) {
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {

		Personaje* p = (*it);
		if (p->getId() == id) {
			p->set_destino(Posicion(mov_x, mov_y));
		}
	}

}
Personaje* Modelo::get_Personaje_Por_Id(Id id) {
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->getId() == id) {
			return p;
		}
	}
	return NULL;
}
void Modelo::atacarServer(Id idAtacante, Id idAtacado) {
	Personaje* atacado = this->get_Personaje_Por_Id(idAtacado);
	Personaje* atacante = this->get_Personaje_Por_Id(idAtacante);
	if (atacado) {
		atacante->set_ataque(atacado);
	} else {
		Entidad* entidad = this->buscarEntidad(idAtacado);
		if (entidad) {
			atacante->set_ataque(entidad);
		}
	}

}
Personaje* Modelo::devolverPersonaje(int x, int y) {
	return mapa->personaje_celda(x, y);
}

int Modelo::get_alto_mapa() {
	return mapa->getLargo();
}

int Modelo::get_ancho_mapa() {
	return mapa->getAncho();
}

//server
recurso_t Modelo::generarRecursoRandom(Posicion pos) {
	//el tiempo de creacion lo tendria que hacer el server
	//struct timeval actual;
	//gettimeofday(&actual, NULL);
	//double ti = estado.tv_sec + (estado.tv_usec / 1000000.0);
	//double tf = actual.tv_sec + (actual.tv_usec / 1000000.0);
	//double tiempo = tf - ti;
	GeneradorNumeros num;
	recurso_t recurso;
	int x = pos.getX();
	int y = pos.getY();
	Entidad * entidad;
	ObjetoMapa * objeto;
	string nombre;
	int numero = num.numeroRandom(0, 4);
	switch (numero) {
	case ORO:
		nombre = "oro";
		objeto = this->juego->tipos["oro"];
		entidad = new Oro(objeto, x, y);
		break;
	case PIEDRA:
		nombre = "madera";
		objeto = this->juego->tipos["madera"];
		entidad = new Madera(objeto, x, y);
		break;

	case COMIDA:
		nombre = "comida";
		objeto = this->juego->tipos["comida"];
		entidad = new Comida(objeto, x, y);
		break;
	default:
		objeto = this->juego->tipos["piedra"];
		nombre = "piedra";
		entidad = new Piedra(objeto, x, y);
		break;
	}
	this->insertarEntidad(entidad);
	int cantidad = ((Recurso *) entidad)->obtenerRecurso();
	recurso.cantidad = cantidad;
	recurso.nombre = nombre;
	this->totalRecursos++;
	//gettimeofday(&estado,NULL);
	return recurso;

}

void Modelo::insertarEntidad(Entidad *entidad) {
	this->mapa->posicionarEntidad(entidad);
	this->juego->escenario->entidades.push_back(entidad);
}

//cliente
int Modelo::agregarEntidad(string nombre, int x, int y, int cantidad) {
	Entidad* entidad;
	ObjetoMapa * objeto = this->juego->tipos[nombre];
	if (!objeto)
		return 0;
	if (objeto->nombre.compare("oro") == 0)
		entidad = new Oro(objeto, x, y);
	else if (objeto->nombre.compare("piedra") == 0)
		entidad = new Piedra(objeto, x, y);
	else if (objeto->nombre.compare("madera") == 0)
		entidad = new Madera(objeto, x, y);
	else if (objeto->nombre.compare("comida") == 0)
		entidad = new Comida(objeto, x, y);
	else
		entidad = new Entidad(objeto, x, y);
	entidad->cargarPersonajes(factory_personaje.devolverTipos(objeto->nombre));

	this->insertarEntidad(entidad);

	if (entidad->esUnRecurso()) {
		((Recurso *) entidad)->setRecurso(cantidad);
		return ((Recurso *) entidad)->obtenerRecurso();
	}
	return 0;
}

bool Modelo::tocaSombra(Entidad * entidad) {
	int ancho, alto, x, y;
	ancho = entidad->objetoMapa->baseLogica->ancho;
	alto = entidad->objetoMapa->baseLogica->alto;
	for (x = 0; x < ancho; x++) {
		for (y = 0; y < alto; y++) {
			if (this->oscuridad(0, entidad->get_posicion().getX() + x, entidad->get_posicion().getY() + y)) {
				return true;
			}
		}
	}
	return false;
}
//server
int Modelo::crearEdificio(string nombre, int x, int y) {
	ObjetoMapa*objeto = this->juego->tipos[nombre];
	Entidad * entidad = new Entidad(objeto);
	entidad->set_posicion(x, y);
	entidad->cargarPersonajes(factory_personaje.devolverTipos(objeto->nombre));
	if (this->mapa->puedeUbicar(entidad)) {
		this->insertarEntidad(entidad);
		return entidad->getId();
	}
	return EDIFICIO_SUPERPUESTO;
}

int Modelo::crearPersonajeServer(Personaje* personaje) {
	this->set_posicionRandomPersonaje(personaje);
	personajes.push_back(personaje);
	GeneradorNumeros generar;
	int id = personaje->getId();
	return (id);
}
vector<msg_t> Modelo::terminarConstruccion(int id){
	vector<msg_t> terminados;
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->esta_contruyendo()){
			if (p->get_objetivo()->getId()==id){
				p->terminarAccion();
				msg_t terminar;
				terminar.type = TERMINAR_ACCION;
				terminar.paramInt1 = p->getId();
				terminados.push_back(terminar);
			}
		}
	}
	return terminados;
}
int Modelo::crearPersonajeServerEdificio(Personaje* personaje, Id id_edificio) {
	Entidad* edificio = this->buscarEntidad(id_edificio);
	printf(personaje->esUnBote()?"Es un bote\n":"No es un bote\n");
	printf("%s\n",personaje->getNombreTipo().c_str());
	Posicion pos = this->mapa->encontrarAdyacenteMasCercano(edificio->get_posicion(),personaje->esUnBote());
	if(pos==Posicion(-1,-1))return -1;
	personaje->set_posicion(pos);
	this->mapa->posicionarPersonaje(personaje);
	personajes.push_back(personaje);
	int id = personaje->getId();
	return (id);
}

int Modelo::crearBandera(Entidad* bandera, Id id_edificio) {
	Entidad* edificio = this->buscarEntidad(id_edificio);
	Posicion pos = this->mapa->encontrarAdyacenteMasCercano(edificio->get_posicion(),false);
	bandera->set_posicion(pos.getX(), pos.getY());
	this->insertarEntidad(bandera);
	int id = bandera->getId();
	return id;
}

Modelo::~Modelo() {
	delete this->juego;

}

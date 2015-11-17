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
	this->celdas = celdas;
}
void Mapa::seleccionar(int x, int y) {
	return this->celdas[x][y]->seleccionarEntidad();
}
bool Mapa::estaSeleccionada(int x, int y) {
	return (this->celdas[x][y]->estaSeleccionada());
}
void Mapa::deseleccionar() {
	int i, j;
	for (int i = 0; i < ancho; i++) {
		for (int j = 0; j < largo; j++) {
			this->getCelda(i, j)->deseleccionarEntidad();
		}
	}
}
Celda* Mapa::getCelda(int x, int y) {
	return this->celdas[x][y];
}
void Mapa::setTiles(dibujo_t dibujo, int x, int y) {
	this->getCelda(x, y)->setTiles(dibujo);
}
void Mapa::setEscenario(dibujo_t dibujo, int x, int y) {
	this->getCelda(x, y)->setEscenario(dibujo);
}
DatosSeleccionado Mapa::mostrar_contenido(int x, int y) {
	return this->getCelda(x, y)->mostrar_contenido();
}
DatosSeleccionado Mapa::mostrar_entidad(int x, int y) {
	return this->getCelda(x, y)->mostrar_entidad();
}
Entidad* Mapa::entidad_celda(int x, int y) {
	return this->getCelda(x, y)->devolver_entidad();
}
bool Mapa::celdaOcupada(int x, int y) {
	Celda* celda = this->getCelda(x, y);
	if (celda == NULL) {
		return false;
	}
	return (celda->estaOcupada());
}
dibujo_t Mapa::dibujarEscenario(int x, int y) {
	if ((y >= this->largo) || (x >= this->ancho) || (y < 0) || (x < 0)) {
		return AFUERA;
	}
	return this->getCelda(x, y)->dibujarEscenario();
}
Personaje* Mapa::personaje_celda(int x, int y) {
	return this->getCelda(x, y)->devolver_personaje();
}
bool Mapa::hay_personaje(int x, int y) {
	return (this->getCelda(x, y)->devolver_personaje() != NULL);
}
dibujo_t Mapa::dibujarTiles(int x, int y) {
	if ((y >= this->largo) || (x >= this->ancho) || (y < 0) || (x < 0)) {
		return AFUERA;
	}
	return this->getCelda(x, y)->dibujarTiles();
}
void Mapa::actualizar(vector<Personaje*> personajes) {
	for (int i = 0; i < ancho; i++) {
		for (int j = 0; j < largo; j++) {
			this->getCelda(i, j)->actualizar();
		}
	}
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		Posicion pos = p->get_posicion();
		this->getCelda(pos.getX(), pos.getY())->ocuparCeldaPersonaje(p);
	}
}

int Mapa::getAncho() {
	return this->ancho;
}
int Mapa::getLargo() {
	return this->largo;
}
bool Mapa::afueraDelMapa(int x, int y) {
	return ((y >= this->largo) || (x >= this->ancho) || (y < 0) || (x < 0));
}

double cuantoMeAcerco(int actual, int acercarme) {
	if (actual == acercarme) {
		return 0;
	}
	double factor = 0.75;
	if (actual < acercarme) {
		return factor;
	} else {
		return 1 - factor;
	}

}
Posicion Mapa::acercar(Posicion adonde_estoy, Posicion adonde_voy) {
	double x_factor, y_factor;
	int x_estoy = adonde_estoy.getX();
	int y_estoy = adonde_estoy.getY();
	int x_voy = adonde_voy.getX();
	int y_voy = adonde_voy.getY();
	x_factor = cuantoMeAcerco(x_estoy, x_voy);
	y_factor = cuantoMeAcerco(y_estoy, y_voy);
	Posicion pos = { (double) x_estoy + x_factor, (double) y_estoy + y_factor };
	return pos;

}
Posicion Mapa::validar_destino(Posicion adonde_voy, Posicion adonde_estoy) {
	if (afueraDelMapa(adonde_voy.getX(), adonde_voy.getY())) {
		return adonde_estoy;
	}

	bool celdaOcupad = celdaOcupada(adonde_voy.getX(), adonde_voy.getY());
	//bool esAdyacente = adonde_voy.es_adyacente(adonde_estoy);

	if ((adonde_estoy == adonde_voy) || (!celdaOcupad)) {
		return adonde_voy;
	}

	bool esAdyacente;
	Entidad* entidad = this->entidad_celda(adonde_voy.getX(), adonde_voy.getY());
	if (entidad) {
		esAdyacente = entidad->esAdyacente(adonde_estoy);
		if (esAdyacente)
			return this->acercar(adonde_estoy, adonde_voy);
	} else {
		esAdyacente = adonde_voy.es_adyacente(adonde_estoy);
		if ((esAdyacente) && (celdaOcupad))
			return this->acercar(adonde_estoy, adonde_voy);
	}

//printf("Voy hacia uno ocupado\n");
	adonde_voy = Posicion(adonde_voy.getX(), adonde_voy.getY());
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>, CompDistancias> pila_no_ocupadas;
	priority_queue<pair<Posicion, double>, vector<pair<Posicion, double>>, CompDistancias> pila_ocupadas;
	pila_ocupadas.push(pair<Posicion, double>(adonde_voy, adonde_voy.distancia_octal(adonde_estoy)));
	while (pila_no_ocupadas.empty()) {
		Posicion ocupado_mas_cercano = pila_ocupadas.top().first;
		//printf("Ocupado: %d,%d\n",ocupado_mas_cercano.getX(),ocupado_mas_cercano.getY());
		vector<Posicion> adyacentes_no_ocupados = adyacenciasNoOcupadas(ocupado_mas_cercano);
		vector<Posicion>::iterator it = adyacentes_no_ocupados.begin();
		for (; it != adyacentes_no_ocupados.end(); ++it) {
			Posicion ady = (*it);
			//printf("No Ocupado: %d,%d\n",ady.getX(),ady.getY());
			pila_no_ocupadas.push(pair<Posicion, double>(ady, adonde_voy.distancia_octal(ady) + adonde_estoy.distancia_octal(ady)));
		}
		if (!pila_no_ocupadas.empty()) {
			//printf("No Ocupado Elegido: %d,%d\n",pila_no_ocupadas.top().first.getX(),pila_no_ocupadas.top().first.getY());

			return pila_no_ocupadas.top().first;
		} else {
			vector<Posicion> adyacentes_ocupados = adyacencias(ocupado_mas_cercano);
			vector<Posicion>::iterator it = adyacentes_ocupados.begin();
			for (; it != adyacentes_ocupados.end(); ++it) {
				//printf("en for de ocupadas\n");
				Posicion ady = (*it);
				//printf("%d,%d\n",ady.getX(),ady.getY());
				pila_ocupadas.push(pair<Posicion, double>(ady, adonde_estoy.distancia_octal(ady)));
			}
		}
	}
	return pila_no_ocupadas.top().first;
}
vector<Posicion> Mapa::adyacencias(Posicion posicion) {
	vector<Posicion> adyacentes = vector<Posicion>();
	int x = posicion.getX(), y = posicion.getY();
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (!((i == x) && (j == y))) {
				adyacentes.push_back(Posicion(i, j));
			}
		}
	}
	return adyacentes;
}
bool Mapa::estoyAlLadoDeEntidadDestino(Posicion adonde_voy, Posicion adonde_estoy) {
	Entidad* entidad = this->entidad_celda(adonde_voy.getX(), adonde_voy.getY());
	if (entidad) {
		return entidad->esAdyacente(adonde_estoy);
	}
	return false;
}
vector<Posicion> Mapa::adyacenciasNoOcupadas(Posicion posicion) {
	vector<Posicion> adyacentes = vector<Posicion>();
	int x = posicion.getX(), y = posicion.getY();
	Entidad* entidad = this->entidad_celda(x, y);
	if (entidad) {
		x = x + entidad->objetoMapa->baseLogica->ancho;
		y = y + entidad->objetoMapa->baseLogica->alto;
	}

	for (int i = x + 1, j = y + 1; i > x - 2; i -= 2, j -= 2) {
		if ((!afueraDelMapa(i, j)) && (!celdaOcupada(i, j)) && (!celdaOcupada(x, j)) && (!celdaOcupada(i, y))) {
			adyacentes.push_back(Posicion(i, j));
		}
	}
	for (int i = x - 1, j = y - 1; i < x + 2; i += 2, j += 2) {
		if ((!afueraDelMapa(i, j)) && (!celdaOcupada(i, j)) && (!celdaOcupada(x, j)) && (!celdaOcupada(i, y))) {
			adyacentes.push_back(Posicion(i, j));
		}
	}

	for (int j = y - 1; j < y + 2; j += 2) {
		if ((!afueraDelMapa(x, j)) && (!celdaOcupada(x, j))) {
			adyacentes.push_back(Posicion(x, j));
		}
	}

	for (int i = x - 1; i < x + 2; i += 2) {
		if ((!afueraDelMapa(i, y)) && (!celdaOcupada(i, y))) {
			adyacentes.push_back(Posicion(i, y));
		}
	}
	return adyacentes;
}
Posicion Mapa::encontrarAdyacenteMasCercano(Posicion posicion) {
	queue<Posicion> pila;
	pila.push(posicion);
	while (!pila.empty()) {
		Posicion p = pila.front();
		pila.pop();
		vector<Posicion> adyacentes_no_ocupados = this->adyacenciasNoOcupadas(p);
		if (adyacentes_no_ocupados.empty()) {
			vector<Posicion> adyacentes = this->adyacencias(p);
			vector<Posicion>::iterator it = adyacentes.begin();
			for (; it != adyacentes.end(); ++it) {
				Posicion ady = (*it);
				pila.push(ady);
			}

		} else {
			return adyacentes_no_ocupados.front();
		}
	}
}

void Mapa::posicionarPersonaje(Personaje * pers) {
	this->getCelda(pers->get_posicion().getX(), pers->get_posicion().getY())->ocuparCeldaPersonaje(pers);
}

void Mapa::posicionarEntidad(Entidad* entidad) {
	int i, j, x, y, alto, ancho;
	alto = entidad->objetoMapa->baseLogica->alto;
	ancho = entidad->objetoMapa->baseLogica->ancho;
	x = entidad->posicion->getX();
	y = entidad->posicion->getY();
	for (i = x; i < alto + x; i++) {
		for (j = y; j < ancho + y; j++) {
			this->getCelda(i, j)->ocuparCelda(entidad); //guardar referencias en celdas
		}
	}
	this->getCelda(x, y)->ocuparCelda(entidad); //guardar referencias en celdas

}
void Mapa::sacarEntidad(Entidad * entidad) {
	int i, j, x, y, alto, ancho;
	alto = entidad->objetoMapa->baseLogica->alto;
	ancho = entidad->objetoMapa->baseLogica->ancho;
	x = entidad->posicion->getX();
	y = entidad->posicion->getY();
	for (i = x; i < alto + x; i++) {
		for (j = y; j < ancho + y; j++) {
			this->getCelda(i, j)->liberarCelda();
		}
	}
}

Posicion Mapa::posicionVacia() {
	GeneradorNumeros num;
	int x;
	int y;
	Celda * celda;
	do {
		x = num.numeroRandom(0, this->ancho);
		y = num.numeroRandom(0, this->largo);
		celda = this->getCelda(x, y);
	} while (celda->estaOcupada());
	Posicion pos = { x, y };
	return pos;
}
bool Mapa::hayRecursosEn(Posicion posicion) {
	return this->getCelda(posicion.getX(), posicion.getY())->tieneRecurso();
}
bool Mapa::puedeUbicar(Entidad* entidad) {
	Posicion pos = entidad->get_posicion();
	int x, y, ancho, alto;
	ancho = entidad->objetoMapa->baseLogica->ancho;
	alto = entidad->objetoMapa->baseLogica->alto;
	for (x = pos.getX(); x < pos.getX() + ancho; x++) {
		for (y = pos.getY(); y < pos.getY() + alto; y++) {
			if (this->getCelda(x, y)->estaOcupada()) {
				return false;
			}
		}
	}
	return true;
}

Posicion Mapa::posicionValidaParaCentroCivico(vector<Entidad*> centros, Entidad * base) {
//devuelve una posicion valida en el mapa
	Posicion pos;

//Lo puede hacer un for per ya fueee
//MALDAD AL MAXIMO
	vector<Posicion> sectores;
	Posicion sector1 = { 0, 0 };
	Posicion sector2 = { this->getAncho() / 2, 0 };
	Posicion sector3 = { 0, this->getLargo() / 2 };
	Posicion sector4 = { this->getAncho() / 2, this->getLargo() / 2 };
	sectores.push_back(sector1);
	sectores.push_back(sector2);
	sectores.push_back(sector3);
	sectores.push_back(sector4);
	vector<Entidad*>::iterator it = centros.begin();
	vector<Posicion>::iterator it_pos = sectores.begin();
//por cada centro civico
	for (; it != centros.end(); ++it) {
		//printf("L2Por centro en mapa\n");
		for (; it_pos != sectores.end(); ++it_pos) {
			//elimina el sector donde se encuentra

			if (this->estaDentroDeSector(*it_pos, (*it)->get_posicion())) {
				//printf("L2Saca un sector%d,%d\n",(*it_pos).getX(),(*it_pos).getY());
				sectores.erase(it_pos);
				break;
			}
		}
		it_pos = sectores.begin();
	}
	if (sectores.empty()) {
		//printf("L2Errores todos los sectores ocupados\n");
		pos.set(-1, -1);
		return pos;
	} else {
		GeneradorNumeros generador;
		int i = generador.numeroRandom(0, sectores.size() - 1);
		return this->posicionValidaEnSector(sectores[i], base);
	}

}
Posicion Mapa::posicionValidaEnSector(Posicion sector, Entidad * entidad) {
//devuelve una posicion random dentro de un cuarto del mapa que este vacia y sea ubicable
	GeneradorNumeros num;
	int x;
	int y;
	Celda * celda;
	do {
		x = num.numeroRandom(sector.getX(), sector.getX() + this->ancho / 2 - 1);
		y = num.numeroRandom(sector.getY(), sector.getY() + this->largo / 2 - 1);
		celda = this->getCelda(x, y);
		entidad->set_posicion(x, y);
		//printf("L3En while\n");
	} while (celda->estaOcupada() || !this->puedeUbicar(entidad));
//printf("L3EncontroPosicion\n");
	Posicion posicion = { x, y };
	return posicion;
}

bool Mapa::estaDentroDeSector(Posicion sector, Posicion entidad) {
//su referencia al mapa esta dentro del sector
	if (entidad.getX() < sector.getX() + this->getAncho() / 2) {
		if (entidad.getY() < sector.getY() + this->getLargo() / 2) {
			return true;
		}
	}
	return false;
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
		delete[] celdas[i];
	}
	delete[] celdas;

}

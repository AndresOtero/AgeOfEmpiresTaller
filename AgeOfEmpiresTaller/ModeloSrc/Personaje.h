/*
 * Personaje.h
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */
#include "../VistaSrc/Dibujo.h"
#include "ObjetoMapa.h"
#include "Posicion.h"
#include "RecursosJugador.h"
#include "../GameControllerSrc/mensaje.h"
#ifndef PERSONAJE_H_
#define PERSONAJE_H_
typedef int dibujo_t;

class Personaje {
	RecursosJugador * recursos;
	double referencia_mapa_x,referencia_mapa_y;
	dibujo_t dibujo;
	double velocidad;
	int fuerza;
	int armadura;
	int recoleccion;
	int construccion;
	Posicion destino;
	Posicion camino;
	bool congelado;
	bool se_movio;
	Personaje* atacado;
	int id;
	string nombreJugador;

public:
	Personaje();
	Personaje(ObjetoMapa* objetoMapa);
	Personaje(ObjetoMapa* objetoMapa, int x, int y);
	RecursosJugador * recursosJugador();
	string mostrar_contenido();
	ObjetoMapa* objetoMapa;
	dibujo_t dibujar();
	virtual ~Personaje();
	void  mover();
	void set_destino(Posicion destino);
	void set_camino(Posicion camino);
	void set_posicion(Posicion pos);
	Posicion get_destino();
	Posicion get_posicion();
	Posicion get_camino();
	void set_ataque(Personaje* otro_personaje);
	void set_destino_al_ataque();

	msg_t interactuar(Personaje* otro_personaje);
	int atacar(Personaje* otro_personaje);

	bool seMovio(){
		return se_movio;
	}
	bool esta_atacando(){
		return this->atacado!=NULL;
	}
	void setDibujo(dibujo_t dibujo) {
		this->dibujo = dibujo;
	}

	double getReferenciaMapaX() const {
		return referencia_mapa_x;
	}

	double getReferenciaMapaY() const {
		return referencia_mapa_y;
	}

	void congelar() {
		this->congelado = true;
	}
	void descongelar() {
			this->congelado = false;
		}
	bool estaCongelado() {
			return this->congelado;
	}

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	const string& getNombreJugador() const {
		return nombreJugador;
	}
	string getNombreTipo() const {
			return objetoMapa->nombre;//nombre del tipo
		}
	void setNombreJugador(const string& nombreJugador) {
		this->nombreJugador = nombreJugador;
	}
};

#endif /* PERSONAJE_H_ */

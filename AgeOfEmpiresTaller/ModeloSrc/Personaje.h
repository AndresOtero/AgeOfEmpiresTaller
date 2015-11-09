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
	int vida;
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
    friend bool operator== ( Personaje &P1,  Personaje &P2);

	msg_t interactuar(Personaje* otro_personaje);
	int danioInfringido();
	bool seMovio(){
		return se_movio;
	}
	void recibirDanio(int danio);
	void dejar_de_atacar();
	bool esta_vivo(){
		return (vida>0);
	}
	bool esta_atacando(){
		return this->atacado!=NULL;
	}
	int get_atacado_id(){
		return this->atacado->getId();
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
	void  ejecutar_ataque();
};

#endif /* PERSONAJE_H_ */

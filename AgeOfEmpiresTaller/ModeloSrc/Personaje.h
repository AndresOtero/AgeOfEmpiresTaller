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
#include "../ModeloSrc/Contador.h"
#include "Entidad.h"
#include "Atacable.h"
#include "Costo.h"
#include "../VistaSrc/DatosSeleccionado.h"
#include <math.h>
#ifndef PERSONAJE_H_
#define PERSONAJE_H_
typedef int dibujo_t;

class Personaje:public Atacable {
	RecursosJugador * recursos;
	double referencia_mapa_x,referencia_mapa_y;
	dibujo_t dibujo_atacando;
	dibujo_t dibujo_esta_quieto;
	dibujo_t dibujo_esta_moviendo;
	dibujo_t dibujo_actual;
	dibujo_t dibujo_anterior;
	double velocidad;
	int vida;
	int fuerza;
	int armadura;
	int recoleccion;
	int construccion;
	Posicion destino;
	Posicion camino;
	Contador contador_ataque;
	bool congelado;
	bool se_movio;
	bool atacando_cliente;
	Atacable* atacado;
	Entidad* objetivo;
	int id;
	string nombreJugador;
	string raza;
	Costo costo;
public:
	bool adyacente;
	Personaje();
	Personaje(ObjetoMapa* objetoMapa);
	Personaje(ObjetoMapa* objetoMapa, int x, int y);
	int getDibujoAnterior(){
		return dibujo_anterior;
	}
	Costo getCosto(){
		return this->costo;
	}
	RecursosJugador * recursosJugador();
	DatosSeleccionado mostrar_contenido();
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

	void set_ataque(Atacable* otro_personaje);
	void set_destino_al_ataque();
	bool es_adyacente_al_atacado();
    friend bool operator== ( Personaje &P1,  Personaje &P2);

	void setAccion(Entidad * entidad);
	msg_t interactuar(Personaje* otro_personaje);
	int danioInfringido();
	msg_t interactuar(Entidad * otra_entidad);

	int atacar(Atacable* otro_personaje);
	void terminarAccion();
	bool esAdyacente(Entidad* entidad);

	string get_raza(){
		return this->raza;
	}
	bool tieneRecursos(){
		return !this->recursos->estaVacio();
	}

	bool seMovio(){
		return se_movio;
	}
	void recibirDanio(int danio);
	void dejar_de_atacar();
	void noInteractua(){
		this->atacado=NULL;
		this->objetivo=NULL;
	}
	bool esta_vivo(){
		return (vida>0);
	}
	bool esta_atacando(){
		return this->atacado!=NULL;
	}
	Atacable * get_atacado(){
		return atacado;
	}
	int get_atacado_id(){
		return this->atacado->getId();
	}
	int get_construccion(){
		return this->construccion;
	}
	void setDibujo(dibujo_t dibujo_esta_atacando,dibujo_t dibujo_esta_quieto,dibujo_t dibujo_esta_moviendo) {
		this->dibujo_atacando = dibujo_esta_atacando;
		this->dibujo_esta_quieto = dibujo_esta_quieto;
		this->dibujo_esta_moviendo = dibujo_esta_moviendo;
		this->dibujo_actual=dibujo_esta_quieto;

	}
	bool puedeCrear(){
		return (this->construccion > 0);
	}
	bool puedeRecolectar(){
		if (this->recoleccion>0)
			return true;
		return false;
	}

	bool puedeAtacar(){
		if (this->fuerza > 0)
			return true;
		return false;
	}
	bool esRey(){
		//si es inutil es rey
		bool esRey= true;
		if (puedeAtacar()){
			esRey=false;
		}else if(puedeRecolectar()){
			esRey=false;
		}else if (puedeCrear()){
			esRey=false;
		}
		return esRey;
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

	int getId() {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	int getRecoleccion(){
		return this->recoleccion;
	}
	const string& getNombreJugador() const {
		return nombreJugador;
	}
	string getNombreTipo() const {
			return objetoMapa->nombre;//nombre del tipo
	}

	bool esta_recolectando(){
		if (this->puedeRecolectar()){
			//para diferenciar recursos de construcciones
			if(this->objetivo){
				return this->objetivo->esUnRecurso();
			}
		}
		return false;
	}
	bool esta_contruyendo() {
		if (this->puedeRecolectar()) {
			//para diferenciar recursos de construcciones
			if (this->objetivo) {
				return !this->objetivo->esUnRecurso();
			}
		}
		return false;
	}

	void setNombreJugador(const string& nombreJugador) {
		this->nombreJugador = nombreJugador;
	}
	bool  ejecutar_ataque();
	Entidad * get_objetivo(){
		return this->objetivo;
	}
	bool contar(){
		return this->contador_ataque.contar();
	}
	int getArmadura(){
		return this->armadura;
	}

	bool estaAtacandoCliente() {
		return atacando_cliente;
	}

	void atacandoCliente(bool atacandoCliente) {
		atacando_cliente = atacandoCliente;
	}
};

#endif /* PERSONAJE_H_ */

/*
 * Celda.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Celda.h"
#include <iostream>
#include "Recurso.h"
#include "../VistaSrc/Dibujo.h"
#define VACIO 0
Celda::Celda() {
	this -> escenario = DEFAULT;
	this -> tiles = DEFAULT;
	this -> ocupada = false;
	this->entidad = NULL;
	this->personaje=NULL;
}
void Celda::setEscenario(dibujo_t dibujo_n){

	this->escenario=dibujo_n;
}
void Celda::setTiles(dibujo_t dibujo_n){
	this->tiles=dibujo_n;
}
dibujo_t Celda::dibujarTiles(){
	return this->tiles;
}
dibujo_t Celda::dibujarEscenario(){
	return this->escenario;
}
void Celda::actualizar(){
	this->personaje=NULL;
}
void Celda::ocuparCeldaPersonaje(Personaje* personaje){
	this->personaje=personaje;

}
void Celda::liberarCelda(){
	this->ocupada=false;
	this->entidad=NULL;
	this->escenario=DEFAULT;
	//nose si este ultimo es necesario pero por las dudas
	//this->tiles=DEFAULT;
}

bool Celda::tieneRecurso(){
	if (this->entidad!=NULL){
		return entidad->esUnRecurso();
	}
	return false;
}

bool Celda::estaOcupada(){
	if ((this->entidad!=NULL)){
		return true;
	}
	if (this->personaje!=NULL)
		return true;
	printf ("Pregunto y no habia ni entidad ni personaje\n");
	return this->ocupada;
}
void Celda::ocuparCelda(Entidad * entidad){
	this->ocupada=true;
	this->entidad=entidad;
	//deberia setear el escenario con el modelo en que estamos
}
string Celda::mostrar_contenido(){
	string nombre;
	if (this->personaje!=NULL){
			nombre = this->personaje->mostrar_contenido();
	}
	else
		nombre = this->mostrar_entidad();
	return nombre;
}
void Celda::seleccionarEntidad(){
	if (this->entidad!=NULL){
		this->entidad->seleccionar();
	}
}
void Celda::deseleccionarEntidad(){
	if (this->entidad!=NULL){
		this->entidad->deselccionar();
	}
}
bool Celda::estaSeleccionada(){
	if (this->entidad!=NULL){
		return this->entidad->estaSeleccionado();
	}
	return false;
}
string Celda::mostrar_entidad(){
	string nombre;
	if (this->entidad!=NULL){
			nombre = this->entidad->mostrar_contenido();

		}
	else {
		nombre = "";
	}
	return nombre;
}
Personaje* Celda::devolver_personaje(){
	return personaje;
}
Entidad* Celda::devolver_entidad(){
	return entidad;
}
Celda::~Celda() {
	// TODO Auto-generated destructor stub

}


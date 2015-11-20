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
	this-> tileActual = this->tiles;
	this->tiles_elfo = NULL;
	this-> tiles_hobbit = NULL;
	this-> tiles_humanos = NULL;
	this->tiles_mordor = NULL;
	this->tiles_water = NULL;
	this->agua = false;
}
void Celda::setEscenario(dibujo_t dibujo_n){
	this->escenario=dibujo_n;
}
void Celda::setTiles(dibujo_t dibujo_n){
	this->tiles=dibujo_n;
}
void Celda::setTilesElfo(dibujo_t dibujo_n){
	this->tiles_elfo=dibujo_n;
}
void Celda::setTilesHobbit(dibujo_t dibujo_n){
	this->tiles_hobbit=dibujo_n;
}
void Celda::setTilesHumanos(dibujo_t dibujo_n){
	this->tiles_humanos=dibujo_n;
}
void Celda::setTilesMordor(dibujo_t dibujo_n){
	this->tiles_mordor=dibujo_n;
}
void Celda::setTilesWater(dibujo_t dibujo_n){
	this->tiles_water=dibujo_n;
}
void Celda::mostrarTileNormal(){
	this->tileActual = tiles;
}
void Celda::mostrarTileElfo(){
	this->tileActual = tiles_elfo;
}
void Celda::mostrarTileHobbit(){
	this->tileActual = tiles_hobbit;
}
void Celda::mostrarTileHumanos(){
	this->tileActual = tiles_humanos;
}
void Celda::mostrarTileMordor(){
	this->tileActual = tiles_mordor;
}
void Celda::mostrarTileWater(){
	this->tileActual = tiles_water;
}
dibujo_t Celda::dibujarTiles(){
	return this->tileActual;
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

	return this->ocupada;
}
void Celda::ocuparCelda(Entidad * entidad){
	this->ocupada=true;
	this->entidad=entidad;
	//deberia setear el escenario con el modelo en que estamos
}
DatosSeleccionado Celda::mostrar_contenido(){
	DatosSeleccionado datos;
	if (this->personaje!=NULL){
			datos = this->personaje->mostrar_contenido();
	}
	else
		datos = this->mostrar_entidad();
	return datos;
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
DatosSeleccionado Celda::mostrar_entidad(){
	DatosSeleccionado datos;
	if (this->entidad!=NULL){
			datos = this->entidad->mostrar_contenido();

		}
	return datos;
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


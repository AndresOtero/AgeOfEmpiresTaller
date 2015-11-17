/*
 * Entidad.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Entidad.h"
#include "Recurso.h"
using namespace std;
unsigned int GeneradorNumeros::id =0;

Entidad::Entidad(ObjetoMapa* objetoMapa) {
	this -> objetoMapa = objetoMapa;
	this -> posicion = new Posicion();
	GeneradorNumeros generar;
	this->id = generar.otroID();
	this->vida = objetoMapa->vida; //TODO
	this->raza = objetoMapa->raza;
	this->velocidad_cosntruccion = objetoMapa->velocidad_construcccion;
	this->costo.setCosto(objetoMapa->oro,objetoMapa->madera,objetoMapa->piedra,objetoMapa->comida);
	this->esUnaBandera = false;

}
Entidad::Entidad(ObjetoMapa* objetoMapa, int x, int y) {
	this -> objetoMapa = objetoMapa;
	this -> posicion = new Posicion(x, y);
	GeneradorNumeros generar;
	this->id = generar.otroID();
	this->vida = objetoMapa->vida;//TODO
	this->raza = objetoMapa->raza;
	this->velocidad_cosntruccion = objetoMapa->velocidad_construcccion;
	this->costo.setCosto(objetoMapa->oro,objetoMapa->madera,objetoMapa->piedra,objetoMapa->comida);
	this->esUnaBandera = false;
}
bool Entidad::esUnRecurso(){
	if (Recurso* rec = dynamic_cast<Recurso*>(this)){
		return true;
	}
	return false;
}
void Entidad::cargarPersonajes(map<string,ObjetoMapa*> diccionario_de_personajes){
	this->diccionario_de_personajes=diccionario_de_personajes;
}
map<string,ObjetoMapa*>  Entidad::devolverPersonajesCreables(){
	return this->diccionario_de_personajes;
}

bool  Entidad::puedeCrearPersonajes(){
	return (!diccionario_de_personajes.empty());
}


DatosSeleccionado Entidad::mostrar_contenido() {
	DatosSeleccionado datos;
	datos.setNombre(objetoMapa->nombre);
	if (this->esUnRecurso()){
		datos.setTipo(RECURSO);
		datos.setRecurso(((Recurso*)this)->obtenerPunteroRecurso());
	}else{
		datos.setTipo(EDIFICIO);
		datos.setVida(&this->vida,this->objetoMapa->vida);
		datos.setConstruccion(&this->velocidad_cosntruccion,this->objetoMapa->velocidad_construcccion);
	}
	return datos;

}

bool Entidad::esAdyacente(Posicion pos){
	int alto,ancho,x,y;
	alto = this->objetoMapa->baseLogica->alto;
	ancho = this->objetoMapa->baseLogica->ancho;
	Posicion temp1,temp2;
	//reviso si alguna fila de ancho esta en rango de la posicion
	for (x = 0; x < (ancho); x++) {
		temp1 = {this->posicion->getX()+x,this->posicion->getY()};
		temp2 = {this->posicion->getX()+x,posicion->getY()+alto-1};
		if (pos.es_adyacente(temp1)|| pos.es_adyacente(temp2)) {
			return true;
		}
	}
	//reviso si alguna que no cheque esta en rango
	for (y = 1; y < (alto - 1); y++) {
		temp1 = {posicion->getX(),posicion->getY()+y};
		temp2 = {posicion->getX()+ancho-1,posicion->getY()+y};
		if (pos.es_adyacente(temp1)|| pos.es_adyacente(temp2)) {
			return true;
		}
	}
	return false;
}
bool Entidad::esUnCentroCivio(){
	if (!this->diccionario_de_personajes.empty()){
		map<string, ObjetoMapa*>::iterator it;
		for (it = this->diccionario_de_personajes.begin(); it != this->diccionario_de_personajes.end(); it++){
			//si puede construir tipitos que construyen es un centro civico
			if (it->second->construccion>0){
				return true;
			}
		}
	}
	return false;
}
bool Entidad::esInternaLaPosicion(int x, int y){
	int ancho = this->objetoMapa->baseLogica->ancho;
	int alto =this->objetoMapa->baseLogica->alto;
	int x_inicio = this->get_posicion().getX()+1;
	int x_final =this->get_posicion().getX()+ancho-1;
	int y_inicio = this->get_posicion().getY()+1;
	int y_final =this->get_posicion().getY()+alto-1;

	for (;x_inicio < x_final; x_inicio++ ){
		for(;y_inicio < y_final; y_inicio++){
			if (x_inicio == x && y_inicio == y){
				return true;
			}
		}
	}
	return false;
}
Entidad::~Entidad() {
	delete posicion;
	if(this->objetoMapa==NULL){
		delete objetoMapa;
	}
}

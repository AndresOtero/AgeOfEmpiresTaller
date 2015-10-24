/*
 * Juego.cpp
 *
 *  Created on: 20/9/2015
 *      Author: ger
 */

#include "Juego.h"

Juego::Juego() {
	//configuracion default
	this -> pantalla = new Pantalla();
	this -> conf = new Configuracion();
	this -> escenario = new Escenario();
	cargarTiposDefault();
}
void Juego::cargarTiposDefault(){
	tipos["oro"]=new ObjetoMapa("oro","img/oro.png");

		tipos["madera"]=new ObjetoMapa("madera","img/madera.png");

		tipos["piedra"]=new ObjetoMapa("piedra","img/piedra.png");
}
Juego::Juego(Pantalla* pantalla, Configuracion* conf, Escenario* escenario, std::map<std::string, ObjetoMapa*> &tipos ){
	this -> pantalla = pantalla;
	this -> conf = conf;
	this -> escenario = escenario;
	this->tipos = tipos;
	cargarTiposDefault();

}
void Juego::setEscenario(string nombre,int ancho,int largo){
	this -> escenario->nombre=nombre;
	this->escenario->size_x=ancho;
	this->escenario->size_y=largo;
}
void Juego::setConfiguracion(int margenScroll,int velocidad_personaje){
	this ->conf->setMargenScroll(margenScroll);
	this ->conf->setVelPersonaje(velocidad_personaje);
}
void Juego::agregarEntidad(string nombre,int x, int y){
	Entidad* entidad;
	ObjetoMapa* objeto=this->tipos[nombre];
	if (nombre.compare("oro")==0)
		entidad = new Oro(objeto,x,y);
	else if (nombre.compare("piedra")==0)
		entidad = new Piedra(objeto,x,y);
	else if (nombre.compare("madera")==0)
		entidad = new Madera(objeto,x,y);
	else
		entidad = new Entidad(objeto,x,y);
	this->escenario->entidades.push_back(entidad);
}



Juego::~Juego() {
	delete this->pantalla;
	delete this->conf;

	std::map<std::string, ObjetoMapa*> ::iterator it;
	for ( it = this->tipos.begin(); it !=this->tipos.end(); it++ ){
		delete it->second;
	}
	delete this-> escenario;
}


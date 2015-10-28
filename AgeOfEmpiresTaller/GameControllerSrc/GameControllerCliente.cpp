/*
dibu * GameControllerCliente.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameControllerCliente.h"

char* GameControllerCliente::string_to_char_array(string str){
	int str_size = str.size();
	char charArray[PARAM_STRING_LEN];
	for (int a = 0; a <= str_size; a++) {
		charArray[a] = str[a];
	}
	return charArray;
}

GameControllerCliente::GameControllerCliente() {
}


GameControllerCliente::~GameControllerCliente() {
}
string GameControllerCliente::nombreJugador() {
	return this->modelo->nombreJugador();
}
string GameControllerCliente::ipJugador() {
	return this->modelo->ipJugador();
}


void GameControllerCliente::cambiar_destino_personaje(string id, double mov_x,double mov_y){

	msg_t mensaje;

	mensaje.type = MOVER_PERSONAJE;

	memcpy(mensaje.paramNombre,string_to_char_array(id),sizeof(mensaje.paramNombre));

	mensaje.paramDouble1 = mov_x;
	mensaje.paramDouble2 = mov_y;

	this->agregarMensaje(mensaje);

}

void GameControllerCliente::mover_personaje(string name,double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(name,mov_x,mov_y);
}

Personaje* GameControllerCliente::conectarme(string name,string str, int x,int y){
	ObjetoMapa* obj= this->juego->tipos[str];
	Personaje* personaje =new Personaje(obj,x,y);
	personaje->setNombreJugador(name);
	this->modelo->crearPersonajeCliente(personaje);

	return personaje;
}

void GameControllerCliente::conectarCliente(string name,string str, int x,int y){
	ObjetoMapa* obj= this->juego->tipos[str];
	Personaje* personaje =new Personaje(obj,x,y);
	personaje->setNombreJugador(name);

	this->modelo->agregarPersonajeCliente(personaje);
}
//solo para iniciar
/*void GameControllerCliente::setearPosicionPersonaje(int id,double pos_x,double pos_y){
	Posicion pos=Posicion(pos_x,pos_y);
	this->modelo->setearPersonajeCliente(id,pos);
}*/

void GameControllerCliente::agregarEntidad(string nombre,int x, int y, int cant){
	this->modelo->agregarEntidad(nombre,x,y,cant);
}

void GameControllerCliente::desconectar(string id){
	this->modelo->congelarPersonaje(id);
}

void GameControllerCliente::reconectar(string id){
	this->modelo->descongelarPersonaje(id);
}

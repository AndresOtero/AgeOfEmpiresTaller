/*
dibu * GameControllerCliente.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameControllerCliente.h"

GameControllerCliente::GameControllerCliente() {
	// TODO Auto-generated constructor stub
}


GameControllerCliente::~GameControllerCliente() {
	// TODO Auto-generated constructor stub
}
string GameControllerCliente::nombreJugador() {
	return this->modelo->nombreJugador();
	// TODO Auto-generated constructor stub
}
string GameControllerCliente::ipJugador() {
	return this->modelo->ipJugador();
	// TODO Auto-generated constructor stub
}


void GameControllerCliente::cambiar_destino_personaje(int id, double mov_x,double mov_y){

	msg_t mensaje;
	mensaje.type = MOVER_PERSONAJE;
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = mov_x;
	mensaje.paramDouble2 = mov_y;
	this->agregarMensaje(mensaje);

}

void GameControllerCliente::mover_personaje(int id,double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(id,mov_x,mov_y);
}

Personaje* GameControllerCliente::conectarme(string str, int x,int y){
	ObjetoMapa* obj= this->juego->tipos[str];
	Personaje* personaje =new Personaje(obj,x,y);
	this->modelo->crearPersonajeCliente(personaje);
	return personaje;
}

void GameControllerCliente::conectarCliente(string str, int x,int y){
	ObjetoMapa* obj= this->juego->tipos[str];
	Personaje* personaje =new Personaje(obj,x,y);
	this->modelo->agregarPersonajeCliente(personaje);
}

void GameControllerCliente::setearModelo(int id,double pos_x,double pos_y){
	Posicion pos=Posicion(pos_x,pos_y);
	this->modelo->setearPersonajeCliente(id,pos);
}
void GameControllerCliente::agregarEntidad(string nombre,int x, int y, int cant){
	this->modelo->agregarEntidad(nombre,x,y,cant);
}

void GameControllerCliente::desconectar(string id){

}

void GameControllerCliente::reconectar(string id){

}
/**
void GameControllerCliente::desconectar(int Id){
	this->modelo->congelarPersonaje(Id);
}

void GameControllerCliente::reconectar(int Id){
	this->modelo->descongelarPersonaje(Id);
}**/

void GameControllerCliente::actualizarJuego(string evento){
	printf("Actualizando modelo en cliente: %s",evento.c_str());
}

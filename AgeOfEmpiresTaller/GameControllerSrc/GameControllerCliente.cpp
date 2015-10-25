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

void GameControllerCliente::cambiar_destino_personaje( double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(mov_x,mov_y);
	this->modelo->getIdCliente();
	//interprete
}
Personaje* GameControllerCliente::conectarme(Personaje* personaje){
	this->modelo->crearPersonajeCliente(personaje);
	return personaje;
}

void GameControllerCliente::conectarCliente(Personaje* personaje){
	this->modelo->crearPersonajeCliente(personaje);
}

void GameControllerCliente::setearModelo(int id,Posicion pos){
	this->modelo->setearPersonajeCliente(id,pos);
}
void GameControllerCliente::desconectar(int Id){
	this->modelo->congelarPersonaje(Id);
}
void GameControllerCliente::reconectar(int Id){
					this->modelo->descongelarPersonaje(Id);
			 }
void GameControllerCliente::actualizarJuego(string evento){
	printf("Actualizando modelo en cliente: %s",evento.c_str());
}

string GameControllerCliente::obtenerSiguienteEvento(){
	//TODO GameController podria tener una cola de eventos donde se van agregando, y se saca el ultimo de ahi.
	string siguienteEvento = "Mover id:1 pos:(5,3)";

	return siguienteEvento;
}

bool GameControllerCliente::hayNuevosEventos(){
	//TODO GameController podria tener una cola de eventos y checkear si hay nuevos eventos para mandar.
	return true;
}


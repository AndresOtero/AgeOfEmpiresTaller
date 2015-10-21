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
					this->modelo->congelarPersonaje(Id);
			 }


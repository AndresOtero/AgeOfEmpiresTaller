/*
 * GameController.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameController.h"

GameController::GameController() {
	// TODO Auto-generated constructor stub
}

void GameController::insertarModelo(Modelo* modelo) {
	// TODO Auto-generated constructor stub
	this->modelo=modelo;
}
void GameController::setMapa(int ancho,int largo){
	this->modelo->setMapa(ancho,largo);
}

void GameController::agregarPersonaje(Personaje* personaje){

	this->modelo->agregarPersonaje(personaje);
}
void GameController::reconectar(int id){
}
void GameController::conectar(){
}
 void GameController::desconectar(int id){
}

 void GameController::cambiar_destino_personaje(int id ,double mov_x,double mov_y){

		this->modelo->cambiar_destino_personaje( mov_x, mov_y);
 }
 void GameController::generarRecursoRandom(){
	this->modelo->generarRecursoRandom();
}
void GameController::eliminarEntidad(Entidad *entidad){
	this->modelo->eliminarEntidad(entidad);
}
GameController::~GameController(){}

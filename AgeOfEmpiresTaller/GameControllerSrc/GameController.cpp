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
GameController::~GameController() {
	// TODO Auto-generated constructor stub
	delete modelo;
	delete juego;
}

void GameController::insertarJuego(Juego* juego) {
	// TODO Auto-generated constructor stub
	this->juego=juego;
}

void GameController::setEscenario(string nombre,int ancho,int largo){
	this->juego->setEscenario(nombre,ancho,largo);
}

void GameController::setConfiguracion(int margenScroll,int velocidad_personaje){
	this->juego->setConfiguracion(margenScroll,velocidad_personaje);

}
void GameController::agregarEntidad(string nombre,int x, int y){
	this->modelo->agregarEntidad(nombre,x,y);
}

void GameController::crearModelo(){
	//luego de setearlo
	this->modelo=new Modelo(juego);
}
Modelo* GameController::devolverModelo(){
	return this->modelo;
}

 void GameController::cambiar_destino_personaje(int id ,double mov_x,double mov_y){
		this->modelo->cambiar_destino_personaje(id, mov_x, mov_y);
 }
 void GameController::generarRecursoRandom(){
	this->modelo->generarRecursoRandom();
}
void GameController::eliminarEntidad(int id){
	this->modelo->eliminarEntidadPorID(id);

}
bool GameController::hayEventos(){
	return !this->cola.empty();
}

msg_t GameController::sacarMensaje(){
	msg_t mensaje = this->cola.front();
	this->cola.pop();
	return mensaje;
}

void GameController::agregarMensaje(msg_t mensaje){
	this->cola.push(mensaje);
}

void GameController::reconectar(int id){}
void GameController::desconectar(int Id){}
void GameController::actualizar(){}

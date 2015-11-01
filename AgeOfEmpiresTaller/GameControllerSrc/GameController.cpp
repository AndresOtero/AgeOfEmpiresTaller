/*
 * GameController.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameController.h"

GameController::GameController() {
}
GameController::~GameController() {
	delete modelo;
	delete juego;
}
void GameController::insertarJuego(Juego* juego) {
	this->juego=juego;
}

void GameController::setEscenario(string nombre,int ancho,int largo){
	this->juego->setEscenario(nombre,ancho,largo);
}

void GameController::setConfiguracion(int margenScroll,int velocidad_personaje){
	this->juego->setConfiguracion(margenScroll,velocidad_personaje);

}
void GameController::agregarEntidad(string nombre,int x, int y,int cantidad){
	this->modelo->agregarEntidad(nombre,x,y,cantidad);
}

void GameController::crearModelo(){
	this->modelo=new Modelo(juego);
}
Modelo* GameController::devolverModelo(){
	return this->modelo;
}

 void GameController::cambiar_destino_personaje(string id ,double mov_x,double mov_y){
		this->modelo->cambiar_destino_personaje(id, mov_x, mov_y);
}

void GameController::eliminarEntidad(int id){
	this->modelo->eliminarEntidadPorID(id);
}
bool GameController::hayEventos(){
	printf("Entro aca \n \n");
	printf((this->cola.empty())? "Es NUll \n" : "No es Null\n");
	return (!this->cola.empty());
}
msg_t GameController::sacarMensaje(){
	msg_t mensaje = this->cola.front();
	this->cola.pop();
	return mensaje;
}
void GameController::agregarMensaje(msg_t mensaje){
	this->cola.push(mensaje);
}
void GameController::reconectar(string id){
	this->modelo->descongelarPersonaje(id);
}
void GameController::desconectar(string id){
	this->modelo->congelarPersonaje(id);
}
void GameController::actualizar(){
	//virtual
}

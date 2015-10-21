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
}

void GameController::insertarModelo(Modelo* modelo) {
	// TODO Auto-generated constructor stub
	this->modelo=modelo;
}
void GameController::setMapa(int ancho,int largo){
	this->modelo->setMapa(ancho,largo);
}

void GameController::setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles){
	this->modelo->setDibujoMapa(escenario,tiles);
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

 void GameController::reconectar(int id){}
	  void GameController::desconectar(int Id){}
	  void GameController::actualizar(){}

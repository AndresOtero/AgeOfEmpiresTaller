/*
 * GameController.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include <vector>
#include "../ModeloSrc/Modelo.h"

#ifndef GAMECONTROLLERSRC_GAMECONTROLLER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLER_H_

class GameController {
protected:
	Modelo* modelo;
public:
	GameController();
	 void agregarPersonaje(Personaje*);
	 void insertarModelo(Modelo* modelo);
	 void setMapa(int ancho,int largo);
	 void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	 void congelarPersonaje(Personaje* personaje);
	 void descongelarPersonaje(Personaje* personaje);
	 void cambiar_destino_personaje(double mov_x,double mov_y);
	 void generarRecursoRandom();
	 void eliminarEntidad(Entidad *entidad);
	 ~GameController();






};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLER_H_ */

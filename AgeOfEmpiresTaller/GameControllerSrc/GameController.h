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
	 void insertarModelo(Modelo* modelo);
	 void setMapa(int ancho,int largo);
	 void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);
	 void cambiar_destino_personaje(int id, double mov_x,double mov_y);
	 void generarRecursoRandom();
	 void eliminarEntidad(int id);


	  void reconectar(int id);
	 	  void desconectar(int Id);
	 	  void actualizar();
	 int get_id(int id);
	 ~GameController();






};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLER_H_ */

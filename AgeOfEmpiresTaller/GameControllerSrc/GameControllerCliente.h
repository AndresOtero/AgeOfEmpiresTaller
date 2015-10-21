/*
 * GameControllerCliente.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include "../GameControllerSrc/GameController.h"
#ifndef GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#include "GameController.h"

class GameControllerCliente:public GameController  {

public:
	GameControllerCliente();
	 virtual ~GameControllerCliente();
	 void insertarModelo(Modelo* modelo);
		 void setMapa(int ancho,int largo);
		 void setDibujoMapa(vector<vector<dibujo_t>> escenario,vector<vector<dibujo_t>> tiles);

		 void cambiar_destino_personaje(int id, double mov_x,double mov_y);
		 void generarRecursoRandom();
		 void eliminarEntidad(int id);

		 //Cliente
		 void cambiar_destino_personaje(double mov_x,double mov_y);
		 void conectarCliente(Personaje* personaje);
		 Personaje* conectarme(Personaje* personaje);//Acordarse inmediatamente despues setear
		 void setearModelo(int id,Posicion pos);
		void desconectar(int Id);
			void reconectar(int Id);

};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_ */

/*
 * GameControllerServer.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include "../GameControllerSrc/GameController.h"

#ifndef GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_

class GameControllerServer:public GameController{
public:
	GameControllerServer();
	virtual ~GameControllerServer();
	 void agregarPersonaje(Personaje*);
	 void insertarModelo(Modelo* modelo);
	 void setMapa(int ancho,int largo);
	 void congelarPersonaje(Personaje* personaje);
	 void descongelarPersonaje(Personaje* personaje);
	 void cambiar_destino_personaje(double mov_x,double mov_y);
	 void generarRecursoRandom();
	 void eliminarEntidad(Entidad *entidad);
		int get_alto_mapa();
		int get_ancho_mapa();
};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_ */

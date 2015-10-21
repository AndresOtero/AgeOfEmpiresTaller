/*
 * GameControllerCliente.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include "../GameControllerSrc/GameController.h"
#ifndef GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_

class GameControllerCliente:public GameController  {

public:
	GameControllerCliente();
	virtual ~GameControllerCliente();
	bool estaSeleccionada(int x,int y);
	 void agregarPersonaje(Personaje*);
		 void insertarModelo(Modelo* modelo);
		 void setMapa(int ancho,int largo);
		 dibujo_t dibujar(int dim,int x,int y);
		 void congelarPersonaje(Personaje* personaje);
		 void descongelarPersonaje(Personaje* personaje);
		 void cambiar_destino_personaje(double mov_x,double mov_y);
		 void generarRecursoRandom();
		 void eliminarEntidad(Entidad *entidad);
			int get_alto_mapa();
			int get_ancho_mapa();


};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_ */

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
	void insertarModelo(Modelo* modelo);
	void setMapa(int ancho, int largo);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,
			vector<vector<dibujo_t>> tiles);
	void conectar();
	void cambiar_destino_personaje(int id, double mov_x, double mov_y);
	void generarRecursoRandom();
	void eliminarEntidad(int id);

	//server
	void reconectar(int id);
	void agregarCliente(Personaje* personaje);
	void desconectar(int id);
	void actualizar();

};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_ */

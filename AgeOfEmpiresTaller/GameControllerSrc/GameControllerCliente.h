/*
 * GameControllerCliente.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#ifndef GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#include "GameController.h"

class GameControllerCliente:public GameController  {

public:
	GameControllerCliente();
	~GameControllerCliente();
	string nombreJugador() ;
	string ipJugador() ;
	void insertarModelo(Modelo* modelo);
	void setMapa(int ancho, int largo);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,
			vector<vector<dibujo_t>> tiles);

	void cambiar_destino_personaje(int id, double mov_x, double mov_y);
	void generarRecursoRandom();
	void eliminarEntidad(int id);

	void actualizarJuego(string evento);
	//Cliente
	void cambiar_destino_personaje(double mov_x, double mov_y);
	void conectarCliente(string tipo, int x, int y);
	Personaje* conectarme(string tipo, int x, int y); //Acordarse inmediatamente despues setear
	void setearModelo(int id, double pos_x, double pos_y);
	//void desconectar(int Id);
	//void reconectar(int Id);
	void reconectar(string id);
	void desconectar(string Id);



};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_ */

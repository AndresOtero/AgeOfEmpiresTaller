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


	void generarRecursoRandom();
	void eliminarEntidad(int id);
	void mover_personaje(string id, double mov_x,double mov_y);

	//Cliente
	void agregarEntidad(string nombre,int x,int y,int cant);
	void cambiar_destino_personaje(string id, double mov_x, double mov_y);
	void conectarCliente(string name,string str, int x,int y);
	Personaje* conectarme(string name,string str, int x,int y);
	//void setearPosicionPersonaje(int id,double pos_x,double pos_y);
	void reconectar(string id);
	void desconectar(string Id);
	char* string_to_char_array(string str);

};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_ */

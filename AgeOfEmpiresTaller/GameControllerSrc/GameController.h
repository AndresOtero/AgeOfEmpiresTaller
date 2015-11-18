/*
 * GameController.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include <vector>
#include "mensaje.h"
#include "../ModeloSrc/Modelo.h"
#include <plog/Log.h>

#include <queue>
#include <SDL2/SDL.h>

#ifndef GAMECONTROLLERSRC_GAMECONTROLLER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLER_H_



class GameController {
protected:
	Modelo* modelo;

	queue <msg_t> cola;

public:
	Juego* juego;
	GameController();
	 //Setear el juego
	 void insertarJuego(Juego* juego);
	 void setEscenario(string nombre,int ancho,int largo);
	 void setConfiguracion(int margenScroll,int velocidad_personaje);
	 void crearModelo();
	 Modelo* devolverModelo();
	 void cambiar_personaje(int id_personaje, string nombre,string raza);
	 //Controlar
	virtual void agregarEntidad(string nombre, int x, int y,int cantidad);
	void cambiar_destino_personaje(int id, double mov_x, double mov_y);
	void eliminarEntidad(int id);

	//Red
	void reconectar(string id);
	void desconectar(string Id);
	void actualizar();
	int get_id(int id);
	~GameController();

};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLER_H_ */

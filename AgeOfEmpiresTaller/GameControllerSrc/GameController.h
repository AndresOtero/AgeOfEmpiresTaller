/*
 * GameController.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include <vector>
#include "mensaje.h"
#include "../ModeloSrc/Modelo.h"
#include <queue>

#ifndef GAMECONTROLLERSRC_GAMECONTROLLER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLER_H_



class GameController {
protected:
	Modelo* modelo;
	Juego* juego;
	queue <msg_t> cola;

public:
	GameController();
	 //Setear el juego
	 void insertarJuego(Juego* juego);
	 void setEscenario(string nombre,int ancho,int largo);
	 void setConfiguracion(int margenScroll,int velocidad_personaje);
	 void crearModelo();
	 Modelo* devolverModelo();
	 bool hayEventos();
	 msg_t sacarMensaje();
	 void agregarMensaje(msg_t mensaje);
	 //Controlar
	virtual void agregarEntidad(string nombre, int x, int y,int cantidad);
	virtual void cambiar_destino_personaje(string id, double mov_x, double mov_y);
	void generarRecursoRandom();
	void eliminarEntidad(int id);

	//Red
	void reconectar(int id);
	void reconectar(string id);
	void desconectar(string Id);
	void desconectar(int Id);
	void actualizar();
	int get_id(int id);
	~GameController();

};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLER_H_ */

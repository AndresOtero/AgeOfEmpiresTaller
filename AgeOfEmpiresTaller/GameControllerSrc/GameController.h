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
	Juego* juego;
public:
	GameController();
	 //Setear el juego
	 void insertarJuego(Juego* juego);
	 void setEscenario(string nombre,int ancho,int largo);
	 void setConfiguracion(int margenScroll,int velocidad_personaje);
	 void crearModelo();

	 //Controlar
	 void agregarEntidad(string nombre,int x, int y);
	 	 void cambiar_destino_personaje(int id, double mov_x,double mov_y);
	 	 void generarRecursoRandom();
	 	 void eliminarEntidad(int id);

	 //Red
	  void reconectar(int id);
	 	  void desconectar(int Id);
	 	  void actualizar();
	 int get_id(int id);
	 ~GameController();






};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLER_H_ */

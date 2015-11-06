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
	 ~GameControllerServer();

	 bool hayEventos(SDL_mutex *mutex);
	 msg_t sacarMensaje(SDL_mutex *mutex);
	 void agregarMensaje(msg_t mensaje, SDL_mutex *mutex);

	void insertarModelo(Modelo* modelo);
	void setMapa(int ancho, int largo);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,
			vector<vector<dibujo_t>> tiles);
	void conectar();
	void eliminarEntidad(int id);
	void cambiar_destino_personaje(Id id, double mov_x,double mov_y);
	void agregarEntidad(string nombre,int x, int y, int cant, SDL_mutex *mutex);
	//server
	void reconectar(std::string id);
	void desconectar(std::string id);
	//void reconectar(int id);
	void agregarCliente(string name,string tipo, SDL_mutex *mutex);
	void generarRecursoRandom(SDL_mutex *mutex);
	//void desconectar(int id);
	void actualizar(SDL_mutex *mutex);
	char* string_to_char_array(string str);
	queue <msg_t>  inicializacion();


private:

};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_ */

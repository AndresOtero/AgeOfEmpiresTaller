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
	 bool hayEventos();
	 msg_t sacarMensaje();
	 void agregarMensaje(msg_t mensaje);
	string nombreJugador() ;;
	void insertarModelo(Modelo* modelo);
	void setMapa(int ancho, int largo);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario,
			vector<vector<dibujo_t>> tiles);
	void eliminar_personaje(Id id);
	void crearPersonajeEdificio(string tipo,int id);

	void crearPersonaje(string nombre,double x, double y, int id);
	void generarRecursoRandom();
	void mover_personaje(Id id,double mov_x,double mov_y);
	void ataque(Id idAtacante,Id idAtacado,int danio);
	void interactuar(Personaje* personaje,Posicion pos);
	void interactuar(Entidad * entidad,Posicion pos);
	//Cliente
	void acutalizarRecursos(string jugador, int id_pers, int cant,int id_rec);
	void agregarEntidad(string nombre,int x,int y,int cant);
	void cambiar_destino_personaje(Id id, double mov_x, double mov_y);
	Personaje* conectarCliente(string name,string tipo, int x,int y,dibujo_t dibujo,int id);
	bool esNombre(char* nombre);
	void crearEdificio(string nombre,int id_constructor,int x,int y);
	void construir(Id idAtacante,Id idConstruido,int construccion);
	//Personaje* conectarme(string name,string str, int x,int y);
	//void setearPosicionPersonaje(int id,double pos_x,double pos_y);
	void setId(double x,double y,int id);
	void reconectar(string id);
	void desconectar(string Id);
	void eliminarEntidad(int id);
	void eliminar(int id);
	char* string_to_char_array(string str);
	void empezarAccion(int id);
	void terminarAccion(int id);
	void finalizarConstruccion(int id);
	void capturaBandera(string razaAtacante,string razaPerdedora);

	void eliminarTodos(string razaPerdedora);


};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_ */

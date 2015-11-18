/*
 * GameControllerServer.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */
#include "../GameControllerSrc/GameController.h"

#ifndef GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_

#define KILL_ALL 0
#define FLAG 1
#define KING 2

class GameControllerServer: public GameController {
public:
	GameControllerServer();
	~GameControllerServer();
	bool hayEventos(SDL_mutex *mutex);
	msg_t sacarMensaje(SDL_mutex *mutex);
	void agregarMensaje(msg_t mensaje, SDL_mutex *mutex);
	void cambiar_personaje(int id_personaje, string nombre,string raza) ;
	void insertarModelo(Modelo* modelo);
	void setMapa(int ancho, int largo);
	void setDibujoMapa(vector<vector<dibujo_t>> escenario, vector<vector<dibujo_t>> tiles);

	void crearBandera(string name, string raza, int idCentro, SDL_mutex *mutex);
	void conectar();
	void eliminarEntidad(int id);
	void cambiar_destino_personaje(Id id, double mov_x, double mov_y);
	void atacar(Id idAtacante, Id idAtacado);
	void agregarEntidad(string nombre, int x, int y, int cant, SDL_mutex *mutex);
	//server
	void reconectar(std::string id);
	void desconectar(std::string id);
	void setAccionEntidad(int id_personaje, int id_entidad); //prra recurso o ataque edifico
	//void reconectar(int id);
	void agregarCliente(string name, string tipo, SDL_mutex *mutex);
	void generarRecursoRandom(SDL_mutex *mutex);
	//void desconectar(int id);
	void actualizar(SDL_mutex *mutex);
	char* string_to_char_array(string str);
	void crearEdificio(string nombre, int id_constructor, int x, int y, SDL_mutex *mutex);
	void crearPersonajeEdificio(string nombre, string tipo, Id id_edificio, SDL_mutex *mutex);
	void crearPersonajeHeroe(string nombre, string tipo, Id id_edificio, SDL_mutex *mutex);
	queue<msg_t> inicializacion();
	void crearCentroCivicoNuevoUser(string tipo, string nombreJugador, SDL_mutex * mutex);
	void capturaBandera(Personaje* personaje, string razaPerdedora, SDL_mutex *mutex);
	int getObjetivo() {
		return objetivo;
	}

	void setObjetivo(int objetivo) {
		this->objetivo = objetivo;
	}

private:
	int objetivo;
};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_ */

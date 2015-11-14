/*
 * Jugador.h
 *
 *  Created on: 25 de oct. de 2015
 *      Author: andres
 */
#include "Personaje.h"
#include "FactoryEdificio.h"
#include <map>
#ifndef JUGADOR_H_
#define JUGADOR_H_
 using namespace std;

class Jugador {
	string nombre;
	//Personaje* personaje;
	RecursosJugador * recursos;
	string ip;
	string raza;
	FactoryEdificio factory;
public:
	Jugador(string nombre,string ip,string raza);
	virtual ~Jugador();

	string getNombre() {
		return nombre;
	}
	string getIp() {
			return ip;
	}
	/**Personaje* getPersonaje()  {
		return personaje;
	}**/
	RecursosJugador * recursosJugador(){
		return this->recursos;
	}
	map<string,ObjetoMapa*> devolverEdificiosCreables();
	void cargarEdificios(std::map<std::string, ObjetoMapa*> tipos);
	void actualizarRecursos(int oro, int madera, int piedra);
	void pagar(Costo costo);
	bool puedePagar(Costo costo);
};

#endif /* JUGADOR_H_ */

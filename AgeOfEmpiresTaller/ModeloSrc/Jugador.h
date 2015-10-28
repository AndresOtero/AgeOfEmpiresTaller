/*
 * Jugador.h
 *
 *  Created on: 25 de oct. de 2015
 *      Author: andres
 */
#include "Personaje.h"
#ifndef JUGADOR_H_
#define JUGADOR_H_
 using namespace std;

class Jugador {
	string nombre;
	Personaje* personaje;
	string ip;
public:
	Jugador(string nombre,string ip,Personaje* personaje);
	virtual ~Jugador();

	string getNombre() {
		return nombre;
	}
	string getIp() {
			return ip;
	}
	Personaje* getPersonaje()  {
		return personaje;
	}
};

#endif /* JUGADOR_H_ */

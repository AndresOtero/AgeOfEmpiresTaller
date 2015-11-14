/*
 * RecursosJugador.h
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */
#include <iostream>
#include "Costo.h"

#ifndef RECURSOSJUGADOR_H_
#define RECURSOSJUGADOR_H_

class RecursosJugador {
private:
	int oro,piedra,madera,comida;
public:
	RecursosJugador();
	RecursosJugador(int oro, int piedra, int madera, int comida);
	void colectarOro(int cant);
	void colectarPiedra(int cant);
	void colectarMadera(int cant);
	void colectarComida(int cant);
	int cantOro();
	int cantPiedra();
	int cantMadera();
	int cantComida();
	bool estaVacio();
	bool puedePagar(Costo costo);
	bool pagar(Costo costo);
	void reintegrarCosto(Costo costo);
	void reset();
	virtual ~RecursosJugador();
};

#endif /* RECURSOSJUGADOR_H_ */

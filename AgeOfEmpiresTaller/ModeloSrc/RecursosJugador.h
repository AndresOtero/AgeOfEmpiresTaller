/*
 * RecursosJugador.h
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#ifndef RECURSOSJUGADOR_H_
#define RECURSOSJUGADOR_H_

class RecursosJugador {
private:
	int oro,piedra,madera;
public:
	RecursosJugador();
	RecursosJugador(int oro, int piedra, int madera);
	void colectarOro(int cant);
	void colectarPiedra(int cant);
	void colectarMadera(int cant);
	int cantOro();
	int cantPiedra();
	int cantMadera();
	void reset();
	virtual ~RecursosJugador();
};

#endif /* RECURSOSJUGADOR_H_ */

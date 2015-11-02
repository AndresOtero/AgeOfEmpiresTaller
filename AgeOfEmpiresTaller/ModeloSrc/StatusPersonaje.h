/*
 * StatusPersonaje.h
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#ifndef STATUSPERSONAJE_H_
#define STATUSPERSONAJE_H_
#include <math.h>
#define PARAMETRO_DEFENSA 100

class StatusPersonaje {
	double vida;
	int ataque;
	int defensa;


public:
	StatusPersonaje(){};
	StatusPersonaje(double vida,int ataque, int defensa){
		this->vida = vida;
		this->defensa = defensa;
		this->ataque=ataque;
	}

	double getVida(){ return this->vida;}
	double getAtaque(){ return this->ataque;}

	void atacarStatusPersonaje(int ataque);
	virtual ~StatusPersonaje();
};

#endif /* STATUSPERSONAJE_H_ */

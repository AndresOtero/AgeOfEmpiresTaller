/*
 * Atacable.h
 *
 *  Created on: Nov 10, 2015
 *      Author: tobias
 */
#include "Posicion.h"
#include <string>

#ifndef ATACABLE_H_
#define ATACABLE_H_

class Atacable {
public:
	Atacable();
	virtual int getId(){};
	virtual void recibirDanio(int danio){};
	virtual Posicion get_posicion(){};
	virtual int getArmadura(){};
	virtual bool esta_vivo(){};
	virtual bool esUnHeroe(){return false;};
	virtual bool esBandera(){return false;};
	virtual bool esUnCentroCivio(){return false;};
	virtual bool esAdyacente(Posicion pos){};
	virtual bool estaEnRango(int rango, Posicion atacante){};
	virtual std::string get_raza(){};
	virtual ~Atacable();
};

#endif /* ATACABLE_H_ */

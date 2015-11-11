/*
 * Atacable.h
 *
 *  Created on: Nov 10, 2015
 *      Author: tobias
 */
#include "Posicion.h"
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
	~Atacable();
};

#endif /* ATACABLE_H_ */

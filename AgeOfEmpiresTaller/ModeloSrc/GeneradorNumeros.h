/*
 * GenerarID.h
 *
 *  Created on: Oct 12, 2015
 *      Author: tobias
 */

#ifndef GENERADORNUMEROS_H_
#define GENERADORNUMEROS_H_
#include <iostream>
#include <random>

class GeneradorNumeros {
private:
	int devolver;
public:
	static unsigned int id;
	GeneradorNumeros(){devolver = id++;};
	int otroID(){return devolver;};
	int numeroRandom(int min, int max);
	virtual ~GeneradorNumeros();
};

#endif /* GENERADORNUMEROS_H_ */

/*
 * Contador.h
 *
 *  Created on: 9 de nov. de 2015
 *      Author: andres
 */

#ifndef CONTADOR_H_
#define CONTADOR_H_

class Contador {
public:
	Contador();

	Contador(int n);
	bool contar();
	virtual ~Contador();
private:
	int contador;
	int actual;
};

#endif /* CONTADOR_H_ */

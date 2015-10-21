/*
 * Interprete.h
 *
 *  Created on: Oct 21, 2015
 *      Author: tobias
 */
#include <iostream>
#include <cstdio>
using namespace std;
#ifndef INTERPRETE_INTERPRETE_H_
#define INTERPRETE_INTERPRETE_H_

class Interprete {
public:
	Interprete();
	void generarMensaje(int tipo_accion,int *parametros);
	void leerMensaje(string mensaje);
	virtual ~Interprete();
};

#endif /* INTERPRETE_INTERPRETE_H_ */

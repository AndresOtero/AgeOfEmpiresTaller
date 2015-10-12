/*
 * RecursoVista.h
 *
 *  Created on: Oct 11, 2015
 *      Author: tobias
 */

#ifndef RECURSOVISTA_H_
#define RECURSOVISTA_H_
#include "Textura.h"
#include <vector>
#include <memory>

class RecursoVista {
private:
	shared_ptr<Textura> text;
	shared_ptr<Textura> img;
	int cant;
public:
	RecursoVista();
	int cantidad();
	void cambiarCant(int cant);
	shared_ptr<Textura> texto();
	shared_ptr<Textura> imagen();
	virtual ~RecursoVista();
};

#endif /* RECURSOVISTA_H_ */

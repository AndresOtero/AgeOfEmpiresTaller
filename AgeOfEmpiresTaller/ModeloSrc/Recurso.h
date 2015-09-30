/*
 * Recurso.h
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Entidad.h"
#include "RecursosJugador.h"

#ifndef RECURSO_H_
#define RECURSO_H_

class Recurso :public Entidad {
private:
	int cantidad;
public:
	Recurso(ObjetoMapa* objeto);
	Recurso(ObjetoMapa* objeto,int x, int y);
	int	obtenerRecurso();
	virtual void recolectar(RecursosJugador* recursos){};
	virtual ~Recurso();
};

#endif /* RECURSO_H_ */

/*
 * Recurso.h
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "Entidad.h"
#include "RecursosJugador.h"
#include "GeneradorNumeros.h"
#ifndef RECURSO_H_
#define RECURSO_H_
#define RECURSO_POR_INTERVALO 25

class Recurso :public Entidad {
private:
	int cantidad;
public:
	Recurso(ObjetoMapa* objeto);
	Recurso(ObjetoMapa* objeto,int x, int y);
	int	obtenerRecurso();
	void setRecurso(int cantidad);
	int sacarRecurso();
	virtual void recolectar(RecursosJugador* recursos){};
	virtual ~Recurso();
};

#endif /* RECURSO_H_ */
